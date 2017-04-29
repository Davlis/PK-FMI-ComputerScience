from math import *
import random as r

#ZADANIE_1

def sincos(x):
    return (sin(x), cos(x))

def sincosViewer():
    for i in range(11):
        x = i*9
        out = sincos(radians(x))
        print("Kąt: " + str(x) + ", sin: " + str(out[0]) + ", cos: " + str(out[1]))

sincosViewer()

#ZADANIE_2

def fibStep(x, y):
    return (y, x+y)

def fibonacci(which):
    a, b = (1, 1)
    for i in range(2, which):
        a, b = fibStep(a, b)
    return b

print(fibonacci(12))

#ZADANIE_3

def blur(lst, tup):
    if len(tup) != 3:
        return False
    if len(lst) < 2:
        return False

    tmp = lst.copy()
    for x in range(1, len(lst) - 1):
        tmp[x] = ((lst[x - 1]*tup[0] + lst[x]*tup[1] + lst[x + 1]*tup[2]) / (tup[0]+tup[1]+tup[2]))
    return tmp

print(blur([3, 1, 2, 0, 4], (2, -1, 2)))

#ZADANIE_4

marks = {'Paweł' : [5, 4, 2, 3], 'Kamil' : [5, 5, 6, 4], 'Tomek' : [1, 1, 1, 2], 'Konrad' : [2, 2, 3, 2]}

def dictSort(dic):
    for i in sorted(dic.keys()):
        print(i)

def dictWMarks(dic):
    for i in list(dic.keys()):
        print(i, dic[i])

dictSort(marks)
dictWMarks(marks)

#ZADANIE_5

marks2 = {'Paweł' : {'Algebra' : 2.0, 'WDP': 2.0, 'Analiza': 3.0}, 'Kamil' : {'Algebra' : 4.0, 'WDP': 4.5, "SO" : 5.0}}

def dictMean(dic):
    for i in dic:
        sum=0
        for j in dic[i].values():
            sum += j
        if (sum / len(dic[i].values())) < 3.0:
            print(i)

dictMean(marks2)

def dictSubj(dic):
    setdic = {}
    setdic = set()
    for i in dic:
        for j in dic[i].keys():
            if not j in setdic:
                setdic.add(j)
    for i in setdic:
        sum=0
        counter=0
        for j in dic.values():
            temp = dict(j)
            if i in j:
                sum += temp[i]
                counter += 1
        print(i, sum/counter)

dictSubj(marks2)

#ZADANIE_6

age = {'Kamil' : 20, 'Tomek' : 21, 'Grażyna' : 44, 'Aniela' : 71, 'Frankenstein' : 342, 'płód' : -0.7}

def dictSleep(dic):
    out = {}
    for i in dic:
        if dic[i] > 200:
            out.update({i : inf})
        elif dic[i] <= 0:
            continue
        else:
            out.update({i : (8 / log10(dic[i]))})
    return out

print(dictSleep(age))

#ZADANIE_7

def statki():
    r.seed()
    Matrix = [[False for col in range(10)] for row in range(10)]
    for i in range(10):
        while True:
            row = r.randint(0, 9)
            col = r.randint(0, 9)
            if Matrix[row][col] == False:
                break
        Matrix[row][col] = True
    userShots = {}
    userShots = set()
    remaining = 10
    while True:
        try:
            (x, y) = input("Podaj współrzędne: ")
        except ValueError:
            print("Błędne dane.")
            continue
        x=int(x); y=int(y)
        if (x, y) in userShots:
            print("Już tam strzelano!")
            continue
        else:
            userShots.add((x, y))

        if Matrix[x][y] == True:
            print("Trafiono!")
            remaining -= 1
            if remaining == 0:
                break
        else:
            print("Pudło!")
    print("Koniec gry!")

#statki()