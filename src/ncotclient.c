#include <gtk/gtk.h>

static const CLSID CLSID_FileOpenDialog  = {0xdc1c5a9c, 0xe88a, 0x4dde, {0xa5, 0xa1, 0x60, 0xf8, 0x2a, 0x20, 0xae, 0xf7}};
static const CLSID CLSID_FileSaveDialog  = {0xc0b4e2f3, 0xba21, 0x4773,{0x8d, 0xba, 0x33, 0x5e, 0xc9, 0x46, 0xeb, 0x8b}};

#include "ncotclient.h"
#include "ncotclientwin.h"
#include "ncotclientprefs.h"
#include "ncotclientconnect.h"

struct _NcotClient
{
  GtkApplication parent;
};

G_DEFINE_TYPE(NcotClient, ncot_client, GTK_TYPE_APPLICATION);

static void
ncot_client_init (NcotClient *app)
{
}

static void
connect_activated (GSimpleAction *action,
		   GVariant      *parameter,
		   gpointer       app)

{
  NcotClientConnect *connect;
  GtkWindow *win;
  
  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  connect = ncot_client_connect_new (NCOT_CLIENT_WINDOW (win));
  gtk_window_present (GTK_WINDOW (connect));
}

static void
preferences_activated (GSimpleAction *action,
                       GVariant      *parameter,
                       gpointer       app)
{
  NcotClientPrefs *prefs;
  GtkWindow *win;

  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  prefs = ncot_client_prefs_new (NCOT_CLIENT_WINDOW (win));
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
ncot_client_startup (GApplication *app)
{
  GtkBuilder *builder;
  GMenuModel *app_menu;
  const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (ncot_client_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entries, G_N_ELEMENTS (app_entries),
                                   app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.quit",
                                         quit_accels);

  builder = gtk_builder_new_from_resource ("/org/gtk/ncotclient/app-menu.ui");
  app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
  gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
  g_object_unref (builder);
}

static void
ncot_client_activate (GApplication *app)
{
  NcotClientWindow *win;

  win = ncot_client_window_new (NCOT_CLIENT (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
ncot_client_open (GApplication  *app,
                  GFile        **files,
                  gint           n_files,
                  const gchar   *hint)
{
  GList *windows;
  NcotClientWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = NCOT_CLIENT_WINDOW (windows->data);
  else
    win = ncot_client_window_new (NCOT_CLIENT (app));

  for (i = 0; i < n_files; i++)
    ncot_client_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void
ncot_client_class_init (NcotClientClass *class)
{
  G_APPLICATION_CLASS (class)->startup = ncot_client_startup;
  G_APPLICATION_CLASS (class)->activate = ncot_client_activate;
  G_APPLICATION_CLASS (class)->open = ncot_client_open;
}

NcotClient *
ncot_client_new (void)
{
  return g_object_new (NCOT_CLIENT_TYPE,
                       "application-id", "org.gtk.ncotclient",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
