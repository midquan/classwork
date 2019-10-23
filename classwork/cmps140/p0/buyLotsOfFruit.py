#!/usr/bin/env python3

"""
Based off of: http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

To run this script, type:

  python3 buyLotsOfFruit.py

Once you have correctly implemented the buyLotsOfFruit function,
the script should produce the output:

Cost of [('apples', 2.0), ('pears', 3.0), ('limes', 4.0)] is 12.25
"""

FRUIT_PRICES = {
    'apples': 2.00,
    'oranges': 1.50,
    'pears': 1.75,
    'limes': 0.75,
    'strawberries': 1.00
}

def buyLotsOfFruit(orderList):
    """
    orderList: List of (fruit, weight) tuples

    Returns cost of order
    """
    
    # *** Your Code Here ***
    cost = 0.0 
    # for fruit in orderList:
        # if(fruit[0] == 'apples'):
            # cost += 2.00 * fruit[1]
        # elif(fruit[0] == 'oranges'):
            # cost += 1.50 * fruit[1]
        # elif(fruit[0] == 'pears'):
            # cost += 1.75 * fruit[1]
        # elif(fruit[0] == 'limes'):
            # cost += .75 * fruit[1]
        # elif(fruit[0] == 'strawberries'):
            # cost += 1.00 * fruit[1]
        # else: 
            # print("Invalid fruit entered")
            # return None 
    for (fruit, quantity) in orderList:
        cost += FRUIT_PRICES[fruit] * quantity 
    return cost

def main():
    orderList = [
        ('apples', 2.0),
        ('pears', 3.0),
        ('limes', 4.0)
    ]

    print("Cost of %s is %s." % (orderList, buyLotsOfFruit(orderList)))

if __name__ == '__main__':
    main()