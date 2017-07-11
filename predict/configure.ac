#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([predict], [0.9.0], [akhileshmaurya494@gmail.com])
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([1.10 no-define foreign])
AC_LANG(C++)

AC_PROG_MAKE_SET
AC_HEADER_STDC

AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_CPLUSPLUS
AC_PROG_INSTALL
AM_PROG_LIBTOOL

AC_CHECK_LIB('glib-2.0')
AC_CHECK_LIB('stdc++')
AC_CHECK_LIB('z')

AC_PROG_CC

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])

AM_CONDITIONAL(CENTOS64, test -d /usr/lib64/glib-2.0/include )
AM_CONDITIONAL(CENTOS, test -d /usr/lib/glib-2.0/include )
AM_CONDITIONAL(DEBIAN64, test -d /usr/lib/x86_64-linux-gnu/glib-2.0/include  )
AM_CONDITIONAL(DEBIAN, test -d /usr/lib/i386-linux-gnu/glib-2.0/include )
AM_SILENT_RULES([yes])
AC_OUTPUT
