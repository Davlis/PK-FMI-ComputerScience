from pyDatalog import pyDatalog as pl

#ZADANIE_1

pl.create_terms('X, Y, mezczyzna, kobieta, rodzice')
+mezczyzna('Adam')
+mezczyzna('Stefan')
+mezczyzna('Staszek')
+mezczyzna('Marek')

+kobieta('Alicja')
+kobieta('Alina')
+kobieta('Maria')
+kobieta('Anna')

+rodzice('Stefan', 'Staszek', 'Maria')
+rodzice('Alicja', 'Staszek', 'Maria')
+rodzice('Anna', 'Marek', 'Alina')

print(rodzice('Stefan', X, Y))
"""
X       | Y
--------|------
Staszek | Maria
"""

print(rodzice(X, 'Staszek', Y))
'''
X      | Y
-------|------
Stefan | Maria
Alicja | Maria
'''

pl.create_terms('X, Y, Ojciec, Matka, siostra')
siostra(X, Y) <= kobieta(Y) & rodzice(X, Ojciec, Matka) & rodzice(Y, Ojciec, Matka)

print(siostra('Stefan', Y))
'''
Y
------
Alicja
'''

pl.create_terms('X, Y, Z, lubi, rlubi')
+lubi('Maria', 'piwo')
+lubi('Stefan', 'piwo')
+lubi('Marek', 'piwo')
+lubi('Adam', 'piwo')
+lubi('Anna', 'piwo')

rlubi(X, Y, Z) <= lubi(Z, X) & (Y != Z)

print(rlubi('piwo', 'Stefan', Z))
"""
Z
-----
Adam
Anna
Marek
Maria
"""

#ZADANIE_2

pl.create_terms('King, Start, End, Year, king, reign')
+king('Mieszko II', 1025, 1036)
+king('Bolesław II Szczodry', 1076, 1079)
+king('Władysław Łokietek', 1320, 1333)
+king('Kazimierz III Wielki', 1333, 1370)
+king('Ludwik Węgierski', 1370, 1382)
+king('Jadwiga Andegaweńska', 1384, 1399)
+king('Władysław Jagiełło', 1386, 1434)
+king('Zygmunt I Stary', 1506, 1548)
+king('Zygmunt II August', 1549, 1572)
+king('Henryk Walezy', 1573, 1574)

reign(King, Year) <= king(King, Start, End) & ((Start <= Year) & (Year <= End))

print(reign(King, 1399))
'''
King
--------------------
Władysław Jagiełło
Jadwiga Andegaweńska
'''

#ZADANIE_3

pl.create_terms('Name, Salary, Tax, earns, tax, taxCounter')
+earns('Adam', 36000)
+earns('Stefan', 60000)
+earns('Staszek', 96000)
+earns('Alina', 3000)

tax(Name, Tax) <= (earns(Name, Salary)) & (Salary<3092) & (Tax==0)
tax(Name, Tax) <= (earns(Name, Salary)) & ((Salary>=3092) & (Salary<85529)) & (Tax==((0.18*Salary)-556.02))
tax(Name, Tax) <= (earns(Name, Salary)) & (Salary>=85529) & (Tax==(14839.02 + (Salary-85528)*0.32))

print(tax(Name, Tax))

"""
Name    | Tax
--------|---------
Staszek | 18190.06
Adam    | 5923.98
Stefan  | 10243.98
Alina   | 0
"""