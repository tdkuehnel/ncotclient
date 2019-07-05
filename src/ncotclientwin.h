#ifndef __NCOTCLIENTWIN_H
#define __NCOTCLIENTWIN_H

#include <gtk/gtk.h>
#include "ncotclient.h"


#define NCOT_CLIENT_WINDOW_TYPE (ncot_client_window_get_type ())
G_DECLARE_FINAL_TYPE (NcotClientWindow, ncot_client_window, NCOT, CLIENT_WINDOW, GtkApplicationWindow)


NcotClientWindow       *ncot_client_window_new          (NcotClient *app);
void                    ncot_client_window_open         (NcotClientWindow *win,
                                                         GFile            *file);


#endif /* __NCOTCLIENTWIN_H */
