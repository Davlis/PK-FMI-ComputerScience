import random

class ZlyNominalException(Exception):
    pass

class NieznanaWalutaException(Exception):
    pass

class UderzylesSieWPalecException(Exception):
    pass

class Moneta:
    coinList = [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5]
    currencyList = ['PLN', 'EUR', 'GBP', 'USD']

    def __init__(self, value, currency):
        if value in self.coinList:
            self.__value__ = value
        else:
            self.__value__ = 0
        if currency in self.currencyList:
            self.__currency__ = currency
        else:
            raise ZlyNominalException

    def get(self):
        return self.__value__

    def currency(self):
        return self.__currency__

class Skarbonka:
    def __init__(self, currency):
        self.coins = []
        self.__currency__ = currency

    def add(self, coin):
        if hasattr(self, 'rozbita'):
            return
        elif not isinstance(coin, Moneta):
            print("Przesłany obiekt nie jest monetą")
        elif coin.currency() != self.__currency__:
            raise NieznanaWalutaException
        else:
            self.coins.append(coin)

    def sum(self):
        sum=0
        for i in self.coins:
            sum+=i.get()
        return sum

    def rozbij(self):
        if hasattr(self, 'rozbita'):
            return
        out = []
        self.rozbita = True
        if random.randint(0, 9) == 0:
            raise UderzylesSieWPalecException
        for i in self.coins:
            out.append(i)
            del i
        return out

x = Moneta(5, 'EUR')

y = Skarbonka('EUR')

y.add(x)

y.rozbij()