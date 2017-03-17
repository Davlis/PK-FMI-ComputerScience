#zadanie1

def isPrime(a):
    counter=1
    for x in range(2, int(a**(1/2))):
        if a%x==0:
            counter+=1
        if counter>2:
            return False
    return True

def Mersenne(a):
    return (2**a)-1

def checkMersenne(a=31):
    for x in range(1, a+1):
        if isPrime(Mersenne(x)):
            print(str(Mersenne(x)) + " is prime")
        else:
            print(str(Mersenne(x)) + " is not prime")

#checkMersenne(60)

#zadanie2

def printCenter(str, length=80):
    if len(str) < length:
        print(" "*int((length-len(str))/2), end="")
    print(str)

#printCenter("ALL HAIL SATAN", 60)

#zadanie3

def function(xp=-1, xk=1, amount=10, fx=lambda x: x):
    sizeOfGap=(xk-xp)/(amount)
    for x in range(amount+1):
        print("x=" + str(xp+x*sizeOfGap) + ", f(x)=" + str(fx(xp+sizeOfGap*x)))

#function(fx=lambda x: x**2)

#function(1, 10, 9, fx=lambda x: x*(x-1)/2)

#zadanie4

import random
random.seed()

def k4():
    return random.randint(1, 4)

def k8():
    return random.randint(1, 8)

def k10():
    return random.randint(1, 10)

def k20():
    return random.randint(1, 20)

def getDice(str):
    if str=="k4":
        return k4()
    elif str=="k8":
        return k8()
    elif str=="k10":
        return k10()
    elif str=="k20":
        return k20()
    else:
        pass

def rollDice(str):
    numbers=str.split("k")
    sum=0
    for x in range(int(numbers[0])):
        sum+=getDice("k"+numbers[1])
    return sum

#print(rollDice("10k20"))

#zadanie5

import time

def credits(*creds):
    for x in creds:
        printCenter(x, 40)
        time.sleep(1)

credits("Kamil Kosiński", "Szymon Hajnos", "Tomasz Grembosz", "JACKASS")