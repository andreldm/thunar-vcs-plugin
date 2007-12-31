/*-
 * Copyright (c) 2006 Peter de Ridder <peter@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __TSH_LOG_MESSAGE_DIALOG_H__
#define __TSH_LOG_MESSAGE_DIALOG_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS;

typedef struct _TshLogMessageDialogClass TshLogMessageDialogClass;
typedef struct _TshLogMessageDialog      TshLogMessageDialog;

#define TSH_TYPE_LOG_MESSAGE_DIALOG             (tsh_log_message_dialog_get_type ())
#define TSH_LOG_MESSAGE_DIALOG(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TSH_TYPE_LOG_MESSAGE_DIALOG, TshLogMessageDialog))
#define TSH_LOG_MESSAGE_DIALOG_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TSH_TYPE_LOG_MESSAGE_DIALOG, TshLogMessageDialogClass))
#define TSH_IS_LOG_MESSAGE_DIALOG(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TSH_TYPE_LOG_MESSAGE_DIALOG))
#define TSH_IS_LOG_MESSAGE_DIALOG_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TSH_TYPE_LOG_MESSAGE_DIALOG))
#define TSH_LOG_MESSAGE_DIALOG_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TSH_TYPE_LOG_MESSAGE_DIALOG, TshLogMessageDialogClass))

GType      tsh_log_message_dialog_get_type    (void) G_GNUC_CONST G_GNUC_INTERNAL;

GtkWidget* tsh_log_message_dialog_new         (const gchar *title,
                                               GtkWindow *parent,
                                               GtkDialogFlags flags) G_GNUC_MALLOC G_GNUC_INTERNAL;

void       tsh_log_message_dialog_add         (TshLogMessageDialog *dialog,
                                               const char *state,
                                               const char *file);

gchar *    tsh_log_message_dialog_get_message (TshLogMessageDialog *dialog);

G_END_DECLS;

#endif /* !__TSH_LOG_MESSAGE_DIALOG_H__ */