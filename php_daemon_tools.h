/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_DAEMON_TOOLS_H
#define PHP_DAEMON_TOOLS_H
#define PHP_DAEMON_TOOLS_EXTNAME "daemon_tools"
#define PHP_DAEMON_TOOLS_VERSION "0.1.0"

extern zend_module_entry daemon_tools_module_entry;
#define phpext_daemon_tools_ptr &daemon_tools_module_entry

#ifdef PHP_WIN32
#	define PHP_DAEMON_TOOLS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DAEMON_TOOLS_API __attribute__ ((visibility("default")))
#else
#	define PHP_DAEMON_TOOLS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(daemon_tools);
PHP_MSHUTDOWN_FUNCTION(daemon_tools);
PHP_MINFO_FUNCTION(daemon_tools);

#ifndef HAVE_DT_CLASS_DAEMON_TOOLS_H
#	include "classes/daemon_tools.h"
#endif

#ifdef ZTS
#define DAEMON_TOOLS_G(v) TSRMG(daemon_tools_globals_id, zend_daemon_tools_globals *, v)
#else
#define DAEMON_TOOLS_G(v) (daemon_tools_globals.v)
#endif

#endif	/* PHP_DAEMON_TOOLS_H */
