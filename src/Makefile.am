PKGCONFIG = $(shell which pkg-config)
GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)
GLIB_COMPILE_SCHEMAS = $(shell $(PKGCONFIG) --variable=glib_compile_schemas gio-2.0)

bin_PROGRAMS = ncotclient

ncotclient_CFLAGS = $(GTK_CFLAGS)
ncotclient_LDADD = $(GTK_LIBS)
ncotclient_SOURCES = 				\
	ncotclientmain.c 			\
	ncotclient.c ncotclient.h 		\
	ncotclientwin.c ncotclientwin.h 		\
	ncotclientprefs.c ncotclientprefs.h 	\
	ncotclientconnect.c ncotclientconnect.h 	\
	resources.c

BUILT_SOURCES = 				\
	resources.c 				\
	gschemas.compiled

resources.c: ncotclient.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/ncotclient.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $(srcdir)/ncotclient.gresource.xml \
		--target=$@ --sourcedir=$(srcdir) --generate-source

#resources.c: exampleapp.gresource.xml 
#	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) $(srcdir)/exampleapp.gresource.xml \
#		--target=$@ --sourcedir=$(srcdir) --generate-source

gsettings_SCHEMAS = 				\
	org.gtk.ncotclient.gschema.xml

@GSETTINGS_RULES@

gschemas.compiled: org.gtk.ncotclient.gschema.xml
	$(GLIB_COMPILE_SCHEMAS) .

EXTRA_DIST = 					\
	window.ui 				\
	app-menu.ui 				\
	prefs.ui 				\
	connect.ui 				\
	ncotclient.gresource.xml 		\
	org.gtk.ncotclient.gschema.xml

CLEANFILES = 					\
	gschemas.compiled

-include $(top_srcdir)/git.mk
