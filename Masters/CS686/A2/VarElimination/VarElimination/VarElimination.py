def printFactor(factor):

    print (' ', factor[0])

    print ('\n')

    for item in factor[1]:
           
        for variable in item:
            if '~' not in variable:
                print ('  ', variable, end=' ')
            else:
                print (' ', variable, end=' ')

        print (' ', round(factor[1][item],6))


    print ('\n')


def restrict(factor,variable,value):
    
    fn = factor[0].copy()
    if len(fn) > 1 : fn.remove(variable)

    newFactor = {}

    for key in factor[1]:
       
        if value in key:
            newKey = list(key)
            if len(key) > 1 : newKey.remove(value)
            newFactor[tuple(newKey)] = factor[1][key]
    
    return [fn, newFactor]


def multiply(factor1,factor2):

    fn = list(set(factor2[0]).union(set(factor1[0])))

    common = list(set(factor2[0]) & (set(factor1[0])))

    newFactor = {}



    #if either factor is just a constant, multiply the other by that constant

    if len(factor1[1].values()) == 1 and len(factor2[1].values()) == 1:
        newFactor[('')] = next (iter (factor2[1].values())) * next (iter (factor1[1].values()))

    elif len(factor1[1].values()) == 1 and len(factor2[1].values()) > 1:
        for key in factor2[1]:
            newFactor[tuple(key)] = factor2[1][key] * next (iter (factor1[1].values()))

    elif len(factor2[1].values()) == 1 and len(factor1[1].values()) > 1:
        for key in factor1[1]:
            newFactor[tuple(key)] = factor1[1][key] * next (iter (factor2[1].values()))

    elif len(factor1[1].values()) == 0:
        newFactor = factor2[:]
        return newFactor 

    elif len(factor2[1].values()) == 0:
        newFactor = factor1[:]
        return newFactor 


    else:

        for key1 in factor1[1]:
            for key2 in factor2[1]:
                if len(set(set(key1) & set(key2))) == len(common):
                    newKey = (set(key1).union(set(key2)))
                    newFactor[tuple(newKey)] = factor1[1][key1] * factor2[1][key2]

    return [fn, newFactor]      


def sumout(factor,variable):
    fn = factor[0].copy()
    fn.remove(variable)
    newFactor = {}

    
    for key1 in factor[1]:
        for key2 in factor[1]:

            intersect = set(key1) & set(key2)

            if len(intersect) == len(fn) and variable.lower() not in intersect and str('~' + variable.lower()) not in intersect:
                newFactor[tuple(set(key1) & set(key2))] = factor[1][key1] + factor[1][key2]

    return [fn, newFactor]


def normalize(factor):

    fn = factor[0]

    newFactor = {}

    sum = 0

    for key in factor[1]:
        sum += factor[1][key]

    for key in factor[1]:
        newFactor[key] = factor[1][key]/sum

    return [fn, newFactor]


def inference(factorList, queryVariables, orderedListOfHiddenVariables, evidenceList):
    
    if len(evidenceList) != 0:

        print("FACTORS: ", end = '')
        for factor in factorList:
            print (factor[0], end='')

        print('')

        restrictedFactors = []
        oldFactors = []

        for evidence in evidenceList:

            restrictedFactors = []
            oldFactors = []

            testString = evidence.replace('~', '')
            for factor in factorList:
                if testString.upper() in factor[0]:
                    
                    print("RESTRICTING", factor[0], testString.upper(), '=', evidence)

                    restrictedFactor = restrict(factor, testString.upper(), evidence)
                    oldFactors.append(factor)
                    restrictedFactors.append(restrictedFactor)

                    printFactor(restrictedFactor)


            for factor in restrictedFactors:
                factorList.append(factor)
            for factor in oldFactors:
                factorList.remove(factor)   


    for variable in orderedListOfHiddenVariables:

        #multiply all factors that contain variable, remove factor list
        #sumout variable from resulting factor, add to factor list
        #print factor that's added

        toMult = []
        toMultList = []

        for factor in factorList:
            if variable in factor[0]:
                toMult.append(factor)
                toMultList.append(factor[0])

        if len(toMult) != 0 and variable != queryVariables:
            

            print("FACTORS: ", end = '')
            for factor in factorList:
                print (factor[0], end='')
            print('')
            print('')


            multResult = toMult[0]
            factorList.remove(toMult[0])
        
            for i in range (1, len(toMult)):
                multResult = multiply(multResult, toMult[i])
                factorList.remove(toMult[i])
        
            if len(toMult) > 1:
                print("PRODUCT OF ",  " ".join(str(x) for x in toMultList))
                print("")
                printFactor(multResult)    

            sumoutResult = sumout(multResult, variable)

            print("SUMMED OUT " + variable)
            print("")

            #if (len(sumoutResult[1]) != 0): 
            printFactor(sumoutResult)
            factorList.append(sumoutResult)

        #else:
        #    print("EMPTY FACTOR")
        #    print("")
            


  #  for factor in factorList:
  #      if len(factor[0]) == 0:
  #          factorList.remove(factor)



    print("REMAINING FACTORS: ", end = '')
    for factor in factorList:
        print (factor[0], end='')
    print("")
    print('')


    if len(factorList) > 1:

        toMult = []
        toMultList = []


        for factor in factorList:
            toMult.append(factor)
            toMultList.append(factor[0])


        multResult = toMult[0]
        factorList.remove(toMult[0])


        for i in range (1, len(toMult)):
            multResult = multiply(multResult, toMult[i])
            factorList.remove(toMult[i])


        if len(toMult) > 1:
            print("PRODUCT OF ",  " ".join(str(x) for x in toMultList))
            print("")
            printFactor(multResult)    

        factorList.append(multResult)



    print ("NORMALIZED RESULT")
    print("")

    resultFactor = normalize(factorList[0])
    printFactor(resultFactor)    
       
    return resultFactor






#factorAB = [['A','B'], {('a','b') : 0.9, ('a', '~b') : 0.1, ('~a','b') : 0.4, ('~a', '~b') : 0.6}]
#factorBC = [['B','C'], {('b','c') : 0.7, ('b', '~c') : 0.3, ('~b','c') : 0.8, ('~b', '~c') : 0.2}]

fA = [['A'], {('a',) : 0.9 , ('~a',) : 0.1}]
fAB = [['A','B'], {('a','b') : 0.9, ('a', '~b') : 0.1, ('~a','b') : 0.4, ('~a', '~b') : 0.6}]
fBC = [['B','C'], {('b','c') : 0.7, ('b', '~c') : 0.3, ('~b','c') : 0.2, ('~b', '~c') : 0.8}]


#result = inference([fA, fAB, fBC], 'B', ['A', 'B', 'C'], ['a','b'])

cloudy = [['C'], {('c',) : 0.5 , ('~c',) : 0.5}]
sprinkler = [['C','S'], {('c','s') : 0.1, ('c', '~s') : 0.9, ('~c','s') : 0.5, ('~c', '~s') : 0.5}]
rain = [['C','R'], {('c','r') : 0.8, ('c', '~r') : 0.2, ('~c','r') : 0.2, ('~c', '~r') : 0.8}]
wetgrass = [['S','R','W'], {('s','r','w') : 0.99, ('s','r','~w') : 0.01, ('s','~r','w') : 0.9, ('s','~r','~w') : 0.1 , ('~s','r','w') : 0.9, ('~s','r','~w') : 0.1, ('~s','~r','w') : 0.0, ('~s','~r','~w') : 1.0}]

#result = inference([cloudy, sprinkler, rain, wetgrass], 'R', ['C', 'S', 'R', 'W'], ['w', 's', 'c'])


fA = [['A'], {('a',) : 0.9 , ('~a',) : 0.1}]
fB = [['B'], {('b',) : 0.5 , ('~b',) : 0.5}]

result = multiply(fA, fB)
#printFactor(result)


lemon = [['L'],{('l',) : 0.5, 
                ('~l',) : 0.5}]

report = [['L', 'I', 'G', 'B', 'N'], {('l', 'i', 'g', '~b', '~n') : 0.2, ('l', 'i', '~g', 'b', '~n') : 0.8, ('l', 'i', '~g', '~b', 'n') : 0.0, 
                                      ('~l', 'i', 'g', '~b', '~n') : 0.9, ('~l', 'i', '~g', 'b', '~n') : 0.1, ('~l', 'i', '~g', '~b', 'n') : 0.0,
                                      ('l', '~i', 'g', '~b', '~n') : 0.0, ('l', '~i', '~g', 'b', '~n') : 0.0, ('l', '~i', '~g', '~b', 'n') : 1.0,
                                      ('~l', '~i', 'g', '~b', '~n') : 0.0, ('~l', '~i', '~g', 'b', '~n') : 0.0, ('~l', '~i', '~g', '~b', 'n') : 1.0}]

utility = [['P', 'L', 'I'],{('p', 'l', 'i') : -650, ('p', 'l', '~i'): -600,
                            ('p', '~l', 'i') : 950, ('p', '~l', '~i'): 1000,
                            ('~p', 'l', 'i') : -350, ('~p', 'l', '~i'): -300,
                            ('~p', '~l', 'i') : -350, ('~p', '~l', '~i'): -300}]

#result = inference([lemon, report, utility], 'P', ['L'], ['~i', 'n'])





trav = [['T'],{('t',) :0.05, ('~t',) :0.95 }]

fraud = [['F','T'], {('f','t') : 0.01, ('~f', 't') : 0.99, 
                     ('f','~t') : 0.004, ('~f', '~t') : 0.996}]

fp =  [['P', 'F', 'T'],{('p', 'f', '~t') : 0.10, ('~p', 'f', '~t'): 0.90,
                        ('p', '~f', '~t') : 0.01, ('~p', '~f', '~t'): 0.99,
                        ('p', 'f', 't') : 0.009, ('~p', 'f', 't'): 0.001,
                        ('p', '~f', 't') : 0.891, ('~p', '~f', 't'): 0.099}]

oc = [['O'],{('o',) :0.75, ('~o',) :0.25 }]

it =  [['I', 'F', 'O'],{('i', '~f', 'o') : 0.01, ('i', 'f', 'o'): 0.02,
                        ('~i', '~f', 'o') : 0.99, ('~i', 'f', 'o'): 0.98,
                        ('i', '~f', '~o') : 0.001, ('i', 'f', '~o'): 0.011,
                        ('~i', '~f', '~o') : 0.999, ('~i', 'f', '~o'): 0.989}]

crp = [['C','O'], {('c','o') : 0.10, ('c', '~o') : 0.001, 
                   ('~c','o') : 0.90, ('~c', '~o') : 0.999}]


u = [['F','B'], {('f','b') : -5, ('~f', 'b') : -10, 
                 ('f','~b') : -1000, ('~f', '~b') : 5}]


#result = inference([trav, fraud, fp, oc, it, crp], 'F', ['T', 'P', 'F', 'I', 'O', 'C'], [])
#result = inference([trav, fraud, fp, oc, it, crp], 'F', ['T', 'P', 'F', 'I', 'O', 'C'], ['p','~i', 'c'])
#result = inference([trav, fraud, fp, oc, it, crp], 'F', ['T', 'P', 'F', 'I', 'O', 'C'], ['p','~i', 'c', 't'])
#result = inference([trav, fraud, fp, oc, it, crp], 'F', ['T', 'P', 'F', 'I', 'O', 'C'], ['i', 'c'])

#result = inference([trav, fraud, fp, oc, it, crp, u], 'B', ['T', 'P', 'F', 'I', 'O', 'C'], ['p', '~i', 'c'])




result = inference([trav, fraud, fp, oc, it, crp], 'F', ['T', 'P', 'F', 'I', 'O', 'C'], ['p', '~i', 'c', '~t'])
result = multiply(result, u)
result = sumout(result, 'F')
printFactor(result)
