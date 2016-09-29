#!/usr/bin/python
import fileinput
import re
from socket import inet_aton
import struct
import socket

blockedDomains = []
blockedHosts = {}
headerString = ''
payloadString = ''

#fetch all blocked domains
for line in open('./input/domains.txt', 'r'):
	blockedDomains.append(line[0:-2].lower())


#resolve all blocked domains to their hosts
for domain in blockedDomains:
	rawAdresses = socket.getaddrinfo(domain, 80)
	for entry in rawAdresses:
		ip = entry[4][0];
		match = re.match('\d+\.\d+\.\d+\.\d+', ip)

		if match:
			if domain in blockedHosts:
				blockedHosts[domain].append(ip)
			else:
				blockedHosts[domain] = [ip]

for domain in blockedDomains:
	blockedHosts[domain] = list(set(blockedHosts[domain]))

print blockedHosts

def q2(header,payload):

	match = re.match('.*?[H,h]ost:\.(([^\.]+\.)+)',payload)
	if match:
		address = match.group(1)[:-1]
		match = re.match('\s*(\d+\.\d+\.\d+\.\d+)\.\d+ > (\d+\.\d+\.\d+\.\d+)\.\d+',header)
		source = match.group(1)

		#print address
		if (address[0:4] == "www."):
			address = address[4:];

		if address in blockedHosts.keys():
			print '[Censored domain connection attempt]: src:%s, host:%s, domain:%s' \
								%(source,match.group(2),address)

		for domain in blockedHosts:
			if address in blockedHosts[domain]:
					print '[Censored domain connection attempt]: src:%s host:%s, domain:%s' \
								%(source,address,domain)
					break





def q1(header):
	###Known censored domains###
	#does the string match a DNS reply format?
	#xxx.xxx.xxx.xxx.xxxxxx > xxx.xxx.xxx.xxx.xxxxxx ... q: A? (xxx.xxx.xxx.......).
	match = re.match(\
		'\s*(\d+\.\d+\.\d+\.\d+)\.(\d+) > \d+\.\d+\.\d+\.\d+\.\d+.*?q: A\? (([^\.\s]+\.)+) ',\
		header)
	
	if match:
		if match.group(3)[:-1] in blockedDomains:
			
			#grabs everything before nameservers (if any are returned)
			ns = re.match('.*?ns', header)

			if ns:
				relevantString = ns.group()
			else:
				relevantString = header

			ips = re.findall('A (\d+\.\d+\.\d+\.\d+)', relevantString)

			ips = sorted(ips, key=lambda ip: struct.unpack('!L', inet_aton(ip))[0])
			
			print '[Censored domain name lookup]: domain:%s, src:%s:%s, IP(s):' \
						 %(match.group(3)[:-1],match.group(1),match.group(2))  + ', '.join(ips)
			return True
	else: return False




def processPacket(header,payload):
	#print header
	#print payload
	if (header == '' and payload == ''): return
	q1(header)
	q2(header, payload)
		

#parse out the header and payload from the input, and process once have entire packet
for line in fileinput.input():
	#print line
	ts = re.match('\d+:\d+:\d+.\d+.*length (\d+)', line)
	header = re.match('\s*\d+\.\d+\.\d+\.\d+\.\d+ > \d+\.\d+\.\d+\.\d+\.\d+', line)
	payload = re.match('\s*(0x.*?):', line)

	if ts:
		length = ts.group(1)
		headerString = ''
		payloadString = ''
	if header:
		headerString = line
	if payload:
		payloadString += line[51:-1]
		value = int(payload.group(1), 0)
		if value >= int(length):
			#print "GOT:" + payloadString
			processPacket(headerString, payloadString)
			length = 0




