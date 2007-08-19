noinst_PROGRAMS= \
	logging

logging_SOURCES=logging.cc
logging_LDFLAGS=@GTKMM_UTILS_LIBS@

INCLUDES= \
	-I$(top_srcdir) \
	-I$(top_srcdir)/glibmm-utils \
	-I$(top_srcdir)/gtkmm-utils \
	@GTKMM_UTILS_CFLAGS@

LDADD= \
	$(top_builddir)/glibmm-utils/libglibmm-utils.la \
	$(top_builddir)/gtkmm-utils/libgtkmm-utils.la
