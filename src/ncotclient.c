#include <gtk/gtk.h>

#include "cpwclient.h"
#include "cpwclientwin.h"
#include "cpwclientprefs.h"
#include "cpwclientconnect.h"

struct _CpwClient
{
  GtkApplication parent;
};

G_DEFINE_TYPE(CpwClient, cpw_client, GTK_TYPE_APPLICATION);

static void
cpw_client_init (CpwClient *app)
{
}

static void
connect_activated (GSimpleAction *action,
		   GVariant      *parameter,
		   gpointer       app)

{
  CpwClientConnect *connect;
  GtkWindow *win;
  
  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  connect = cpw_client_connect_new (CPW_CLIENT_WINDOW (win));
  gtk_window_present (GTK_WINDOW (connect));
}

static void
preferences_activated (GSimpleAction *action,
                       GVariant      *parameter,
                       gpointer       app)
{
  CpwClientPrefs *prefs;
  GtkWindow *win;

  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  prefs = cpw_client_prefs_new (CPW_CLIENT_WINDOW (win));
  gtk_window_present (GTK_WINDOW (prefs));
}

static void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
  g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
{
  { "preferences", preferences_activated, NULL, NULL, NULL },
  { "connect", connect_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void
cpw_client_startup (GApplication *app)
{
  GtkBuilder *builder;
  GMenuModel *app_menu;
  const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (cpw_client_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entries, G_N_ELEMENTS (app_entries),
                                   app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.quit",
                                         quit_accels);

  builder = gtk_builder_new_from_resource ("/org/gtk/cpwclient/app-menu.ui");
  app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
  gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
  g_object_unref (builder);
}

static void
cpw_client_activate (GApplication *app)
{
  CpwClientWindow *win;

  win = cpw_client_window_new (CPW_CLIENT (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
cpw_client_open (GApplication  *app,
                  GFile        **files,
                  gint           n_files,
                  const gchar   *hint)
{
  GList *windows;
  CpwClientWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = CPW_CLIENT_WINDOW (windows->data);
  else
    win = cpw_client_window_new (CPW_CLIENT (app));

  for (i = 0; i < n_files; i++)
    cpw_client_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void
cpw_client_class_init (CpwClientClass *class)
{
  G_APPLICATION_CLASS (class)->startup = cpw_client_startup;
  G_APPLICATION_CLASS (class)->activate = cpw_client_activate;
  G_APPLICATION_CLASS (class)->open = cpw_client_open;
}

CpwClient *
cpw_client_new (void)
{
  return g_object_new (CPW_CLIENT_TYPE,
                       "application-id", "org.gtk.cpwclient",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
