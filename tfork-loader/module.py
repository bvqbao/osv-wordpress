from osv.modules import api

api.require('wordpress')

default = api.run("/loader")
