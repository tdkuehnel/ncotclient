AC_INIT([ncotclient], [0.1], [tdkuehnel@naturfreundeskreis.de])
## AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])

GTK_REQUIRED=3.18.9
GLIB_REQUIRED=2.46.2
PKG_CHECK_MODULES([GTK],[
  gtk+-3.0 >= $GTK_REQUIRED
  glib-2.0 >= $GLIB_REQUIRED
  gmodule-2.0
  libxml-2.0 >= 2.4.0
])

PKG_CHECK_MODULES([GMODULE_EXPORT],[
  gmodule-export-2.0
])

GLIB_GSETTINGS

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
