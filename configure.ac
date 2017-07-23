AC_INIT([page-mutter-compositor], [0.0.1])
AC_CONFIG_MACRO_DIR([m4])

LT_PREREQ([2.4.6])
LT_INIT([disable-static])
LT_LANG([C++])

AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/main.cxx])

# check for C++11
AX_CXX_COMPILE_STDCXX(11, noext, mandatory)

dnl Check for libs

GLIB_GSETTINGS

# Package requirements
PKG_CHECK_MODULES([GLIB], [glib-2.0])
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

PKG_CHECK_MODULES(MUTTER, [
	libmutter >= 3.22.4
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

PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.0.0)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

PKG_CHECK_MODULES(PANGO, pangocairo >= 0.28)
AC_SUBST(PANGO_CFLAGS)
AC_SUBST(PANGO_LIBS)

PKG_CHECK_MODULES(CLUTTER, [
	xkbcommon
	xkbcommon-x11
	x11-xcb
	xcb
	gdk-3.0 >= 3.20.9
	cogl-1.0 >= 1.22.1
	clutter-1.0 >= 1.26.0
	clutter-wayland-compositor-1.0 >= 1.26.0
	clutter-wayland-1.0 >= 1.26.0
	clutter-x11-1.0 >= 1.26.0
	clutter-egl-1.0 >= 1.26.0
	clutter-cogl-1.0 >= 1.26.0
	clutter-gdk-1.0 >= 1.26.0
])

AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  ])
AC_OUTPUT
