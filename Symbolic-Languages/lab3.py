someList = [1, 2, 34, 94, 22, 0, 134, 4, 8, 45, 278, 293, 7, 472, 10, 0, 28, 17, 39, 2, 18, 94]

#ZADANIE_1

def listMean(lst):
    sum=0; amount=0
    for x in lst:
        sum+=x
        amount+=1
    return (sum, sum/amount)

wynik = listMean(someList)

print("Sum: " + str(wynik[0]) + ", Mean: " + str(wynik[1]))

#ZADANIE_2

def listCopier(lst):
    tmp=[ x for x in lst ]
    return tmp

print(listCopier(someList))

#ZADANIE_3

def listBlur(lst):
    tmp = lst.copy()
    for x in range(1, len(lst)-1):
        tmp[x]=((lst[x-1]+lst[x]+lst[x+1])/3)
    return tmp

print(listBlur(someList))

#ZADANIE_4

def listAdd(lst1, lst2):
    if(len(lst1)<len(lst2)):
        length=len(lst1)
    else:
        length=len(lst2)
    tmp = []
    for x in range(length):
        tmp.append(lst1[x]+lst2[x])
    return tmp

print(listAdd(someList[:11], someList[11:]))
print(listAdd(someList[:8], someList[8:]))

#ZADANIE_5

def listDivide(lst1, lst2):
    if(len(lst1)<len(lst2)):
        length=len(lst1)
    else:
        length=len(lst2)
    tmp = []
    for x in range(length):
        if(lst2[x]==0):
            continue
        tmp.append(lst1[x]/lst2[x])
    return tmp

print(listDivide(someList[:11], someList[11:]))
print(listDivide(someList[:8], someList[8:]))

#ZADANIE_6

def listMinMax(lst):
    length = len(lst)
    tmp = lst.copy(); tmp.sort(); tmp.reverse()
    if (length<=3):
        return tmp

    out = []
    for x in range(length-3, length):
        out.append(tmp[x])
    length-=3
    if (length > 3):
        length=3
    for x in range(length):
        out.append(tmp[x])
    return out

print(listMinMax(someList))

#ZADANIE_7

def listDel(lst):
    out = lst.copy()
    for x in range(len(lst)-1, -1, -1):
        if (((x+1)%3==0) or (out[x]==0)):
            del out[x]
    return out

print(listDel(someList))

#ZADANIE_8

def listInsert(lst, gap=0):
    if(gap<=0):
        return lst
    initial=0
    out = lst.copy()
    for x in range(gap, len(lst), gap):
        out.insert(x+initial, 0)
        initial+=1
    return out

print(listInsert(someList, 3))

#ZADANIE_9

def listCheckerboard(size):
    out = []
    for x in range(size):
        tmp = x+1
        part = [ y%2 for y in range(tmp, tmp+size)]
        out.append(part)
    return out

print(listCheckerboard(6))

#ZADANIE_9000

textList = ["Doctor Who", "Star Trek", "Star Wars", "Mass Effect", "Andromeda"]

def samogloski(text):
    counter=0
    samog = ['a', 'e', 'i', 'o', 'u', 'y']
    for i in list(text):
        if i in samog:
            counter+=1
    return counter

def itsAlmostOver9000(lst):
    out = []
    for i in lst:
        if samogloski(i)%2==0:
            out.append(i)
    return out

print(itsAlmostOver9000(textList))