#ifndef __NCOTCLIENTCONNECT_H
#define __NCOTCLIENTCONNECT_H

#include <gtk/gtk.h>
#include "ncotclientwin.h"


#define NCOT_CLIENT_CONNECT_TYPE (ncot_client_connect_get_type ())
G_DECLARE_FINAL_TYPE (NcotClientConnect, ncot_client_connect, NCOT, CLIENT_CONNECT, GtkDialog)


NcotClientConnect        *ncot_client_connect_new          (NcotClientWindow *win);


#endif /* __NCOTCLIENTCONNECT_H */
