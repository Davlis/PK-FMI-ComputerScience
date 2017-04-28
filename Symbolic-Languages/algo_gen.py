from math import cos, pow, e
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import pandas

def func(args):
    x1, x2 = args
    return -(x1 ** 2 + x2 ** 2)

def func2(args):
    x1 = args[0]
    return x1 ** 2 + 2 * x1 + 4

def func3(arg):
    return -(arg[0] ** 2)

def easome(args):
    x1, x2 = args
    return cos(x1)*cos(x2)*pow(e, -pow(x1-25, 2)-pow(x2-25, 2))

def obj_func(x):
    x = np.array(x)
    a = 20
    b = 0.2
    c = 2*np.pi
    d = 5.7
    f = 0.8
    n = 2
    return -1*(1./f)*(-a*np.exp(-b*np.sqrt(np.mean(x*x)))-np.exp(np.mean(np.cos(c*x)))+a+np.exp(1)+d)

class Population:
    """
    a - początek przedziału
    b - koniec przedziału
    dx - krok w przedziale
    population - populacja (bitowo)
    dec_pop - populacja (dziesiętnie)
    eval_pop - populacja (po przeliczeniu wartości funkcji)
    """
    def __init__(self, func, populationSize, amountOfVariables, amountOfIterations, pk, pm, a, b, dx):
        self.func = func
        self.populationSize, self.amountOfVariables = populationSize, amountOfVariables
        self.probabilityOfCross, self.probabilityOfMutation = pk, pm
        self.a, self.b = a, b
        self.amountOfBits, self.dx = self.nbits(dx)
        self.population = self.gen_population()
        self.dec_pop = self.decode_population()
        self.eval_pop = self.evaluate_population()

        print("0: " + str(self.get_best()))
        self.best_values = [self.get_best()]
        self.best = self.best_values[0]

        for i in range(amountOfIterations):
            pop = self.roulette(self.population, self.eval_pop)
            self.cross(pop)
            self.mutate(pop)
            self.population = pop
            self.dec_pop = self.decode_population()
            self.eval_pop = self.evaluate_population()
            print(str(i+1) + ": " + str(self.get_best()))
            self.best_values.append(self.get_best())
            if self.best_values[i][1] > self.best[1]:
                self.best = self.best_values[i]

        print("Best: " + str(self.best))
        sum = 0
        for i in self.best_values:
            sum += i[2]
        print("Average: " + str(sum/len(self.best_values)))

        #self.make_plot(self.best_values)
        self.make_plot2()
        #x = pandas.DataFrame(self.best_values)
        #x.to_csv("output")

    def get_best(self):
        max = 0
        for x in range(max, len(self.eval_pop)):
            if (self.eval_pop[max] < self.eval_pop[x]):
                max = x
        decoded_max = []
        for i in self.dec_pop[max]:
            decoded_max.append(self.a+self.dx*i)
        return (decoded_max, self.eval_pop[max])

    def make_plot(self, args):
        x, y = [x for x in range(len(args))], args
        plt.scatter(x, y)
        plt.show()

    def make_plot2(self):
        n = 100
        sampled = np.linspace(self.a, self.b, n)
        x, y = np.meshgrid(sampled, sampled)
        z = np.zeros((len(sampled), len(sampled)))

        for i in range(len(sampled)):
            for j in range(len(sampled)):
                z[i, j] = obj_func(np.array([x[i, j], y[i, j]]))

        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis',
                               linewidth=0.4, antialiased=True)

        cset = ax.contourf(x, y, z, zdir='z', offset=7, cmap='viridis', alpha=0.5)
        cset = ax.contourf(x, y, z, zdir='x', offset=2, cmap='viridis', alpha=0.5)
        cset = ax.contourf(x, y, z, zdir='y', offset=2, cmap='viridis', alpha=0.5)

        ax.view_init(30, 200)
        plt.show()

    def nbits(self, dx):
        x, y = (self.b - self.a) / dx + 1, 0
        while x > 1:
            x = x / 2
            y += 1
        return (y, (self.b - self.a) / ((2 ** y) - 1))

    def gen_population(self):
        return np.random.randint(2, size=(self.populationSize, self.amountOfVariables * self.amountOfBits))

    def decode_population(self):
        arr = []
        for p in self.population:
            r = []
            for x in range(self.amountOfVariables):
                t = p [ x * self.amountOfBits : (x + 1) * self.amountOfBits ]
                r.insert(x, 0)
                for y in range(self.amountOfBits):
                    r[x] += t[y] * 2 ** (self.amountOfBits - y - 1)
            arr.append(r)
        return arr

    def evaluate_population(self):
        arr = []
        for p in self.dec_pop:
            args = []
            for n in range(self.amountOfVariables):
                args.append(self.a + p[n] * self.dx)
            arr.append(self.func(args))
        return arr

    def roulette(self, pop, eval_pop):
        values = []
        for p in range(self.populationSize):
            for i in values:
                if i[0] == eval_pop[p]:
                    break
            else:
                values.append([eval_pop[p], pop[p]])

        for i in values:
            if i[0] < 0:
                x = i[0]
                for j in values:
                    j[0] -= x

        sum = 0
        for i in values:
            sum += i[0]

        probabilities = []
        for i in values:
            probabilities.append(i[0]/sum)

        new_pop = []
        currentRoulettePosition = 0.0
        for i in range(self.populationSize):
            rouletteSpin = np.random.random_sample()
            currentRoulettePosition += rouletteSpin
            currentRoulettePosition %= 1
            temp = currentRoulettePosition
            for j in range(len(values)):
                temp -= probabilities[j]
                if temp <= 0:
                    new_pop.append(values[j][1])
                    continue

        return new_pop

    def cross(self, pop):
        for cur in range(self.populationSize):
            if np.random.random_sample() < self.probabilityOfCross:
                cross_point = np.random.randint(1, self.amountOfBits * self.amountOfVariables - 1)

                while True:
                    ano = np.random.randint(self.populationSize)
                    if cur != ano:
                        break

                curFin = list(pop[cur][:cross_point]) + list(pop[ano][cross_point:])
                anoFin = list(pop[ano][:cross_point]) + list(pop[cur][cross_point:])
                pop[cur] = np.array(curFin)
                pop[ano] = np.array(anoFin)

    def mutate(self, pop):
        for p in pop:
            if np.random.random_sample() < self.probabilityOfMutation:
                mutation = np.random.randint(self.amountOfBits*self.amountOfVariables)
                p[mutation] += 1
                p[mutation] %= 2


#pop = Population(0, 12.7, 0.1, 100, 2, func, 500)

'''
pop2 = Population(0, 10, 10, 1, func2, 0)
print(pop2.get_best())
'''

#pop3 = Population(20, 30, 0.0001, 300, 2, easome, 100)

pop4 = Population(obj_func, 100, 2, 1000, 0.7, 0.02, -1.5, 1.5, 0.0001)