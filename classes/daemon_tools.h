#ifndef HAVE_DT_CLASS_DAEMON_TOOLS_H
#define HAVE_DT_CLASS_DAEMON_TOOLS_H

PHP_METHOD(DaemonTools, fdClose);
PHP_METHOD(DaemonTools, dup);
PHP_METHOD(DaemonTools, isLocking);
PHP_METHOD(DaemonTools, lock);
PHP_METHOD(DaemonTools, unlock);

ZEND_BEGIN_ARG_INFO_EX(DaemonTools_dup, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(DaemonTools_fdClose, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(DaemonTools_isLocking, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(DaemonTools_lock, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(DaemonTools_unlock, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

extern zend_function_entry dt_daemon_tools_methods[];

#else
#	ifndef HAVE_DT_CLASS_DAEMON_TOOLS
#	define HAVE_DT_CLASS_DAEMON_TOOLS

#include <fcntl.h>

zend_function_entry dt_daemon_tools_methods[] = {
		PHP_ME(DaemonTools,  dup,       DaemonTools_dup,       ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(DaemonTools,  fdClose,   DaemonTools_fdClose,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(DaemonTools,  isLocking, DaemonTools_isLocking, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(DaemonTools,  lock,      DaemonTools_lock,      ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(DaemonTools,  unlock,    DaemonTools_unlock,    ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_FE_END
};


PHP_METHOD(DaemonTools, isLocking)
{
	zval *arg1 = NULL;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &arg1) == FAILURE) {
		zend_throw_exception(
				spl_ce_InvalidArgumentException, NULL, 0 TSRMLS_CC);
		return;
	}

	php_stream_from_zval_no_verify(stream, &arg1);

	if (stream == NULL) {
		zend_throw_exception(
				spl_ce_InvalidArgumentException, "The stream can't be null", 0 TSRMLS_CC);
		return;
	}

    int fd;

    if (SUCCESS == php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&fd, 1) && fd != -1) {
    	if (0 == lockf(fd, F_TEST, 0)) {
    		RETURN_FALSE;
    	}
    }

    RETURN_TRUE;
}
/* }}} */


PHP_METHOD(DaemonTools, lock)
{
	zval *arg1 = NULL;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &arg1) == FAILURE) {
		zend_throw_exception(
				spl_ce_InvalidArgumentException, NULL, 0 TSRMLS_CC);
		return;
	}

	php_stream_from_zval_no_verify(stream, &arg1);

	if (stream == NULL) {
		RETURN_FALSE;
	}

    int fd;

    if (SUCCESS == php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&fd, 1) && fd != -1) {

    	do {
			struct flock lock;
			lock.l_type = F_WRLCK;
			lock.l_start = 0;
			lock.l_whence = SEEK_SET;
			lock.l_len = 0;
			if (fcntl(fd, F_SETLKW, &lock) != -1) {
				RETURN_TRUE;
				break;
			}
	//		} else if (errno != EINTR || in_shutdown) {
	//			return -1;
	//		}
		} while (1);
    }

    RETURN_FALSE;
}
/* }}} */


PHP_METHOD(DaemonTools, unlock)
{
	zval *arg1 = NULL;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &arg1) == FAILURE) {
		zend_throw_exception(
				spl_ce_InvalidArgumentException, NULL, 0 TSRMLS_CC);
		return;
	}

	php_stream_from_zval_no_verify(stream, &arg1);

	if (stream == NULL) {
		RETURN_FALSE;
	}

	int fd;

	if (SUCCESS == php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&fd, 1) && fd != -1) {

		do {
	//		int orig_errno = errno;
			while (1) {
				struct flock lock;
				lock.l_type = F_UNLCK;
				lock.l_start = 0;
				lock.l_whence = SEEK_SET;
				lock.l_len = 0;
				if (fcntl(fd, F_SETLK, &lock) != -1) {
					RETURN_TRUE;
					break;
				}
	//			} else if (errno != EINTR) {
	//				return -1;
	//			}
			}
	//		errno = orig_errno;
		} while (0);

	}

	RETURN_FALSE;


}
/* }}} */

PHP_METHOD(DaemonTools, fdClose)
{
	long fd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &fd) == FAILURE) {
		return;
	}

	RETURN_LONG(close(fd));
}

PHP_METHOD(DaemonTools, dup)
{
	zval *old_handle = NULL;
	zval *new_handle = NULL;
	php_stream *old_stream;
	php_stream *new_stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &old_handle, &new_handle) == FAILURE) {
		return;
	}

	php_stream_from_zval_no_verify(old_stream, &old_handle);
	php_stream_from_zval_no_verify(new_stream, &new_handle);

	if (old_stream == NULL || new_stream == NULL) {
		RETURN_FALSE;
	}

	int old_fd;
	int new_fd;

	if (SUCCESS == php_stream_cast(old_stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&old_fd, 1) && old_fd != -1
			&& SUCCESS == php_stream_cast(new_stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&new_fd, 1) && new_fd != -1) {
		dup2(old_fd, new_fd);
	}

	RETURN_FALSE;
}

#	endif
#endif
