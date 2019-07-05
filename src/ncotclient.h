#ifndef __NCOTCLIENT_H
#define __NCOTCLIENT_H

#include <gtk/gtk.h>


#define NCOT_CLIENT_TYPE (ncot_client_get_type ())
G_DECLARE_FINAL_TYPE (NcotClient, ncot_client, NCOT, CLIENT, GtkApplication)


NcotClient     *ncot_client_new         (void);


#endif /* __NCOTCLIENT_H */
