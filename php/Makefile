ROOT=${CURDIR}
PCRE_SOURCE=https://ftp.pcre.org/pub/pcre/pcre-8.42.tar.gz
ZLIB_SOURCE=https://zlib.net/fossils/zlib-1.2.3.tar.gz
XML2_SOURCE=ftp://xmlsoft.org/libxml2/libxml2-2.9.9.tar.gz
PHP_SOURCE=http://fr.php.net/get/php-7.1.28.tar.gz/from/this/mirror

.PHONY: module clean

SRC=php-7.1.28

module: usr.manifest

usr.manifest: $(SRC)/sapi/cgi/php-cgi
	echo '[manifest]' > usr.manifest
	echo '/php/php-cgi: $${MODULE_DIR}/php-7.1.28/sapi/cgi/php-cgi' >> usr.manifest
	echo '/php/php.ini: $${MODULE_DIR}/php.ini' >> usr.manifest
	echo '/php/php_errors.log: $${MODULE_DIR}/php_errors.log' >> usr.manifest
	echo '/usr/lib/libxml2.so.2: $${MODULE_DIR}/install/usr/local/libxml2/lib/libxml2.so.2' >> usr.manifest

clean:
	rm -f usr.manifest *.tar.gz
	rm -rf libxml2-2.9.9 pcre-8.42 zlib-1.2.3 php-7.1.28 install

$(SRC)/Makefile:
	wget $(PCRE_SOURCE)
	tar -zxf pcre-8.42.tar.gz
	cd pcre-8.42 && CFLAGS='-fPIC -fno-stack-protector' ./configure --prefix=$(ROOT)/install/usr/local/pcre
	make -C pcre-8.42 install  -j `nproc`
	wget $(ZLIB_SOURCE)
	tar -zxf zlib-1.2.3.tar.gz
	cd zlib-1.2.3 && CFLAGS='-fPIC -fno-stack-protector' ./configure --prefix=$(ROOT)/install/usr/local/zlib
	make -C zlib-1.2.3 install -j `nproc`
	wget $(XML2_SOURCE)
	tar -zxf libxml2-2.9.9.tar.gz
	cd libxml2-2.9.9 && CFLAGS='-fPIC -fno-stack-protector' ./configure --without-python --prefix=$(ROOT)/install/usr/local/libxml2
	make -C libxml2-2.9.9 install
	wget -O php-7.1.28.tar.gz $(PHP_SOURCE)
	tar -zxf php-7.1.28.tar.gz
	cd php-7.1.28; patch -p1 < ../osv.patch && CFLAGS='-fPIC -fno-stack-protector' LDFLAGS='-pie' ./configure --enable-fastcgi --disable-phar --with-mysqli -with-pdo-mysql --with-libxml-dir=$(ROOT)/install/usr/local/libxml2 --with-pcre-dir=$(ROOT)/install/usr/local/pcre --with-zlib-dir=$(ROOT)/install/usr/local/zlib
	sed -i "s/HAVE_MREMAP 1/HAVE_MREMAP 0/" ./php-7.1.28/ext/sqlite3/libsqlite/sqlite3.c
	sed -i "s/fvisibility=hidden/fvisibility=default/" ./php-7.1.28/Makefile

$(SRC)/sapi/cgi/php-cgi: $(SRC)/Makefile
	cd php-7.1.28 && make -j `nproc`

.DELETE_ON_ERROR:
