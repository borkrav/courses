nodes = []
weights = []
tour = []


width = 1920
height = 1080

#read in all the data

with open('C:\\Users\\Boris\\Desktop\\outputNodes') as f:
    next(f)
    for line in f:
        data = line.split()
        nodes.append(data)

with open('C:\\Users\\Boris\\Desktop\\outputWeights') as f:
    next(f)
    for line in f:
        weights.append(line.rstrip('\n'))

with open('C:\\Users\\Boris\\Desktop\\tour') as f:
    for line in f:
        tour.append(line.rstrip('\n'))




#create PS file


with open('C:\\Users\\Boris\\Desktop\\TSP.ps', 'w') as f:
    print('%!PS', file=f)

    print('%%PageBoundingBox: 0 0 ', width, ' ', height, file=f)

    for i in range(1, len(nodes)-1):
        weight = 5*float(weights[int(tour[i])])
        
        print(weight, ' setlinewidth', file=f)

        print('1 setlinecap', file=f)


        print(nodes[int(tour[i])][0], ' ' ,nodes[int(tour[i])][1], ' moveto', file=f)
        print(nodes[int(tour[i+1])][0], ' ' ,nodes[int(tour[i+1])][1], ' lineto', file=f)

        print('stroke', file=f)


    print(nodes[int(tour[len(nodes)-1])][0], ' ' ,nodes[int(tour[len(nodes)-1])][1], ' moveto', file=f)
    print(nodes[int(tour[0])][0], ' ' ,nodes[int(tour[0])][1], ' lineto', file=f)
