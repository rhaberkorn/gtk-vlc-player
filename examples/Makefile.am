AM_CFLAGS = -Wall
AM_CPPFLAGS =
LDADD =

AM_CFLAGS += @LIBGTK_CFLAGS@
LDADD += @LIBGTK_LIBS@

AM_CPPFLAGS += -I@top_srcdir@/src
LDADD += @top_srcdir@/src/libgtk-vlc-player.la

check_PROGRAMS = simple
