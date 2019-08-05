from osv.modules import api

default = api.run('PHP_FCGI_CHILDREN=0 /php/php-cgi -b 9000 -c /php/php.ini -C')
