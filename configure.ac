#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.65)
AC_INIT([GTK VLC Player Widget], [1.0],
	[robin.haberkorn@googlemail.com],
	[gtk-vlc-player],
	[https://github.com/rhaberkorn/gtk-vlc-player])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR(src/gtk-vlc-player.c)
AC_CONFIG_HEADER(config.h)

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# GtkVlcPlayer data directory
gtk_vlc_player_datadir=$datarootdir/$PACKAGE_TARNAME
AC_SUBST(gtk_vlc_player_datadir)

#
# Checks for programs.
#
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_CC
AC_PROG_CC_C99
if [[ $ac_cv_prog_cc_c99 = no ]]; then
	AC_MSG_ERROR([C compiler does not support C99 mode!])
fi
AM_PROG_CC_C_O

AC_CHECK_PROG(GLIB_GENMARSHAL, glib-genmarshal, glib-genmarshal)
if [[ x$GLIB_GENMARSHAL = x ]]; then
	AC_MSG_ERROR([glib-genmarshal not found!])
fi

# not necessarily required (depends on options)
AC_CHECK_PROG(DOXYGEN, doxygen, doxygen)

#
# Checks for libraries.
#
PKG_CHECK_MODULES(LIBGTK, [gtk+-2.0 gthread-2.0])

PKG_CHECK_EXISTS([gladeui-1.0],
		 [glade3_catalogsdir=`$PKG_CONFIG --variable=catalogdir gladeui-1.0`])
if [[ x$glade3_catalogsdir = x ]]; then
	AC_MSG_WARN([Glade-3 catalog directory not found, installing widget catalog into data directory!])
fi
# TODO: with-option to overwrite the catalogsdir
catalogsdir=${glade3_catalogsdir:-$gtk_vlc_player_datadir/catalogs}
AC_SUBST(catalogsdir)

# FIXME: further restrict libvlc version
PKG_CHECK_MODULES(LIBVLC, [libvlc >= 1.1.10 vlc-plugin])

#
# Checks for header files.
#
AC_HEADER_STDC

case $host in
*-*-mingw*)
	AC_CHECK_HEADERS([windows.h], , [
		AC_MSG_ERROR([Missing Windows headers!])
	])
	AC_CHECK_HEADERS([winuser.h], , [
		AC_MSG_ERROR([Missing Windows headers!])
	], [
		#include <windows.h>
	])
	;;
esac

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

#
# Config options
#
AC_ARG_ENABLE(doxygen-doc,
	AS_HELP_STRING([--enable-doxygen-doc],
		       [Generate Doxygen documentation [default=no]]),
	[doxygen_doc=$enableval], [doxygen_doc=no])
if [[ $doxygen_doc = yes -a x$DOXYGEN = x ]]; then
        AC_MSG_ERROR([Enabled generating Doxygen documentation, but Doxygen not found! Try --disable-doxygen-doc.])
fi
AM_CONDITIONAL(BUILD_DOXYGEN, [test $doxygen_doc = yes])

AC_ARG_ENABLE(doxygen-extract-private,
	AS_HELP_STRING([--enable-doxygen-extract-private],
		       [Include private and static members in Doxygen documentation [default=no]]),
[
	case $enableval in
	yes)	DOXYGEN_EXTRACT_PRIVATE=YES ;;
	*)	DOXYGEN_EXTRACT_PRIVATE=NO ;;
	esac
], [
	DOXYGEN_EXTRACT_PRIVATE=NO
])
AC_SUBST(DOXYGEN_EXTRACT_PRIVATE)

#
# Some minor configuration options.
# Can only be changed here in the Autoconf script
#
AC_DEFINE(GTK_VLC_PLAYER_TIME_ADJ_STEP,	[1000.],	[VLC Player time adjustment step increment])
AC_DEFINE(GTK_VLC_PLAYER_TIME_ADJ_PAGE,	[30000.],	[VLC Player time adjustment page increment])

AC_DEFINE(GTK_VLC_PLAYER_VOL_ADJ_STEP,	[0.02],		[VLC Player volume adjustment step increment])
AC_DEFINE(GTK_VLC_PLAYER_VOL_ADJ_PAGE,	[0.],		[VLC Player volume adjustment page increment])

AC_CONFIG_FILES([Makefile src/Makefile examples/Makefile])
AC_CONFIG_FILES([doc/Makefile doc/Doxyfile])

AC_OUTPUT
