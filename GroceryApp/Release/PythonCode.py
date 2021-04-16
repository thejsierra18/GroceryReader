import re
import string
from collections import Counter


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def CountEachWordFrequency(fileName):
    f = open(fileName, "r")
    l = [item[:len(item)-1] for item in f]
    result = Counter(l)
    for k,v in result.items():
        print(k, v)
    f.close()
    return 0

groceryList = []

def CountOneWordFrequency(word):
    f = open("GroceryList.txt", "r")
    l = [item[:len(item)-1] for item in f]
    result = l.count(word.capitalize())
    if (result == 0):
        print("Item \"" + word + "\" is not in the grocery list.")
        return 0
    else:
        return result
    f.close()

def CreateFile(fileName):
    f = open(fileName, "r")
    l = [item[:len(item)-1] for item in f]
    result = Counter(l)
    f.close()
    g = open("frequency.dat", "w")
    for k,v in result.items():
        g.write( "{} {}\n".format(k,v) )
    g.close()
    return 0
    
    


