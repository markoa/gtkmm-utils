
hh_sources = \
	glibmm-utils.hh \
	date.hh \
	exception.hh \
	initializer.hh \
	log-stream.hh \
	log-stream-utils.hh \
	option-utils.hh \
	scope-logger.hh \
	ustring.hh

cc_sources = \
	date.cc \
	exception.cc \
	initializer.cc \
	log-stream.cc \
	option-utils.cc \
	scope-logger.cc \
	ustring.cc

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = glibmm-utils.pc

library_includedir = $(includedir)/glibmm-utils-@GTKMM_UTILS_API_VERSION@/glibmm-utils
library_include_HEADERS = $(hh_sources)

INCLUDES = \
	-I$(top_srcdir) \
	$(GLIBMM_CFLAGS) \
	$(LIBGTHREAD_CFLAGS)

lib_LTLIBRARIES = libglibmm-utils.la

libglibmm_utils_la_SOURCES = $(hh_sources) $(cc_sources)
libglibmm_utils_la_LIBADD = $(GLIBMM_LIBS) $(LIBGTHREAD_LIBS)
libglibmm_utils_la_LDFLAGS = -export-dynamic -fPIC -version-info @LIBGTKMM_UTILS_SO_VERSION@ -release $(GTKMM_UTILS_RELEASE)
