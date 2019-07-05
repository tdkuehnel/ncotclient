#include <gtk/gtk.h>

#include "cpwclient.h"

int
main (int argc, char *argv[])
{
  /* Since this example is running uninstalled,
   * we have to help it find its schema. This
   * is *not* necessary in properly installed
   * application.
   */
  g_setenv ("GSETTINGS_SCHEMA_DIR", ".", FALSE);

  return g_application_run (G_APPLICATION (cpw_client_new ()), argc, argv);
}
