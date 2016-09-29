import os, math, datetime, sys
from random import shuffle
from operator import itemgetter

puzzle = []

mode = "easy"
solver = 1


randomize = True

nodes = 0

def checkConstraints(assignment, value, index):

    #index (0-80) to V_abcd conversion formulation

    # a = row of square {0 - 2}
    # floor( index/27 ) 
    # b = column of square {0 - 2}
    # floor ( ( index % 9 ) / 3 )
    # c = row inside square {0 - 2}
    # floor ((index % 27) / 9)
    # d = column inside square  {0 - 2}
    # ( ( index % 9 ) % 3 )

    v_a = math.floor(index/27)
    v_b = math.floor((index%9)/3)
    v_c = math.floor((index%27)/9)
    v_d = ((index%9)%3) 

    #could be optimized further to minimize number of squares checked
    #-- only check indeces that contain constraints

    for i in range (0,81):

        a_a = math.floor(i/27)
        a_b = math.floor((i%9)/3)
        a_c = math.floor((i%27)/9)
        a_d = ((i%9)%3) 

        #square
        if v_a == a_a and v_b == a_b and v_c != a_c and v_d != a_d and value == int(assignment[i]): 
            return False
        #column
        if v_a == a_a and v_c == a_c and (v_b*3 + v_d) != (a_b*3 + a_d) and value == int(assignment[i]): 
            return False
        #row
        if v_b == a_b and v_d == a_d and (v_a*3 + v_c) != (a_a*3 + a_c) and value == int(assignment[i]): 
            return False

    return True


def processForward(assignment, value, index, forward):

    v_a = math.floor(index/27)
    v_b = math.floor((index%9)/3)
    v_c = math.floor((index%27)/9)
    v_d = ((index%9)%3) 

    changes = []


    for i in range (0,81):

        a_a = math.floor(i/27)
        a_b = math.floor((i%9)/3)
        a_c = math.floor((i%27)/9)
        a_d = ((i%9)%3) 


        #square
        if v_a == a_a and v_b == a_b and v_c != a_c and v_d != a_d and 0 not in forward[i]:
            if value in forward[i]: 
                forward[i].remove(value)
                changes.append(i)
        #column
        if v_a == a_a and v_c == a_c and (v_b*3 + v_d) != (a_b*3 + a_d) and 0 not in forward[i]:
            if value in forward[i]: 
                forward[i].remove(value)
                changes.append(i)
        #row
        if v_b == a_b and v_d == a_d and (v_a*3 + v_c) != (a_a*3 + a_c) and 0 not in forward[i]:
            if value in forward[i]: 
                forward[i].remove(value)
                changes.append(i)

    return changes

def countConstraints(assignment, index):

    v_a = math.floor(index/27)
    v_b = math.floor((index%9)/3)
    v_c = math.floor((index%27)/9)
    v_d = ((index%9)%3) 

    constraints = 0
  
    for i in range (0,81):

        a_a = math.floor(i/27)
        a_b = math.floor((i%9)/3)
        a_c = math.floor((i%27)/9)
        a_d = ((i%9)%3) 

        #square
        if v_a == a_a and v_b == a_b and v_c != a_c and v_d != a_d and int(assignment[i]) == 0: 
            constraints+=1
        #column
        if v_a == a_a and v_c == a_c and (v_b*3 + v_d) != (a_b*3 + a_d) and int(assignment[i]) == 0: 
            constraints+=1
        #row
        if v_b == a_b and v_d == a_d and (v_a*3 + v_c) != (a_a*3 + a_c) and int(assignment[i]) == 0: 
            constraints+=1

    return constraints


def countVarConstraining(assignment, value, index, forward):
    v_a = math.floor(index/27)
    v_b = math.floor((index%9)/3)
    v_c = math.floor((index%27)/9)
    v_d = ((index%9)%3) 

    constraints = 0
  
    for i in range (0,81):

        a_a = math.floor(i/27)
        a_b = math.floor((i%9)/3)
        a_c = math.floor((i%27)/9)
        a_d = ((i%9)%3) 

        constraints = 0

        if v_a == a_a and v_b == a_b and v_c != a_c and v_d != a_d and 0 not in forward[i]:
            if value in forward[i]: constraints+=1
        #column
        if v_a == a_a and v_c == a_c and (v_b*3 + v_d) != (a_b*3 + a_d) and 0 not in forward[i]:
            if value in forward[i]: constraints+=1
        #row
        if v_b == a_b and v_d == a_d and (v_a*3 + v_c) != (a_a*3 + a_c) and 0 not in forward[i]:
            if value in forward[i]: constraints+=1

    return constraints



def solver1(puzzle):
    return solver1Recurse(puzzle)


#exactly as stated in the slides
def solver1Recurse(assignment):

    global nodes

    # assignment is complete, base case
    if "0" not in assignment:
        return assignment


    next = 0
    emptySquares = []
    
    #find the indeces of all unsolved squares
    for i in range (0,81):
        if assignment[i] == "0":
            emptySquares.append(i)

    #shuffle indeces of unsolved squares, pick first one to solve
    if randomize: shuffle(emptySquares)
    next = emptySquares[0]

    #print (len(emptySquares))

    listToCheck = [i for i in range(1,10)]
    if randomize: shuffle(listToCheck)

    for i in listToCheck:
       
        if (checkConstraints(assignment,i,next)) == True:
            assignment[next] = str(i)
            #printSudoku()
            nodes +=1
            result = solver1Recurse(assignment)

            if result != "failure":
                return result

            assignment[next] = str(0)

    return "failure"




def solver2(puzzle):


    valid = []

    #create list of valid values for all empty squares
    for i in range (0,81):
        if puzzle[i] == "0":
            valid.append([1,2,3,4,5,6,7,8,9])
        else:
            valid.append([0])

    return solver2Recurse(puzzle, valid)

def solver2Recurse(assignment, forward):

    global nodes

    if "0" not in assignment:
        return assignment

    next = 0

    emptySquares = []

    
    for i in range (0,81):
        if assignment[i] == "0":
            emptySquares.append(i)

    if randomize: shuffle(emptySquares)
    next = emptySquares[0]


    listToCheck = forward[next][:]
    if randomize: shuffle(listToCheck)
    
    for valueToCheck in listToCheck:
       
        if (checkConstraints(assignment,valueToCheck,next)) == True:
            assignment[next] = str(valueToCheck)

            rollback = processForward(assignment,valueToCheck,next, forward)[:]

            oldValues = forward[next][:]
            forward[next] = [0]

            skip = False

            for j in forward:
                if not j:
                    skip = True
                    #print ("skipping")

           # printSudoku()

            if not skip:
                nodes +=1
                result = solver2Recurse(assignment, forward)

                if result != "failure":
                    return result

            assignment[next] = str(0)
            
            for item in range (0,81):
                if item in rollback:
                    forward[item].append(valueToCheck)

            forward[next] = oldValues [:]


    return "failure"

            



def solver3(puzzle):


    valid = []

    for i in range (0,81):
        if puzzle[i] == "0":
            valid.append([1,2,3,4,5,6,7,8,9])
        else:
            valid.append([0])

    return solver3Recurse(puzzle, valid)

def solver3Recurse(assignment, forward):
    
    global nodes

    if "0" not in assignment:
        return assignment

    next = 0

    mostConstrained = []

    for j in range (0,10):
        for i in range (0,81):
            if forward[i][0] != 0 and len(forward[i]) == j:
                mostConstrained.append(i)
        if len(mostConstrained) > 0:
            break

   # print (mostConstrained)

    next = mostConstrained[0]

    mostConstraining = []

    if (len(mostConstrained) > 0):

        for i in mostConstrained:
            mostConstraining.append([next, countConstraints(assignment,next)])

    min = 10000

    for i in mostConstraining:
        if i[1] < min:
            min = i[1]
            next = i[0]


    #print (mostConstraining)

    leastConstrained = []

    listToCheck = forward[next][:]

    for i in listToCheck:
        leastConstrained.append([i, countVarConstraining(assignment, i, next, forward)])

    leastConstrained.sort(key=lambda x: x[1])


    
    for valueToCheck in leastConstrained:
       
         if (checkConstraints(assignment,valueToCheck[0],next)) == True:
            assignment[next] = str(valueToCheck[0])

            rollback = processForward(assignment,valueToCheck[0],next, forward)[:]

            oldValues = forward[next][:]
            forward[next] = [0]

            skip = False

            for j in forward:
                if not j:
                    skip = True
                    print ("skipping")

           # printSudoku()

            if not skip:
                nodes +=1
                result = solver3Recurse(assignment, forward)

                if result != "failure":
                    return result

            assignment[next] = str(0)
            
            for item in range (0,81):
                if item in rollback:
                    forward[item].append(valueToCheck[0])

            forward[next] = oldValues [:]

    return "failure"





def printSudoku():
   
    for i in range (0,9):

        for j in range (0,9):
            print ("  " + puzzle[i*9 + j], end="")
        print("\n")


    #os.system('cls')


#read in sudoku puzzle


with open('Tests/'+ mode + '.txt', 'r') as f:

    while True:
        c= f.read(1)

        if not c:
            break

        if not c == '\n':
            puzzle.append(c)

f.close()



printSudoku()
a = datetime.datetime.now()


for i in range (1, 51):

    nodes = 0

    inputPuzzle = puzzle [:]

    print("START:", i, mode)
    a = datetime.datetime.now()
    print ("TIME:", a)
    if solver == 1:
        solver1(inputPuzzle)
    if solver == 2:
        solver2(inputPuzzle)
    if solver == 3:
        solver3(inputPuzzle)
    print("DONE:", i, mode)
    b = datetime.datetime.now()
    print((b-a).total_seconds())
    print(nodes)



#forwardChecking(puzzle)


#printSudoku()

