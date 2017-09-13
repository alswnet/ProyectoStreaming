#!/usr/bin/python

import urllib2, json

AccessToken = 'xxxx'
IDStriming = 'xxxx'

dato = urllib2.urlopen('https://greap.facebook.com/' + IDStriming + '?fields=comments.limit(10).order(reverse_chronological)&access_token=' + AccessToken).read()
DatosFB = json.loads(dato)

print DatosFB

print DatosFB['comments']

if DatosFB['comments'][0]['name'] == 'jose':
	print "hola jose"
