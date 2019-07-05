#include <gtk/gtk.h>

#include "ncotclient.h"
#include "ncotclientwin.h"
#include "ncotclientprefs.h"

struct _NcotClientPrefs
{
  GtkDialog parent;
};

typedef struct _NcotClientPrefsPrivate NcotClientPrefsPrivate;

struct _NcotClientPrefsPrivate
{
  GSettings *settings;
  GtkWidget *font;
  GtkWidget *transition;
};

G_DEFINE_TYPE_WITH_PRIVATE(NcotClientPrefs, ncot_client_prefs, GTK_TYPE_DIALOG)

static void
ncot_client_prefs_init (NcotClientPrefs *prefs)
{
  NcotClientPrefsPrivate *priv;

  priv = ncot_client_prefs_get_instance_private (prefs);
  gtk_widget_init_template (GTK_WIDGET (prefs));
  priv->settings = g_settings_new ("org.gtk.ncotclient");

  g_settings_bind (priv->settings, "font",
                   priv->font, "font",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (priv->settings, "transition",
                   priv->transition, "active-id",
                   G_SETTINGS_BIND_DEFAULT);
}

static void
ncot_client_prefs_dispose (GObject *object)
{
  NcotClientPrefsPrivate *priv;

  priv = ncot_client_prefs_get_instance_private (NCOT_CLIENT_PREFS (object));
  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (ncot_client_prefs_parent_class)->dispose (object);
}

static void
ncot_client_prefs_class_init (NcotClientPrefsClass *class)
{
  G_OBJECT_CLASS (class)->dispose = ncot_client_prefs_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/gtk/ncotclient/prefs.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), NcotClientPrefs, font);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), NcotClientPrefs, transition);
}

NcotClientPrefs *
ncot_client_prefs_new (NcotClientWindow *win)
{
  return g_object_new (NCOT_CLIENT_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
