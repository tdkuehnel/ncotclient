#ifndef __CPWCLIENTCONNECT_H
#define __CPWCLIENTCONNECT_H

#include <gtk/gtk.h>
#include "cpwclientwin.h"


#define CPW_CLIENT_CONNECT_TYPE (cpw_client_connect_get_type ())
G_DECLARE_FINAL_TYPE (CpwClientConnect, cpw_client_connect, CPW, CLIENT_CONNECT, GtkDialog)


CpwClientConnect        *cpw_client_connect_new          (CpwClientWindow *win);


#endif /* __CPWCLIENTCONNECT_H */
