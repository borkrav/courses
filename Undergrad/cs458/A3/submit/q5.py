#!/usr/bin/python

import sqlite3, csv, os, sys


conn = sqlite3.connect(':memory:')

cur = conn.cursor()

mode = sys.argv[1]


# create polling table
cur.execute('''CREATE TABLE poll
	           (name text, phone text, dmob text, 
							yob text, gender text, postal text)''')

# fill polling table
inputFile = csv.reader(open('./Poll-Data.csv', 'r'), delimiter=',')

for row in inputFile:

	dateMonth = row[2][:-5]
	year = row[2][-4:]

	row[2] = dateMonth
	row.insert(3, year)

	cur.execute('''INSERT INTO poll 
								(name, phone, dmob, yob, gender, postal)
								VALUES (?, ?, ?, ?, ?, ?);''', row) 


#create disease table
cur.execute('''CREATE TABLE disease
	           (yob text, gender text, postal text, disease text)''')

#fill disease table
inputFile = csv.reader(open('./Disease-Records.csv', 'r'), delimiter=',')

for row in inputFile:

	cur.execute('''INSERT INTO disease 
								(yob, gender, postal, disease)
								VALUES (?, ?, ?, ?);''', row[3:]) 



if mode == '1':

	#PART A
	cur.execute('''
							SELECT *
							FROM

							(SELECT poll.name, poll.phone, poll.yob, poll.gender, 										poll.postal, disease.disease

							FROM poll 
							INNER JOIN disease
							ON poll.yob = disease.yob 
							AND poll.gender = disease.gender
							AND poll.postal = disease.postal
							GROUP BY poll.name
							HAVING COUNT(*) = 1)

							GROUP BY yob,gender,postal
							HAVING COUNT(*) = 1
							''')


	outputFile = csv.writer(open("./big.csv", "wb"), lineterminator='\n')
	outputFile.writerows(cur)
	del outputFile

	os.system('cat big.csv')

	os.remove('big.csv')




if mode == '2':

	#PART B


	#create query table
	cur.execute('''CREATE TABLE query
		           (name text, phone text, yob text, 
								gender text, postal text, disease text)''')

	#fill query table
	inputFile = csv.reader(open('./Queries.csv', 'r'), delimiter=',')

	for row in inputFile:

		cur.execute('''INSERT INTO query 
									(name, phone, yob, gender, postal, disease)
									VALUES (?, ?, ?, ?, ?, ?);''', row) 


	total = []
	match = []
	names = []

	cur.execute('''
							SELECT query.name, COUNT(*)
							FROM query
							INNER JOIN disease
							ON query.yob = disease.yob
							AND query.gender = disease.gender
							AND query.postal = disease.postal
							GROUP BY query.name
							''')

	for row in cur:
		total.append(row[0])
		total.append(row[1])

	cur.execute('''
							SELECT query.name, COUNT(*)
							FROM query
							INNER JOIN disease
							ON query.yob = disease.yob
							AND query.gender = disease.gender
							AND query.postal = disease.postal
							AND query.disease = disease.disease
							GROUP BY query.name
							''')

	for row in cur:
		match.append(row[0])
		match.append(row[1])


	cur.execute ('''
							 SELECT name
							 FROM QUERY
							 ''')


	for row in cur:
		names.append(row[0])

	outputFile = open('./Query-Probs.txt', 'w')
	
	for name in names:
		if name in total:
			outputFile.write('%.2f' % (float(match[total.index(name)+1]) \
										 / total[total.index(name)+1]) + '\n')
	
		else:
			outputFile.write('%.2f' % 0.00 + '\n')


	del outputFile
	
	os.system('cat Query-Probs.txt')

	os.remove('Query-Probs.txt')



#standard SQL exit
conn.commit()
conn.close()
