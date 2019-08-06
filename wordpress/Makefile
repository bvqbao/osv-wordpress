SOURCE=http://download.lighttpd.net/lighttpd/releases-1.4.x/lighttpd-1.4.45.tar.xz
WP_SOURCE=https://wordpress.org/latest.tar.gz

.PHONY: module clean

SRC=upstream/lighttpd

module: usr.manifest

usr.manifest: $(SRC)/lighttpd.so wordpress
	echo '[manifest]' > usr.manifest
	echo '/lighttpd.so: $${MODULE_DIR}/$(SRC)/lighttpd.so' >> usr.manifest
	ldd $(SRC)/lighttpd.so | grep -v 'libc.so\|libpthread.so\|libdl.so\|=>\W*(' |\
		sed -n 's/ *[^ ] *\(.*\) => \(.*\) .*/\/\1: \2/p' \
		>> usr.manifest
	echo '/lighttpd/www-data/**: $${MODULE_DIR}/wordpress/**' >> usr.manifest
	echo '/lighttpd/www-data/wp-config.php: $${MODULE_DIR}/wp-config.php' >> usr.manifest
	echo '/lighttpd/www-data/info.php: $${MODULE_DIR}/info.php' >> usr.manifest
	echo '/lighttpd/lighttpd.conf: $${MODULE_DIR}/lighttpd.conf' >> usr.manifest
	echo '/var/tmp/empty: $${MODULE_DIR}/empty' >> usr.manifest

clean:
	rm -fr upstream wordpress
	rm -f upstream.tar latest.tar.gz usr.manifest patch

# Note: the touch commands below are needed after commands which create files
# "in the past", like wget and tar, and can confuse Make to rebuild a target
# which is new, just pretends to be old.
upstream.tar:
	wget -c -O $@ $(SOURCE)
	touch $@

upstream/lighttpd/Makefile.in: upstream.tar
	mkdir upstream
	tar -C upstream -xf upstream.tar
	cd upstream; ln -sf lighttpd-* lighttpd
	touch upstream/lighttpd/Makefile.in

$(SRC)/libtool-orig: $(SRC)/Makefile.in
	cd $(SRC) && patch -p1 < ../../static-build.patch && \
		spatch ../../tforkify.cocci src --ignore "src/lemon.c" > patch && patch -d src -p1 < patch && cp ../../tfork.h src && \
		autoreconf && LIGHTTPD_STATIC=yes ./configure -C --enable-static=yes --without-bzip2 --prefix=/lighttpd
	sed -i "s/tfork()/fork()/" $(SRC)/src/mod_fastcgi.c
	mv $(SRC)/libtool $(SRC)/libtool-orig

$(SRC)/libtool: $(SRC)/libtool-orig
	sed 's/^\(export_dynamic_flag_spec=.*\)"/\1 -fpie"/' $(SRC)/libtool-orig > $(SRC)/libtool

$(SRC)/lighttpd.so: $(SRC)/libtool
	make -C $(SRC) CFLAGS="-O2 -fpie -fno-stack-protector -fno-omit-frame-pointer" LDFLAGS="-pie"
	mv $(SRC)/src/lighttpd $(SRC)/lighttpd.so

wordpress:
	wget -c -O latest.tar.gz $(WP_SOURCE)
	tar -xf latest.tar.gz

.DELETE_ON_ERROR:
