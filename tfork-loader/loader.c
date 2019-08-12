#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <unistd.h>
#include "tfork.h"

void *main_ret_addr;

int main( void ) {
	main_ret_addr = __builtin_return_address(0);

	char *mysql_argv[6] = {"Command-line",
		"--defaults-file=/etc/my.cnf",
		"--datadir=/data",
		"--user=root",
		"--innodb-use-native-aio=0",
		NULL};

	printf("*** fork(): mysql ***\n");
	long pid1 = tfork();
	if ( pid1 == 0 ) {
		tfork_execve("/usr/bin/mysqld", mysql_argv, NULL);

		printf( "[%d] exiting to %p\n", getpid(), __builtin_return_address(0));

		return 0;
	}

	char *php_argv[6] = {"Command-line",
		"-b", "9000", "-c", "/php/php.ini",
		NULL};

	printf("*** fork(): php ***\n");
	long pid2 = tfork();
	if ( pid2 == 0 ) {
		tfork_execve("/php/php-cgi", php_argv, NULL);

		printf( "[%d] exiting to %p\n", getpid(), __builtin_return_address(0));

		return 0;
	}

	char *httpd_argv[5] = {"Command-line",
		"-D", "-f", "/lighttpd/lighttpd.conf",
		NULL};

	printf("*** fork(): lighttpd ***\n");
	long pid3 = tfork();
	if ( pid3 == 0 ) {
		tfork_execve("/lighttpd.so", httpd_argv, NULL);

		printf( "[%d] exiting to %p\n", getpid(), __builtin_return_address(0));

		return 0;
	}

	char *osvapi_argv[2] = {"Command-line", NULL};

	printf("*** fork(): osv api ***\n");
	long pid4 = tfork();
	if ( pid4 == 0 ) {
		tfork_execve("/libhttpserver-api.so", osvapi_argv, NULL);

		printf( "[%d] exiting to %p\n", getpid(), __builtin_return_address(0));

		return 0;
	}

	return 0;
}
