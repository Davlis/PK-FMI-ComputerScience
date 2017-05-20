from pyDatalog import pyDatalog as pl

#MINIPROJEKT
#komis samochodowy

pl.create_terms('car, X, Marka, Model, Rok, Moc, TypPaliwa, Przebieg, searchForCars, searchYoungCars, searchSmallPrzebieg')
+car('Mazda', '3', 2010, 150, 'benzyna', 45000)
+car('Renault', 'Megane', 2008, 115, 'benzyna', 140000)
+car('BMW', 'X5', 2007, 210, 'diesel', 180000)
+car('Peugeot', '307', 2005, 110, 'gaz', 120000)
+car('Renault', 'Scenic', 2008, 120, 'diesel', 250000)
+car('Peugeot', '206', 1999, 90, 'gaz', 300000)
+car('BMW', 'X3', 2008, 190, 'diesel', 175000)
+car('Audi', 'A4', 2002, 140, 'benzyna', 250000)
+car('Audi', 'A6', 2005, 170, 'diesel', 190000)
+car('Toyota', 'Yaris', 2009, 80, 'gaz', 130000)
+car('Ford', 'Galaxy', 2000, 130, 'benzyna', 140000)
+car('Tesla', 'Model S', 2013, 300, 'elektryczny', 80000)
+car('Volkswagen', 'Passat', 2001, 100, 'gaz', 230000)
+car('Volkswagen', 'Beetle', 1963, 60, 'benzyna', 130000)
+car('Ford', 'Focus', 1999, 90, 'diesel', 260000)
+car('Mitsubishi', 'Eclipse', 2005, 160, 'benzyna', 130000)
+car('Mazda', 'RX-7', 2005, 130, 'benzyna', 160000)
+car('Seat', 'Leon', 2002, 150, 'benzyna', 150000)
+car('Opel', 'Astra', 1997, 80, 'gaz', 280000)
+car('Mercedes', 'GLK 220', 2009, 180, 'diesel', 50000)


searchForCars(Marka, Model, Rok, Moc, TypPaliwa, Przebieg) <= car(Marka, Model, Rok, Moc, TypPaliwa, Przebieg)
searchYoungCars(Marka, Model, X, Moc, TypPaliwa, Przebieg) <= car(Marka, Model, Rok, Moc, TypPaliwa, Przebieg) & (Rok>X)
searchSmallPrzebieg(Marka, Model, Rok, Moc, TypPaliwa, X) <= car(Marka, Model, Rok, Moc, TypPaliwa, Przebieg) & (Przebieg<X)


def userLoop():
    options = ['a', 'b', 'c']
    options2=['a', 'b', 'c', 'd']
    print("WITAMY W KOMISIE")
    while True:
        print()
        print("Co chcesz zrobić?")
        print('\t[a] wyszukaj auta po cechach')
        print("\t[b] wyszukaj aut z mniejszym przebiegiem od podanego")
        print("\t[c] wyszukaj aut młodszych od podanego roku")
        print("\t[d] pokaż wszystkie auta")
        print("\tinny znak - wyjdź z programu")
        c = input('Podaj znak: ')
        if c not in options2:
            print("Do widzenia")
            return None
        elif c == 'b':
            Pzebieg = int(input('Podaj żądany przebieg samochodu: '))
            print("Oto auta mające mniejszy przebieg: ")
            print(searchSmallPrzebieg(Marka, Model, Rok, Moc, TypPaliwa, Pzebieg))
            continue
        elif c == 'c':
            Rocznik = int(input('Podaj żądany rocznik samochodu: '))
            print("Oto auta nowsze od danego rocznika: ")
            print(searchYoungCars(Marka, Model, Rocznik, Moc, TypPaliwa, Przebieg))
            continue
        elif c == 'd':
            print(searchForCars(Marka, Model, Rok, Moc, TypPaliwa, Przebieg))
            continue
        else:
            print("Wyszukaj po:")
            print('\t[a] marce')
            print("\t[b] mocy")
            print("\t[c] typie paliwa")
            d = input('Podaj znak: ')
            if d not in options:
                print("Błędny wybór")
                continue
            elif d == 'a':
                MarkaAuta = input("Wpisz markę auta: ")
                print(searchForCars(MarkaAuta, Model, Rok, Moc, TypPaliwa, Przebieg))
                continue
            elif d == 'b':
                MocAuta = int(input("Podaj moc w koniach mechanicznych: "))
                print(searchForCars(Marka, Model, Rok, MocAuta, TypPaliwa, Przebieg))
                continue
            else:
                print("Typy paliwa:")
                print('\t[a] benzyna')
                print("\t[b] diesel")
                print("\t[c] gaz")
                print("\t[d] elektryczny")
                e = input('Podaj znak: ')
                if e not in options2:
                    print("Błędny wybór")
                    continue
                elif e == 'a':
                    print(searchForCars(Marka, Model, Rok, Moc, 'benzyna', Przebieg))
                    continue
                elif e == 'b':
                    print(searchForCars(Marka, Model, Rok, Moc, 'diesel', Przebieg))
                    continue
                elif e == 'c':
                    print(searchForCars(Marka, Model, Rok, Moc, 'gaz', Przebieg))
                    continue
                else:
                    print(searchForCars(Marka, Model, Rok, Moc, 'elektryczny', Przebieg))
                    continue

userLoop()