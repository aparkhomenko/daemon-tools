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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/spl/spl_exceptions.h"
#include "php_daemon_tools.h"

/* True global resources - no need for thread safety here */
static int le_daemon_tools;

zend_class_entry       * dt_daemon_tools_entry;
zend_object_handlers     dt_handlers;

/* {{{ daemon_tools_module_entry
 */
zend_module_entry daemon_tools_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_DAEMON_TOOLS_EXTNAME,
	NULL,
	PHP_MINIT(daemon_tools),
	PHP_MSHUTDOWN(daemon_tools),
	NULL,
	NULL,
	PHP_MINFO(daemon_tools),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_DAEMON_TOOLS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DAEMON_TOOLS
ZEND_GET_MODULE(daemon_tools)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(daemon_tools)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry ce;

	memcpy(&dt_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	// INIT DaemonTools
	INIT_CLASS_ENTRY(ce, "DaemonTools", dt_daemon_tools_methods);
	dt_daemon_tools_entry = zend_register_internal_class(&ce TSRMLS_CC);
	dt_daemon_tools_entry->ce_flags = ZEND_ACC_TRAIT;

#ifndef HAVE_SPL
	spl_ce_InvalidArgumentException = zend_exception_get_default(TSRMLS_C);
	spl_ce_RuntimeException			= zend_exception_get_default(TSRMLS_C);
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(daemon_tools)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(daemon_tools)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "daemon_tools support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

#ifndef HAVE_DT_CLASS_DAEMON_TOOLS
#	include "classes/daemon_tools.h"
#endif
