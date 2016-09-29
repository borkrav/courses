import csv, random
from math import exp, fsum

testData = []
trainData = []



def readData(type):

    data = []
    labels = []
    with open('input\\'+type+'Data.csv', 'r') as dataFile:
        dataReader = csv.reader(dataFile)
        for row in dataReader:

            intRow = [int(s) for s in row]
            data.append(intRow)


    with open('input\\'+type+'Labels.csv', 'r') as labelFile:
        labelReader = csv.reader(labelFile)
        for row in labelReader:

            labels.append(int(row[0]))

    return [(data[i], labels[i]) for i in range(0,len(data))]

def q3Train(dataset):

    numWeights = len(dataset[0][0])
    done = False
    iteration = 0

    #initialize weights to zero
    weights = [0 for i in range(numWeights)]

    while (not done):
        print (iteration)
        iteration += 1

        correct = len(dataset)
        done = True


        for data in dataset:
            a = 0
            y = 0
            result = 0

            #w transpose x
            for i in range(numWeights):
                result += weights[i] * data[0][i]

            #fstep
            if result  > 0 :
                a = 1
            else:
                a = 0
            

        
            #y
            if data[1] == 5:
                y = 0
            elif data[1] == 6:
                y = 1

            #correct the weights
            for i in range(numWeights):
                weights[i] = weights[i] + (y-a)*data[0][i]

            #if anything is not classified, not done
            if y != a:
                done = False
                correct -=1


    return weights      


def q3Test(weights, dataset):

    numWeights = len(dataset[0][0])
    total = len(dataset)
    hits = 0

    for data in dataset:

        result = 0
        a = 0
        y = 0

        #w transpose x
        for i in range(numWeights):
            result += weights[i] * data[0][i]

        #fstep
        if result  > 0 :
            a = 1
        else:
            a = 0

        if data[1] == 5:
            y = 0
        elif data[1] == 6:
            y = 1

        if y == a:
            hits +=1

    print (hits/total)
            

def sigmoid(input):
    return 1 / (1 + exp(-input))

def gPrime(input):
    return (1-sigmoid(input))*(sigmoid(input))

def q4Train(dataset, hiddenNodes, alpha):

    numInputs = len(dataset[0][0])

    #j = number of hidden nodes
    #k = number of input nodes (64)

    # [j][k]
    hiddenWeights = []
    # [j]
    outputWeights = []

    #initialize weights
    for j in range(hiddenNodes):
        weights = []
        for i in range(numInputs+1):
            weights.append(random.uniform(-0.5, 0.5))

        hiddenWeights.append(weights)

    for i in range(hiddenNodes+1):
        outputWeights.append(random.uniform(-0.5, 0.5))


    for iteration in range(1000):    

        hits = 0
        output = 0
        target = 0

        for example in dataset:
        
            
            classification = 0
            target = example[1]

            hlOutput = []
            hlInput = []

            for node in range(hiddenNodes):
                sum = 0
                for i in range(numInputs):
                    sum += example[0][i] * hiddenWeights[node][i]
            
                #add bias
                sum+=hiddenWeights[node][numInputs]

                hlInput.append(sum)
                hlOutput.append(sigmoid(sum))


            sum = 0
            for node in range(hiddenNodes):
                sum += hlOutput[node] *outputWeights[node]

            #add bias
            sum += outputWeights[hiddenNodes]

            output = sigmoid(sum)


            if output > 0.5:
                classification = 1
            elif output <= 0.5:
                classification = 0

            if target == 5:
                target = 0
            elif target == 6:
                target = 1

            if target == classification:
                hits+=1
 


            error = gPrime(fsum(hlOutput))*(target-output)

        
            for i in range(hiddenNodes):
            
                hError = gPrime(hlInput[i]) * error * fsum(outputWeights[0:hiddenNodes])

                for j in range(numInputs):
                    hiddenWeights[i][j] += alpha*hError * example[0][j]

                hiddenWeights[i][numInputs] += alpha*hError*1


            for i in range(hiddenNodes):
                outputWeights[i] += alpha*error*hlOutput[i]

            outputWeights[hiddenNodes] += alpha*error*1



        print(iteration)
        print("Percentage correct: " + str(hits / len(dataset)))
        print(output)
        print(target)




    return [hiddenWeights, outputWeights]


def q4Test(weights, dataset):

    numInputs = len(dataset[0][0])


    total = len(dataset)
    hits = 0

    hiddenWeights = weights[0]
    # [j]
    outputWeights = weights[1]

    hiddenNodes = len(outputWeights)-1

    for example in dataset:
        
        output = 0
        classification = 0
        target = example[1]

        hlOutput = []

        for node in range(hiddenNodes):
            sum = 0
            for i in range(numInputs):
                sum += example[0][i] * hiddenWeights[node][i]
            
            #add bias
            sum+=hiddenWeights[node][numInputs]

            hlOutput.append(sigmoid(sum))


        sum = 0
        for node in range(hiddenNodes):
            sum += hlOutput[node] *outputWeights[node]

        #add bias
        sum += outputWeights[hiddenNodes]

        output = sigmoid(sum)


        if output > 0.5:
            classification = 1
        elif output <= 0.5:
            classification = 0

        if target == 5:
            target = 0
        elif target == 6:
            target = 1

        if target == classification:
            hits+=1


    f = open("output\\result.txt", 'a')
    f.write(str(hiddenNodes) + "\n")
    f.write(str(hits/total) + "\n")

    print(hiddenNodes)
    print(str(hits/total))








trainData = readData('train')
testData = readData('test')

#weights = q3Train(trainData)
#print (weights)
#q3Test(weights, trainData)
#q3Test(weights, testData)


for i in range(5,16):
   
    weights = q4Train(trainData, i, 0.001)

    q4Test(weights, trainData)
    q4Test(weights, testData)

