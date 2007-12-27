/* GTK+: gtkfilechooserentry.h
 * 
 * Copyright (c) 2004 James M. Cape <jcape@ignore-your.tv>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GTK_FILE_CHOOSER_ENTRY_H__
#define __GTK_FILE_CHOOSER_ENTRY_H__

#include <gtk/gtkhbox.h>
#include <gtk/gtkfilechooser.h>

G_BEGIN_DECLS


#define GTK_TYPE_FILE_CHOOSER_ENTRY \
  (gtk_file_chooser_entry_get_type ())
#define GTK_FILE_CHOOSER_ENTRY(object) \
  (G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_FILE_CHOOSER_ENTRY, GtkFileChooserEntry))
#define GTK_FILE_CHOOSER_ENTRY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FILE_CHOOSER_ENTRY, GtkFileChooserEntryClass))
#define GTK_IS_FILE_CHOOSER_ENTRY(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_FILE_CHOOSER_ENTRY))
#define GTK_IS_FILE_CHOOSER_ENTRY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FILE_CHOOSER_ENTRY))
#define GTK_FILE_CHOOSER_ENTRY_GET_CLASS(object) \
  (G_TYPE_INSTANCE_GET_CLASS ((object), GTK_TYPE_FILE_CHOOSER_ENTRY, GtkFileChooserEntryClass))


typedef struct _GtkFileChooserEntry GtkFileChooserEntry;
typedef struct _GtkFileChooserEntryPrivate GtkFileChooserEntryPrivate;
typedef struct _GtkFileChooserEntryClass GtkFileChooserEntryClass;

struct _GtkFileChooserEntry
{
  /*< private >*/
  GtkHBox parent;

  GtkFileChooserEntryPrivate *priv;
};

struct _GtkFileChooserEntryClass
{
  /*< private >*/
  GtkHBoxClass parent_class;

  void (*__gtk_reserved1);
  void (*__gtk_reserved2);
  void (*__gtk_reserved3);
  void (*__gtk_reserved4);
  void (*__gtk_reserved5);
  void (*__gtk_reserved6);
  void (*__gtk_reserved7);
  void (*__gtk_reserved8);
};


GType                 gtk_file_chooser_entry_get_type           (void) G_GNUC_CONST;
GtkWidget *           gtk_file_chooser_entry_new                (const gchar          *title,
                                                                 GtkFileChooserAction  action);
GtkWidget *           gtk_file_chooser_entry_new_with_backend   (const gchar          *title,
                                                                 GtkFileChooserAction  action,
                                                                 const gchar          *backend);
GtkWidget *           gtk_file_chooser_entry_new_with_dialog    (GtkWidget            *dialog);
G_CONST_RETURN gchar *gtk_file_chooser_entry_get_title          (GtkFileChooserEntry  *entry);
void                  gtk_file_chooser_entry_set_title          (GtkFileChooserEntry  *entry,
                                                                 const gchar          *title);
gint                  gtk_file_chooser_entry_get_width_chars    (GtkFileChooserEntry  *entry);
void                  gtk_file_chooser_entry_set_width_chars    (GtkFileChooserEntry  *entry,
                                                                 gint                  n_chars);
gboolean              gtk_file_chooser_entry_get_focus_on_click (GtkFileChooserEntry  *entry);
void                  gtk_file_chooser_entry_set_focus_on_click (GtkFileChooserEntry  *entry,
                                                                 gboolean              focus_on_click);

gchar                *gtk_file_chooser_entry_get_uri            (GtkFileChooserEntry  *entry);

G_END_DECLS

#endif /* !__GTK_FILE_CHOOSER_ENTRY_H__ */
