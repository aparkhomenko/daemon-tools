dnl $Id$
dnl config.m4 for extension daemon_tools

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(daemon_tools, for daemon_tools support,
dnl Make sure that the comment is aligned:
dnl [  --with-daemon_tools             Include daemon_tools support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(daemon_tools, whether to enable daemon_tools support,
dnl Make sure that the comment is aligned:
[  --enable-daemon_tools           Enable daemon_tools support])

if test "$PHP_DAEMON_TOOLS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-daemon_tools -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/daemon_tools.h"  # you most likely want to change this
  dnl if test -r $PHP_DAEMON_TOOLS/$SEARCH_FOR; then # path given as parameter
  dnl   DAEMON_TOOLS_DIR=$PHP_DAEMON_TOOLS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for daemon_tools files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DAEMON_TOOLS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DAEMON_TOOLS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the daemon_tools distribution])
  dnl fi

  dnl # --with-daemon_tools -> add include path
  dnl PHP_ADD_INCLUDE($DAEMON_TOOLS_DIR/include)

  dnl # --with-daemon_tools -> check for lib and symbol presence
  dnl LIBNAME=daemon_tools # you may want to change this
  dnl LIBSYMBOL=daemon_tools # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DAEMON_TOOLS_DIR/lib, DAEMON_TOOLS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DAEMON_TOOLSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong daemon_tools lib version or lib not found])
  dnl ],[
  dnl   -L$DAEMON_TOOLS_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DAEMON_TOOLS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(daemon_tools, daemon_tools.c, $ext_shared)
fi
