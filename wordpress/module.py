from osv.modules import api

api.require('mysql')
api.require('php')
api.require('httpserver')

default = api.run('/usr/bin/mysqld --defaults-file=/etc/my.cnf --datadir=/data --user=root --innodb-use-native-aio=0 &! /php/php-cgi -b 9000 -c /php/php.ini &! /lighttpd.so -D -f /lighttpd/lighttpd.conf')
