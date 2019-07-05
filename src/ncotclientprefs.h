#ifndef __NCOTCLIENTPREFS_H
#define __NCOTCLIENTPREFS_H

#include <gtk/gtk.h>
#include "ncotclientwin.h"


#define NCOT_CLIENT_PREFS_TYPE (ncot_client_prefs_get_type ())
G_DECLARE_FINAL_TYPE (NcotClientPrefs, ncot_client_prefs, NCOT, CLIENT_PREFS, GtkDialog)


NcotClientPrefs        *ncot_client_prefs_new          (NcotClientWindow *win);


#endif /* __NCOTCLIENTPREFS_H */
