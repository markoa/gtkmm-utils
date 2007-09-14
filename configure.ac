## configure.ac
#
## Process this file with autoconf to produce a configure script.

pushdef([GTKMM_UTILS_MAJOR_VERSION], [0])
pushdef([GTKMM_UTILS_MINOR_VERSION], [2])
pushdef([GTKMM_UTILS_MICRO_VERSION], [0])
pushdef([GTKMM_UTILS_VERSION], GTKMM_UTILS_MAJOR_VERSION.GTKMM_UTILS_MINOR_VERSION.GTKMM_UTILS_MICRO_VERSION)

AC_INIT([gtkmm-utils], GTKMM_UTILS_VERSION, [marko@marko.anastasov.name])
AC_CONFIG_SRCDIR([gtkmm-utils/dialog.hh])
AC_PREREQ(2.59)

#########################################################################
#  Version and initialization
#########################################################################
[GTKMM_UTILS_MAJOR_VERSION]=GTKMM_UTILS_MAJOR_VERSION
[GTKMM_UTILS_MINOR_VERSION]=GTKMM_UTILS_MINOR_VERSION
[GTKMM_UTILS_MICRO_VERSION]=GTKMM_UTILS_MICRO_VERSION
[GTKMM_UTILS_VERSION]=GTKMM_UTILS_VERSION

popdef([GTKMM_UTILS_MAJOR_VERSION])
popdef([GTKMM_UTILS_MINOR_VERSION])
popdef([GTKMM_UTILS_MICRO_VERSION])
popdef([GTKMM_UTILS_VERSION])

GTKMM_UTILS_RELEASE="$GTKMM_UTILS_MAJOR_VERSION.$GTKMM_UTILS_MINOR_VERSION"
AC_DEFINE_UNQUOTED(GTKMM_UTILS_MAJOR_VERSION, $GTKMM_UTILS_MAJOR_VERSION, [Major version of gtkmm-utils])
AC_DEFINE_UNQUOTED(GTKMM_UTILS_MINOR_VERSION, $GTKMM_UTILS_MINOR_VERSION, [Minor version of gtkmm-utils])
AC_DEFINE_UNQUOTED(GTKMM_UTILS_MICRO_VERSION, $GTKMM_UTILS_MICRO_VERSION, [Micro version of gtkmm-utils])

AC_SUBST(GTKMM_UTILS_MAJOR_VERSION)
AC_SUBST(GTKMM_UTILS_MINOR_VERSION)
AC_SUBST(GTKMM_UTILS_MICRO_VERSION)
AC_SUBST(GTKMM_UTILS_VERSION)
AC_SUBST(GTKMM_UTILS_RELEASE)

GTKMM_UTILS_API_VERSION="1.0"
AC_SUBST(GTKMM_UTILS_API_VERSION)

# CURRENT : REVISION : AGE
LIBGTKMM_UTILS_SO_VERSION=1:0:0

AC_SUBST(LIBGTKMM_UTILS_SO_VERSION)

GTKMM_UTILS_NAME="gtkmm-utils"
GTKMM_UTILS_SUMMARY="gtkmm-utils is a library of utility functions and classes based on gtkmm"
GLIBMM_UTILS_NAME="glibmm-utils"
GLIBMM_UTILS_SUMMARY="glibmm-utils is a library of utility functions and classes based on glibmm"
GTKMM_UTILS_LICENSE="LGPL"

AC_SUBST(GTKMM_UTILS_NAME)
AC_SUBST(GTKMM_UTILS_SUMMARY)
AC_SUBST(GLIBMM_UTILS_NAME)
AC_SUBST(GLIBMM_UTILS_SUMMARY)
AC_SUBST(GTKMM_UTILS_LICENCE)

#########################################################################
# Build options
#########################################################################

# gcc visibility support
# explained in http://gcc.gnu.org/wiki/Visibility
ENABLE_GCC_SYMBOLS_VISIBILITY=yes
AC_ARG_ENABLE(symvis,
              AC_HELP_STRING([--enable-symvis=yes|no],
                             [use the gcc symbols visibility feature (gcc4).
                             default is no)]),
              ENABLE_GCC_SYMBOLS_VISIBILITY=$enableval,
              ENABLE_GCC_SYMBOLS_VISIBILITY=no)

#########################################################################
#  don't touch this
#########################################################################
GTKMM_UTILS_RELEASE=$GTKMM_UTILS_MAJOR_VERSION.$GTKMM_UTILS_MINOR_VERSION
AC_SUBST(GTKMM_UTILS_RELEASE)

AC_DEFINE_UNQUOTED(GTKMM_UTILS_MAJOR_VERSION, $GTKMM_UTILS_MAJOR_VERSION, [Major version])
AC_DEFINE_UNQUOTED(GTKMM_UTILS_MINOR_VERSION, $GTKMM_UTILS_MINOR_VERSION, [Minor version])
AC_DEFINE_UNQUOTED(GTKMM_UTILS_MICRO_VERSION, $GTKMM_UTILS_MICRO_VERSION, [Micro version])
AC_SUBST(GTKMM_UTILS_MAJOR_VERSION)
AC_SUBST(GTKMM_UTILS_MINOR_VERSION)
AC_SUBST(GTKMM_UTILS_MICRO_VERSION)

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-bzip2 dist-zip])
AM_MAINTAINER_MODE

#########################################################################
#  Environment Checks
#########################################################################

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_CONFIG_HEADERS([config.h])

# Checks for various programs
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

# Check for C compiler
AC_LANG([C])
AC_LANG([C++])
AC_ISC_POSIX

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Next four lines is a hack to prevent libtool checking for C++/F77
m4_undefine([AC_PROG_CXX])
m4_defun([AC_PROG_CXX],[])
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])

# Libtool
AC_DISABLE_STATIC
AC_ENABLE_SHARED
AC_PROG_LIBTOOL

# pkg-config
PKG_PROG_PKG_CONFIG
AC_ARG_WITH([pkgconfig-dir],
    AS_HELP_STRING([--with-pkgconfig-dir@<:@=PATH@:>@],
        [pkgconfig file destination dir]),
    [pkgconfigdir="$withval"],
    [pkgconfigdir='$(libdir)/pkgconfig'])
AC_SUBST([pkgconfigdir])

# Check for dependencies and set build libs and cflags
PKG_CHECK_MODULES([LIBGTHREAD], [gthread-2.0 >= 2.8.5])

AC_SUBST(LIBGTHREAD_LIBS)
AC_SUBST(LIBGTHREAD_CFLAGS)

PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 >= 2.12.0 sigc++-2.0])

AC_SUBST(GLIBMM_LIBS)
AC_SUBST(GLIBMM_CFLAGS)

PKG_CHECK_MODULES([GTKMM], [gtkmm-2.4 >= 2.10.0])

AC_SUBST(GTKMM_LIBS)
AC_SUBST(GTKMM_CFLAGS)

GTKMM_UTILS_LIBS="$LIBGTHREAD_LIBS $GLIBMM_LIBS $GTKMM_LIBS"
GTKMM_UTILS_CFLAGS="$LIBGTHREAD_CFLAGS $GLIBMM_CFLAGS $GTKMM_CFLAGS"

AC_SUBST(GTKMM_UTILS_LIBS)
AC_SUBST(GTKMM_UTILS_CFLAGS)

#########################################################################
# Set build options
#########################################################################

# gcc visibility support
if test x$ENABLE_GCC_SYMBOLS_VISIBILITY = xyes && test x$host_cpu != xx86_64 ; then
    AC_DEFINE(HAS_GCC_VISIBILITY_SUPPORT,1,[gcc visibility support])
    REQUIRED_FLAGS="-fvisibility=hidden -fvisibility-inlines-hidden"
else
    REQUIRED_FLAGS=""
fi

# CFLAGS, CXXFLAGS
# Set the $GTKMM_UTILS_DEVEL environment variable
# to enable additional (debug) compiler flags
CFLAGS="$CFLAGS -Wall -pedantic -std=c99"

if test  "x$GTKMM_UTILS_DEVEL" = "xon" ; then
    CXXFLAGS="$CXXFLAGS -Wall -pedantic -g -O0 -Werror -Wextra -fuse-cxa-atexit $REQUIRED_FLAGS"
else
    CXXFLAGS="$CXXFLAGS -fuse-cxa-atexit $REQUIRED_FLAGS"
fi

AC_ARG_ENABLE([documentation],
    [AS_HELP_STRING([--enable-documentation], [Whether to build the Doxygen documentation])],
    [enable_documentation="$enableval"],
    [enable_documentation="no"]
)
if test "$enable_documentation" = "yes"; then
    AC_PATH_PROG([DOXYGEN], [doxygen], AC_MSG_ERROR[Documentation build requested but doxygen not found!])

AC_CONFIG_FILES(
        docs/Makefile
        docs/Doxyfile
)
fi
AM_CONDITIONAL([GTKMM_UTILS_BUILD_DOCUMENTATION], [test "$enable_documentation" = "yes"])

GTKMM_UTILS_INSTALL_PREFIX=$prefix

AC_SUBST(GTKMM_UTILS_INSTALL_PREFIX)

#########################################################################
# Generated files
#########################################################################

AC_CONFIG_FILES([
    Makefile
    glibmm-utils/Makefile
    glibmm-utils/glibmm-utils.pc
    gtkmm-utils/Makefile
    gtkmm-utils/gtkmm-utils.pc
    examples/Makefile
])

AC_OUTPUT

cat <<EOT

=================================================================
                      gtkmm-utils: $GTKMM_UTILS_VERSION
=================================================================
            Here is the configuration of the package:

    Prefix                          : ${prefix}
    Source code location            : ${srcdir}
    C Compiler                      : ${CC}
    C++ Compiler                    : ${CXX}
    Build documentation             : ${enable_documentation}
    GTKMM_UTILS_DEVEL env variable  : ${GTKMM_UTILS_DEVEL}
    Enable symbols visibility ctrl  : ${ENABLE_GCC_SYMBOLS_VISIBILITY}
    CFLAGS                          : ${CFLAGS}
    CXXFLAGS                        : ${CXXFLAGS}
    GTKMM_UTILS_LIBS                : ${GTKMM_UTILS_LIBS}
    GTKMM_UTILS_CFLAGS              : ${GTKMM_UTILS_CFLAGS}

=================================================================

EOT
