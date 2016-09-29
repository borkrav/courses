from sys import float_info

#https://www.interviewcake.com/question/python/stock-price

#for every time stamp t compare with every other timestamp after it
#save the difference t_n - t
#output max

#analysis
#sum(n to 1) n = n(n-1) /2 = O(n^2)

#is there a better solution?
#we need to consider every pair of values
#finding global min/max isn't that useful, since timestamp requirement

def get_max_profit(prices):

    max = -float_info.max

    
    for t in range(len(prices)):
        for n in prices[t+1:]:
            if (n-prices[t]) > max:
                max = n-prices[t]

    return max
                        

#real solution was greedy...

def get_max_profit2(prices):

    min_price = stock_prices_yesterday[0]
    max_profit = stock_prices_yesterday[1] - stock_prices_yesterday[0]

    for index, current_price in enumerate(stock_prices_yesterday):

        # skip the first (0th) time
        # we can't sell at the first time, since we must buy first,
        # and we can't buy and sell at the same time!
        # if we took this out, we'd try to buy /and/ sell at time 0.
        # this would give a profit of 0, which is a problem if our
        # max_profit is supposed to be /negative/--we'd return 0!
        if index == 0:
            continue

        # see what our profit would be if we bought at the
        # min price and sold at the current price
        potential_profit = current_price - min_price

        # update max_profit if we can do better
        max_profit = max(max_profit, potential_profit)

        # update min_price so it's always
        # the lowest price we've seen so far
        min_price  = min(min_price, current_price)

    return max_profit



stock_prices_yesterday = [10, 7, 5, 8, 11, 9]
stock_prices_yesterday = [10, 9, 8, 7, 6, 5]


print (get_max_profit2(stock_prices_yesterday))
# returns 6 (buying for $5 and selling for $11)










###############################################################################




#since num and den are integers, this is O(1)
def divide(num,den):

    if num == 0:
        return 0

    sign = 1
    result = 1    

    if num*den < 0:
        sign = -1

    num = abs(num)
    den = abs(den)

    while num-den > 0:
        num = num-den
        result +=1

    return sign*result
        

    


#brute force is n^2, not going to bother implementing

#This is O(n), but technically I may have cheated by implementing my own division, by using subtraction
def get_products_of_all_ints_except_at_index(vals):

    result = []
    total = 1;

    for val in vals:
        total *= val;


    for val in vals:
        result.append(divide(total,val))


    return result


#they actually wanted a greedy solution, my solution is just as good

# - start with brute force, break down calculation, find patterns
# - if it's a maximization/minimization problem, greedy will probably work


print(get_products_of_all_ints_except_at_index([1,0,3,4]))


################################################################################################################




#brute force
# O(n^3)

def highest_product_1(input):

    maxi = 0;
        
    for i, vali in enumerate(input):
        for j, valj in enumerate(input[i+1:]):
            for k, valk in enumerate ((input[i+1:])[j+1:]):
                maxi = max(maxi, vali*valj*valk)


    return maxi


#sorting
#O(nlogn)

def highest_product_2(input):

    input = sorted(input)

    return input[-1]*input[-2]*input[-3]

#divide and conquer - split the list in 3 parts recursively, find max in each, recursively
#not O(n)

#123456789

#123 456 789

#1 2 3 4 5 6 7 8 9 

#this kind of solution will not work


#Greedy
#this is a maximization problem, so perhaps a greedy approach is possible
#Scan through the list, keeping track of the 2 largest numbers seen so far

#total O(n)
def highest_product_3(input):

    max1 = input[0]
    max2 = input[1]
    max3 = input[2]

    #iterating through the list once  = O(n)
    for val in input[3:]:
    
        #sorting 4 items = O(1)
        list = sorted([max1, max2, max3, val])
        
        max1 = list[-1]
        max2 = list[-2]
        max3 = list[-3]

    return max1*max2*max3
            





print(highest_product_1([-10,-10,1,3,2]))







