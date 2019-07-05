#include <gtk/gtk.h>

#include "ncotclient.h"
#include "ncotclientwin.h"
#include "ncotclientconnect.h"

struct _NcotClientConnect
{
  GtkDialog parent;
};

typedef struct _NcotClientConnectPrivate NcotClientConnectPrivate;

struct _NcotClientConnectPrivate
{
  GSettings *settings;
  GtkWidget *connectstring;
  GtkWidget *connectport;
};

G_DEFINE_TYPE_WITH_PRIVATE(NcotClientConnect, ncot_client_connect, GTK_TYPE_DIALOG)

static void
ncot_client_connect_init (NcotClientConnect *connect)
{
  NcotClientConnectPrivate *priv;

  priv = ncot_client_connect_get_instance_private (connect);
  gtk_widget_init_template (GTK_WIDGET (connect));
  priv->settings = g_settings_new ("org.gtk.ncotclient");

  g_settings_bind (priv->settings, "connectstring",
                   priv->connectstring, "text",
                   G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (priv->settings, "connectport",
                   priv->connectport, "text",
                   G_SETTINGS_BIND_DEFAULT);
}

static void
ncot_client_connect_dispose (GObject *object)
{
  NcotClientConnectPrivate *priv;

  priv = ncot_client_connect_get_instance_private (NCOT_CLIENT_CONNECT (object));
  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (ncot_client_connect_parent_class)->dispose (object);
}

static void
ncot_client_connect_class_init (NcotClientConnectClass *class)
{
  G_OBJECT_CLASS (class)->dispose = ncot_client_connect_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/gtk/ncotclient/connect.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), NcotClientConnect, connectstring);
}

NcotClientConnect *
ncot_client_connect_new (NcotClientWindow *win)
{
  return g_object_new (NCOT_CLIENT_CONNECT_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
