AC_INIT([page-mutter-compositor], [0.0.1])
AC_CONFIG_MACRO_DIR([m4])

LT_PREREQ([2.4.6])
LT_INIT([disable-static])
LT_LANG([C++])

PKG_PROG_PKG_CONFIG([0.22])

AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/main.cxx])

# check for C++11
AX_CXX_COMPILE_STDCXX(11, noext, mandatory)

dnl Check for libs

GLIB_GSETTINGS

PKG_CHECK_MODULES(MUTTER, [
	libmutter-1 >= 3.22.4
])
AC_SUBST(MUTTER_CFLAGS)
AC_SUBST(MUTTER_LIBS)

PKG_CHECK_MODULES(CAIRO, [
	cairo >= 1.14.6
	cairo-xlib >= 1.14.6
	cairo-xcb >= 1.14.6
	cairo-xcb-shm >= 1.14.6
	cairo-xlib-xrender >= 1.14.6
])
AC_SUBST(CAIRO_CFLAGS)
AC_SUBST(CAIRO_LIBS)

PKG_CHECK_MODULES(PANGO, pangocairo >= 0.28)
AC_SUBST(PANGO_CFLAGS)
AC_SUBST(PANGO_LIBS)

MUTTER_TYPELIB_DIR=`$PKG_CONFIG --variable=typelibdir libmutter-1`
AC_SUBST(MUTTER_TYPELIB_DIR)

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  gschemas/Makefile
  net.hzog.Shell.desktop
  ])
AC_OUTPUT
