#!/usr/bin/python
import fileinput
import re
from socket import inet_aton
import struct
import socket
from sys import stdin

originalDomains = []
blockedDomains = []
blockedHosts = {}
blockedKeywords = []
headerString = ''
payloadString = ''

#fetch all blocked domains
for line in open('./domains.txt', 'r'):
	blockedDomains.append(line[0:-2].lower())
	originalDomains.append(line[0:-2])

for line in open('./keywords.txt', 'r'):
	blockedKeywords.append(line[0:-1])


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

#print blockedHosts


def fixCaps(lowerCase):
	for original in originalDomains:
		if lowerCase == original.lower():
			return original


#TOR blocking
# main client
# torproject.org or tor.eff.org or torservers.net related IP addresses
# any url or packet with keyword torbrowser-install
# any packet with 'gettor@torproject.org'

torAddresses = ['torproject.org', 'tor.eff.org', 'torservers.net']
torIPs = []
torNetwork = ['86.59.21.38', '86.59.21.38', '171.25.193.9', \
							'171.25.193.9', '193.23.244.244', '208.83.223.34', \
						  '208.83.223.34', '128.31.0.34', '128.31.0.34', \
							'194.109.206.212', '194.109.206.212', '212.112.245.170', \
						  '212.112.245.170', '154.35.32.5', '154.35.32.5']

for line in open('./torNetwork.txt', 'r'):
	torNetwork.append(line[0:-1])


for domain in torAddresses:
	rawAdresses = socket.getaddrinfo(domain, 80)
	for entry in rawAdresses:
		ip = entry[4][0];
		match = re.match('\d+\.\d+\.\d+\.\d+', ip)
		if match:
				torIPs.append(ip)

def q5q6(header,payload):

	match = re.match('\s*(\d+\.\d+\.\d+\.\d+)\.(\d+) > (\d+\.\d+\.\d+\.\d+)\.(\d+)',header)
	if match:	
		address = match.group(3)
		keywords = re.findall('torbrowser-install', payload)
		email = re.findall('gettor@torproject.org', payload)
		
		if len(keywords) != 0 or address in torIPs:
			print '[Tor download attempt]: Method:HTTP, Address:%s' %(address)
	
		if len(email) != 0:
			print '[Tor download attempt]: Method:SMTP, Address:%s' %(address)

		if address in torNetwork:
			print '[Tor connection attempt]: Host:%s, Port:%s' %(address,match.group(4))



def q4(header, payload):
	
	match = re.match('\s*(\d+\.\d+\.\d+\.\d+)\.(\d+) > \d+\.\d+\.\d+\.\d+\.\d+', header)

	keywords = re.findall('[a-zA-Z0-9-]+', payload)

	result = []

	for item in keywords:
		for blocked in blockedKeywords:
			if blocked == item:
				result.append(blocked)

	result = list(set(result))
	result.sort()

	if len(result) > 0:
		print '[Censored Keyword - Payload]: src:%s:%s, keyword(s):' \
					 %(match.group(1),match.group(2))  + ', '.join(result)
		return True

	else: return False
		


def q3(payload):
	
# lowercase[a-z], uppercase[A-Z], numeral[0-9] and hyphen[-]

	match = re.match('.*?[H,h]ost:\.(([^\.]+\.)+)',payload)

	get = re.match('.*?GET\.([^\.]+\.)',payload)

	if match and get:
		host = match.group(1)[:-1]
		url = get.group(1)[:-1]

		keywords = re.findall('[a-zA-Z0-9-]+', payload)
		result = []

		for item in keywords:
			for blocked in blockedKeywords:
				if blocked == item:
					result.append(blocked)

		result = list(set(result))
		result.sort()

		if len(result) > 0:
			print '[Censored Keyword - URL]: URL:%s, keyword(s):' \
						 %(host+url)  + ', '.join(result)
			return True

	else: return False




def q2(header,payload):
#	print payload
	flag = False
	match = re.match('.*?[H,h]ost:\.(([^\.]+\.)+)',payload)
	if match:
		address = match.group(1)[:-1]
		match = re.match('\s*(\d+\.\d+\.\d+\.\d+)\.(\d+) > (\d+\.\d+\.\d+\.\d+)\.\d+',header)
		source = match.group(1)
		port = match.group(2)

		#print address
		if (address[0:4] == "www."):
			address = address[4:];

		if address in blockedHosts.keys():
			print '[Censored domain connection attempt]: src:%s:%s, host:%s, domain:%s' \
								%(source,port,match.group(3),fixCaps(address))
			flag = True

		for domain in blockedHosts:
			if address in blockedHosts[domain]:
					print '[Censored domain connection attempt]: src:%s:%s, host:%s, domain:%s' \
								%(source,port,address,fixCaps(domain))
					flag = True
					break

	return flag



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
						 %(fixCaps(match.group(3)[:-1]),match.group(1),match.group(2))  + ', '.join(ips)
			return True

	#check if it's a DNS request, if so don't filter further
	match = re.match(\
		'\s*(\d+\.\d+\.\d+\.\d+)\.(\d+) > \d+\.\d+\.\d+\.\d+\.\d+.*?A\? (([^\.\s]+\.)+) ',\
		header)
	if match:
		return True

	else: return False




def processPacket(header,payload):
	#print header
	#print payload
	if (header == '' and payload == ''): return

	#first check for TOR
	q5q6(header,payload)

	#then do non-TOR checks
	if not q1(header): 
		if not q2(header, payload): 
			if not q3(payload):
				if not q4(header, payload):
					"aaa"
		


#parse out the header and payload from the input, and process once have entire packet
while True:
	line = stdin.readline()
	if not line:
		break


#	print line

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
		if value >= int(length)-2:
			#print "GOT:" + payloadString
			processPacket(headerString, payloadString)
			length = 0




