from math import log2
from operator import itemgetter

words = []
training = []
labels = []
testing = []

classifier = {}


def readFiles():

    global words
    global training
    global labels
    global testing

    words = open("input\\words.txt").read().splitlines() 

    with open("input\\trainData.txt") as f:
        currentDocument = 1
        wordList = []

        for line in f:

            data = line.split()

            if int(data[0]) != currentDocument:
                training.append([currentDocument, wordList, 0])
                currentDocument +=1
                wordList = []

            wordList.append(words[int(data[1])-1])


    with open("input\\trainLabel.txt") as f:      
        for line in f:
            data = int(line)
            labels.append(data)  

    for i in range(0,len(labels)-1):
        training[i][2] = labels[i]


    labels = []

    with open("input\\testData.txt") as f:
        currentDocument = 1
        wordList = []

        for line in f:

            data = line.split()

            if int(data[0]) != currentDocument:
                testing.append([currentDocument, wordList, 0])
                currentDocument +=1
                wordList = []

            wordList.append(words[int(data[1])-1])


    with open("input\\testLabel.txt") as f:      
        for line in f:
            data = int(line)
            labels.append(data)  

    for i in range(0,len(labels)-1):
        testing[i][2] = labels[i]


def train():

    global classifier

    c1 = 0
    c2 = 0

    for data in training:
        if data[2] == 1:
            c1 += 1
        else: 
            c2 +=1

    #calculate P(c=1) and P(c=2)
    classifier[1] = (c1+1)/(c1+c2+2)
    classifier[2] = (c2+1)/(c1+c2+2)


    w1 = 0
    w2 = 0
    c1TotalWords = 0
    c2TotalWords = 0


    for data in training:

        if data[2] == 1:
            c1TotalWords += len(data[1])

        if data[2] == 2:
            c2TotalWords += len(data[1])

    for word in words:

        w1 = 0
        w2 = 0

        for data in training:

            if data[2] == 1:
                if word in data[1]:
                    w1 += 1

            if data[2] == 2:
                if word in data[1]:
                    w2 += 1

        classifier[(word, 1)] = (w1+1)/(c1TotalWords+len(words))
        classifier[(word, 2)] = (w2+1)/(c2TotalWords+len(words))


def test(dataset):

    hit = 0
    miss = 0

    for data in dataset:

        p1 = classifier[1]
        p2 = classifier[2]

        guess = 0

        for word in data[1]:

            p1 *= classifier[(word, 1)]
            p2 *= classifier[(word, 2)]

            

    
        if p1 > p2:
                guess = 1
        else:
                guess = 2

        if guess == data[2]:
            hit +=1
        else:
            miss +=1


    print(hit*100/(hit+miss))




def mostDiscriminative():

    diffs = []

    for word in words:

        p1 = classifier[(word,1)]
        p2 = classifier[(word,2)]

        diffs.append((word, abs(log2(p1) - log2(p2))))


    diffs = sorted(diffs, key=itemgetter(1), reverse = True)

    print (diffs[0:11])


readFiles()

train()

test(training)
test(testing)



mostDiscriminative()



print("Hello World")