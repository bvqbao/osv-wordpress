from osv.modules import api

default = api.run("/usr/bin/mysqld --defaults-file=/etc/my.cnf --datadir=/data --user=root --innodb-use-native-aio=0")
