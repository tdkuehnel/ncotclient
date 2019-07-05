#ifndef __CPWCLIENT_H
#define __CPWCLIENT_H

#include <gtk/gtk.h>


#define CPW_CLIENT_TYPE (cpw_client_get_type ())
G_DECLARE_FINAL_TYPE (CpwClient, cpw_client, CPW, CLIENT, GtkApplication)


CpwClient     *cpw_client_new         (void);


#endif /* __CPWCLIENT_H */
