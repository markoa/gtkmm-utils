noinst_PROGRAMS= \
	logging \
	tiles-simple

logging_SOURCES=logging.cc logging.h
logging_LDFLAGS=@GTKMM_UTILS_LIBS@

tiles_simple_SOURCES=tiles-simple.cc tiles-simple.h
tiles_simple_LDFLAGS=@GTKMM_UTILS_LIBS@

INCLUDES= \
	-I$(top_srcdir) \
	-I$(top_srcdir)/glibmm-utils \
	-I$(top_srcdir)/gtkmm-utils \
	@GTKMM_UTILS_CFLAGS@

LDADD= \
	$(top_builddir)/glibmm-utils/libglibmm-utils.la \
	$(top_builddir)/gtkmm-utils/libgtkmm-utils.la
