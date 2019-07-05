#include <gtk/gtk.h>

#include "cpwclient.h"
#include "cpwclientwin.h"
#include "cpwclientprefs.h"

struct _CpwClientPrefs
{
  GtkDialog parent;
};

typedef struct _CpwClientPrefsPrivate CpwClientPrefsPrivate;

struct _CpwClientPrefsPrivate
{
  GSettings *settings;
  GtkWidget *font;
  GtkWidget *transition;
};

G_DEFINE_TYPE_WITH_PRIVATE(CpwClientPrefs, cpw_client_prefs, GTK_TYPE_DIALOG)

static void
cpw_client_prefs_init (CpwClientPrefs *prefs)
{
  CpwClientPrefsPrivate *priv;

  priv = cpw_client_prefs_get_instance_private (prefs);
  gtk_widget_init_template (GTK_WIDGET (prefs));
  priv->settings = g_settings_new ("org.gtk.cpwclient");

  g_settings_bind (priv->settings, "font",
                   priv->font, "font",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (priv->settings, "transition",
                   priv->transition, "active-id",
                   G_SETTINGS_BIND_DEFAULT);
}

static void
cpw_client_prefs_dispose (GObject *object)
{
  CpwClientPrefsPrivate *priv;

  priv = cpw_client_prefs_get_instance_private (CPW_CLIENT_PREFS (object));
  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (cpw_client_prefs_parent_class)->dispose (object);
}

static void
cpw_client_prefs_class_init (CpwClientPrefsClass *class)
{
  G_OBJECT_CLASS (class)->dispose = cpw_client_prefs_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/gtk/cpwclient/prefs.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), CpwClientPrefs, font);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), CpwClientPrefs, transition);
}

CpwClientPrefs *
cpw_client_prefs_new (CpwClientWindow *win)
{
  return g_object_new (CPW_CLIENT_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
