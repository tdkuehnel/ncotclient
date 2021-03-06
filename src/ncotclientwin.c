#include <gtk/gtk.h>

#include "ncotclient.h"
#include "ncotclientwin.h"

struct _NcotClientWindow
{
  GtkApplicationWindow parent;
};

typedef struct NcotClientWindowPrivate NcotClientWindowPrivate;

struct NcotClientWindowPrivate
{
  GSettings *settings;
  GtkWidget *stack;
};

G_DEFINE_TYPE_WITH_PRIVATE(NcotClientWindow, ncot_client_window, GTK_TYPE_APPLICATION_WINDOW);

static void
ncot_client_window_init (NcotClientWindow *win)
{
  NcotClientWindowPrivate *priv;

  priv = ncot_client_window_get_instance_private (win);
  gtk_widget_init_template (GTK_WIDGET (win));
  priv->settings = g_settings_new ("org.gtk.ncotclient");

  g_settings_bind (priv->settings, "transition",
                   priv->stack, "transition-type",
                   G_SETTINGS_BIND_DEFAULT);
}

static void
ncot_client_window_dispose (GObject *object)
{
  NcotClientWindow *win;
  NcotClientWindowPrivate *priv;

  win = NCOT_CLIENT_WINDOW (object);
  priv = ncot_client_window_get_instance_private (win);

  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (ncot_client_window_parent_class)->dispose (object);
}

static void
ncot_client_window_class_init (NcotClientWindowClass *class)
{
  G_OBJECT_CLASS (class)->dispose = ncot_client_window_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/gtk/ncotclient/window.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), NcotClientWindow, stack);
}

NcotClientWindow *
ncot_client_window_new (NcotClient *app)
{
  return g_object_new (NCOT_CLIENT_WINDOW_TYPE, "application", app, NULL);
}

void
ncot_client_window_open (NcotClientWindow *win,
                         GFile            *file)
{
  NcotClientWindowPrivate *priv;
  gchar *basename;
  GtkWidget *scrolled, *view;
  gchar *contents;
  gsize length;
  GtkTextBuffer *buffer;
  GtkTextTag *tag;
  GtkTextIter start_iter, end_iter;

  priv = ncot_client_window_get_instance_private (win);
  basename = g_file_get_basename (file);

  scrolled = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolled);
  gtk_widget_set_hexpand (scrolled, TRUE);
  gtk_widget_set_vexpand (scrolled, TRUE);
  view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
  gtk_widget_show (view);
  gtk_container_add (GTK_CONTAINER (scrolled), view);
  gtk_stack_add_titled (GTK_STACK (priv->stack), scrolled, basename, basename);

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

  if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    {
      gtk_text_buffer_set_text (buffer, contents, length);
      g_free (contents);
    }

  tag = gtk_text_buffer_create_tag (buffer, NULL, NULL);
  g_settings_bind (priv->settings, "font", tag, "font", G_SETTINGS_BIND_DEFAULT);

  gtk_text_buffer_get_start_iter (buffer, &start_iter);
  gtk_text_buffer_get_end_iter (buffer, &end_iter);
  gtk_text_buffer_apply_tag (buffer, tag, &start_iter, &end_iter);

  g_free (basename);
}
