
hh_sources = \
	gtkmm-utils.hh \
	dialog.hh \
	page-navigator.hh \
	tile.hh \
	tile-view.hh \
	white-box.hh

cc_sources = dialog.cc \
	page-navigator.cc \
	tile.cc \
	tile-view.cc \
	white-box.cc

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = gtkmm-utils.pc

library_includedir = $(includedir)/gtkmm-utils-@GTKMM_UTILS_API_VERSION@/gtkmm-utils
library_include_HEADERS = $(hh_sources)

INCLUDES = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/glibmm-utils/ \
	$(GTKMM_UTILS_CFLAGS)

lib_LTLIBRARIES = libgtkmm-utils.la

libgtkmm_utils_la_SOURCES = $(hh_sources) $(cc_sources)
libgtkmm_utils_la_LIBADD = $(GTKMM_UTILS_LIBS)
libgtkmm_utils_la_LDFLAGS = -export-dynamic -fPIC -version-info @LIBGTKMM_UTILS_SO_VERSION@ -release $(GTKMM_UTILS_RELEASE)
