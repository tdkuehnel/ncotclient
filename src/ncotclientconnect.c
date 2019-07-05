#include <gtk/gtk.h>

#include "cpwclient.h"
#include "cpwclientwin.h"
#include "cpwclientconnect.h"

struct _CpwClientConnect
{
  GtkDialog parent;
};

typedef struct _CpwClientConnectPrivate CpwClientConnectPrivate;

struct _CpwClientConnectPrivate
{
  GSettings *settings;
  GtkWidget *connectstring;
  GtkWidget *connectport;
};

G_DEFINE_TYPE_WITH_PRIVATE(CpwClientConnect, cpw_client_connect, GTK_TYPE_DIALOG)

static void
cpw_client_connect_init (CpwClientConnect *connect)
{
  CpwClientConnectPrivate *priv;

  priv = cpw_client_connect_get_instance_private (connect);
  gtk_widget_init_template (GTK_WIDGET (connect));
  priv->settings = g_settings_new ("org.gtk.cpwclient");

  g_settings_bind (priv->settings, "connectstring",
                   priv->connectstring, "text",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (priv->settings, "connectport",
                   priv->connectport, "text",
                   G_SETTINGS_BIND_DEFAULT);
}

static void
cpw_client_connect_dispose (GObject *object)
{
  CpwClientConnectPrivate *priv;

  priv = cpw_client_connect_get_instance_private (CPW_CLIENT_CONNECT (object));
  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (cpw_client_connect_parent_class)->dispose (object);
}

static void
cpw_client_connect_class_init (CpwClientConnectClass *class)
{
  G_OBJECT_CLASS (class)->dispose = cpw_client_connect_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/gtk/cpwclient/connect.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), CpwClientConnect, connectstring);
}

CpwClientConnect *
cpw_client_connect_new (CpwClientWindow *win)
{
  return g_object_new (CPW_CLIENT_CONNECT_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
