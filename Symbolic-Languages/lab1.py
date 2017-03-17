from math import sin

#zadanie2

def czyPrzestepny(x):
    try:
        year=int(x)
    except ValueError:
        print("Podana wartość nie jest liczbą naturalną.")
        return None
    #print("Halo", x)
    if year%4==0 and not year%400==0:
        print("Rok jest przestępny.")
    else:
        print("Rok nie jest przestępny.")

#czyPrzestepny(input("Podaj żądany rok: "))

#zadanie3

def displayX():
    for x in range(21):
        a=-1.0+(x*0.1)
        print("{0:8.2f} {1:+10.6f} {1:12.2e}".format(a, sin(a)))

#displayX()

#zadanie4

def ifPrime(x):
    try:
        number=int(x)
    except ValueError:
        print("Podana wartość nie jest liczbą naturalną.")
        return None
    sum=1
    for i in range(2, number):
        if number%i==0:
            sum+=1
        if sum>2:
            print("Liczba nie jest pierwsza.")
            break
    else:
        print("Liczba jest pierwsza.")

#ifPrime(input("SPRAWDŹ CZY LICZBA JEST PIERWSZA: "))

#zadanie5

def klingon(str):
    counter=0
    retStr=[]
    for i in str:
        if i=='a' or i=='e' or i=='i' or i=='o' or i=='u':
            retStr.append('a')
            counter+=1
        else:
            retStr.append(i)
    print("".join(retStr))
    print(counter)

klingon(input("Przetłumacz na język Klingon: "))

#zadanie6

def dayOfTheWeek(day):
    for i in range(2):
        if not (day=="Poniedziałek" or day=="Wtorek" or day=="Środa" or day=="Czwartek" or day=="Piątek" or day=="Sobota" or day=="Niedziela"):
            if i==0:
                day=input("Użytkowniku, podajże jeszcze raz dzień tygodnia, boś coś źle wpisał: ")
                continue
            else:
                print("Dobra, nie chcesz to nie, wypchaj się z takim podejściem")
                return None
        else:
            if day=="Poniedziałek":
                print("Poniedziałek to najgorszy dzień tygodnia, weź wyjdź najlepiej.")
            elif day=="Wtorek":
                print("Wtorek niby jest ok, ale niesmak po poniedziałku pozostał :/")
            elif day=="Środa":
                print("Półmetek tygodnia, więc już bliżej niż dalej do odpoczynku")
            elif day=="Czwartek":
                print("Jutro piąteczek, więc można wychillować ^^")
            elif day=="Piątek":
                print("Nareszcie koniec tygodnia, można iść na piwo :3")
            elif day=="Sobota":
                print("Pobudka dopiero o 14")
            else:
                print("Już jutro poniedziałek, więc nie ciesz się tak.")
            break

#dayOfTheWeek(input("Podaj dzień tygodnia (poprawnie, z dużej litery): "))