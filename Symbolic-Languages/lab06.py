import random

class Moneta:
    def __init__(self, value, currency):
        if value in [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5]:
            self.__value__ = value
        else:
            self.__value__ = 0
        self.__currency__ = currency

    def get(self):
        return self.__value__

    def currency(self):
        return self.__currency__

#mon = Moneta(0.5, 'PLN')
#mon2 = Moneta(0.1, 'PLN')
#mon3 = Moneta(1, 'PLN')

class PrzechowywaczMonet:
    def __init__(self, coinList):
        self.monety = []
        self.__coinList__ = coinList

    def add(self, moneta):
        if isinstance(moneta, Moneta):
            if moneta.get() in self.__coinList__:
                self.monety.append(moneta)
        else:
            print("Przesłany obiekt nie jest monetą")

    def sum(self):
        sum=0
        for i in self.monety:
            sum+=i.get()
        return sum

    def get(self, value):
        for i in self.monety:
            if i.get() == value:
                _i = i
                self.monety.remove(i)
                return _i

coins = [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5]

"""
skarb = PrzechowywaczMonet(coins)
skarb.add(mon)
skarb.add(mon2)
skarb.add(mon3)

skarb.get(0.1)

print(skarb.sum())
"""

class Skarbonka(PrzechowywaczMonet):
    def __init__(self, currency):
        self.monety = []
        self.__currency__ = currency

    def add(self, moneta):
        if isinstance(moneta, Moneta):
            if moneta.currency() == self.__currency__:
                self.monety.append(moneta)
            else:
                print("Nieznana moneta")
        else:
            print("Przesłany obiekt nie jest monetą")

    def sum(self):
        sum=0
        for i in self.monety:
            sum+=i.get()
        return sum

    def get(self, value):
        print("Nie można wyciągnąć pojedynczej monety")

"""
skarb = Skarbonka('PLN')
skarb.add(mon)
skarb.add(mon2)
skarb.add(mon3)

skarb.get(0.01)

print(skarb.sum())

mon4 = Moneta(0.5, 'GBP')

skarb.add(mon4)
"""

class ZlotaSkarbonka(Skarbonka, Moneta):
    def __init__(self):
        Skarbonka.__init__(self, 'PLN')
        Moneta.__init__(self, 9000, 'PLN')

"""
s2 = ZlotaSkarbonka()

print(Moneta.get(s2))

s2.add(s2)
print(Moneta.get(s2))
"""

class Numizmatyk:
    def identyfikuj(self, coin):
        if not isinstance(coin, Moneta):
            print("Obiekt nie jest monetą.")
            return
        if hasattr(coin, 'zidentyfikowany'):
            return
        coin.zidentyfikowany = True
        coin.year = random.triangular(1900, 2017, 1980)
        if coin.year < 1914:
            coin.wartosc_numizmatyczna = 2000
        elif coin.year < 1939:
            coin.wartosc_numizmatyczna = 1000
        else:
            coin.wartosc_numizmatyczna = 0

    def sprzedaj(self, coin):
        if not isinstance(coin, Moneta):
            print("Obiekt nie jest monetą.")
            return
        if not hasattr(coin, 'zidentyfikowany'):
            Numizmatyk.identyfikuj(self, coin)
        sum = 0
        list = []
        counter = 0
        while sum < coin.wartosc_numizmatyczna:
            counter += 1
            newCoin = Moneta(5, coin.currency())
            Numizmatyk.identyfikuj(self, newCoin)
            if newCoin.wartosc_numizmatyczna != 0:
                continue
            sum += newCoin.get()
            list.append(newCoin)
        print(counter)
        return list

    def transmutuj(self, coin):
        if not isinstance(coin, Moneta):
            print("Obiekt nie jest monetą.")
            return
        coin.zidentyfikowany = False
        del coin.wartosc_numizmatyczna

"""
print()
num = Numizmatyk()
list = [Moneta(0.5, 'PLN'), Moneta(5, 'EUR'), Moneta(2, 'GBP')]
for i in list:
    num.identyfikuj(i)
    if i.wartosc_numizmatyczna != 0:
        num.sprzedaj(i)
    else:
        num.transmutuj(i)
"""