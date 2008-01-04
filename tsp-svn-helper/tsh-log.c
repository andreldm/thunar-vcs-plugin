/*-
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <glib.h>
#include <gtk/gtk.h>

#include <thunar-vfs/thunar-vfs.h>

#include <subversion-1/svn_client.h>

#include "tsh-common.h"
#include "tsh-dialog-common.h"
#include "tsh-log-dialog.h"

#include "tsh-log.h"

struct thread_args {
	svn_client_ctx_t *ctx;
	apr_pool_t *pool;
	TshLogDialog *dialog;
	gchar **files;
	apr_array_header_t *paths;
};

static gpointer log_thread (gpointer user_data)
{
	struct thread_args *args = user_data;
  svn_opt_revision_t revision, start, end;
	svn_error_t *err;
	svn_client_ctx_t *ctx = args->ctx;
	apr_pool_t *pool = args->pool;
	TshLogDialog *dialog = args->dialog;
	gchar **files = args->files;
	apr_array_header_t *paths = args->paths;
	gint size, i;

  if(!args->paths)
  {
    size = files?g_strv_length(files):0;

    if(size)
    {
      paths = apr_array_make (pool, size, sizeof (const char *));
      
      for (i = 0; i < size; i++)
      {
        APR_ARRAY_PUSH (paths, const char *) = files[i];
      }
    }
    else
    {
      paths = apr_array_make (pool, 1, sizeof (const char *));
      
      APR_ARRAY_PUSH (paths, const char *) = ""; // current directory
    }

    args->paths = paths;
  }

  revision.kind = svn_opt_revision_unspecified;
  start.kind = svn_opt_revision_head;
  end.kind = svn_opt_revision_number;
  end.value.number = 0;
	if ((err = svn_client_log3(paths, &revision, &start, &end, 0, TRUE, FALSE, tsh_log_func, dialog, ctx, pool)))
	{
		gdk_threads_enter();
		tsh_log_dialog_done (dialog);
		gdk_threads_leave();

		svn_handle_error2(err, stderr, FALSE, G_LOG_DOMAIN ": ");
		svn_error_clear(err);
		return GINT_TO_POINTER (FALSE);
	}

	gdk_threads_enter();
	tsh_log_dialog_done (dialog);
	gdk_threads_leave();
	
	return GINT_TO_POINTER (TRUE);
}

static void create_log_thread(TshLogDialog *dialog, struct thread_args *args)
{
	GThread *thread = g_thread_create (log_thread, args, TRUE, NULL);
  if (thread)
    tsh_replace_thread (thread);
  else
    tsh_log_dialog_done (dialog);
}

GThread *tsh_log (gchar **files, svn_client_ctx_t *ctx, apr_pool_t *pool)
{
	GtkWidget *dialog;
	struct thread_args *args;

	dialog = tsh_log_dialog_new (NULL, NULL, 0);
  g_signal_connect(dialog, "cancel-clicked", tsh_cancel, NULL);
	tsh_dialog_start (GTK_DIALOG (dialog), TRUE);

	ctx->notify_func2 = NULL;
	ctx->notify_baton2 = NULL;

  args = g_malloc (sizeof (struct thread_args));
	args->ctx = ctx;
	args->pool = pool;
	args->dialog = TSH_LOG_DIALOG (dialog);
	args->files = files;
  args->paths = NULL;

  g_signal_connect(dialog, "refresh-clicked", G_CALLBACK(create_log_thread), args);

	return g_thread_create (log_thread, args, TRUE, NULL);
}

