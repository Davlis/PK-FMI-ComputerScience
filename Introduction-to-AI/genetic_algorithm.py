import numpy as np
from numpy import cos, sqrt, e, pi
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import random

def obj_func(x):
    return -1.25 * (-20 * e ** (-0.2 * sqrt((x[0] ** 2 + x[1] ** 2) / 2)) - e ** ((cos(2 * pi * x[0]) + cos(2 * pi * x[1])) / 2) + e + 25.7)

def analytical_plot(self):
    n = 100
    sampled = np.linspace(-1.5, 1.5, n)
    x, y = np.meshgrid(sampled, sampled)
    z = np.zeros((len(sampled), len(sampled)))
    for i in range(len(sampled)):
        for j in range(len(sampled)):
            z[i, j] = self.func(np.array([x[i, j], y[i, j]]))
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis', linewidth=0.4, antialiased=True)
    cset = ax.contourf(x, y, z, zdir='z', offset=7, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='x', offset=2, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='y', offset=2, cmap='viridis', alpha=0.5)
    ax.view_init(30, 200)
    plt.show()

class Population:
    """ Populacja liczy osobników dla funkcji maksymalizujących
    a - początek przedziału
    b - koniec przedziału
    dx - krok w przedziale
    pk - prawdopodobieństwo krzyżowania
    pm - prawdopodobieństwo mutacji
    population - populacja (bitowy index)
    dec_pop - populacja (dziesiętnie)
    eval_pop - populacja (wartość funkcji) """

    def __init__(self, func, size=100, variables=1, pk=0.7, pm=0.02, a=-1.0, b=1.0, dx=0.01):
        self.func = func
        self.sizeOfPopulation, self.amountOfVariables = size, variables
        self.probabilityOfCross, self.probabilityOfMutation = pk, pm
        self.a, self.b = a, b
        self.amountOfBits, self.dx = self.nbits(dx)
        self.population = self.gen_population()
        self.decode_population()
        self.evaluate_population()

        self.best_values = [self.get_best()]
        self.best = self.best_values[0]
        self.plot_values = []
        self.plot_values.append(self.get_plot_values())

    def make_generations(self, amountOfIterations=100):
        for i in range(1, amountOfIterations + 1):
            self.roulette()
            self.cross()
            self.mutate()
            self.decode_population()
            self.evaluate_population()

            self.best_values.append(self.get_best())
            if self.best_values[i] > self.best:
                self.best = self.best_values[i]
                print(self.best)
            self.plot_values.append(self.get_plot_values())

        print("Best: " + str(self.best) + ", Average: " + str(self.get_average(self.best_values)))
        self.make_runtime_plot(self.plot_values)

    def nbits(self, dx):
        x, y = (self.b - self.a) / dx + 1, 0
        while x > 1:
            x = x / 2
            y += 1
        return (y, (self.b - self.a) / ((2 ** y) - 1))

    def gen_population(self):
        np_pop = np.random.randint(2, size=(self.sizeOfPopulation, self.amountOfVariables * self.amountOfBits))
        py_pop = []
        for i in range(self.sizeOfPopulation):
            py_pop.append(list(np_pop[i]))
        return py_pop

    def decode_population(self):
        self.dec_pop = []
        for p in self.population:
            output = []
            for var in range(self.amountOfVariables):
                value = 0
                pos = var * self.amountOfBits
                for power in range(self.amountOfBits-1, -1, -1):
                    value += int(p[pos] * (2**power))
                    pos += 1
                output.append(self.a + (value * self.dx))
            self.dec_pop.append(output)

    def evaluate_population(self):
        self.eval_pop = []
        for p in self.dec_pop:
            self.eval_pop.append(self.func(p))

    def roulette(self):
        values = []
        for p in range(self.sizeOfPopulation):
            for i in values:
                if i[0] == self.eval_pop[p]:
                    break
            else:
                values.append([self.eval_pop[p], self.population[p]])
        self.population = []

        x_min, x = 0, 0
        for i in values:
            if i[0] < x_min:
                x = x_min
                x_min = i[0]

        if x_min < 0:
            for i in values:
                i[0] -= (x_min + (x_min-x))

        sum = 0
        for i in values:
            sum += i[0]

        probabilities = []
        for i in values:
            probabilities.append(i[0]/sum)

        currentRoulettePosition = 0.0
        for i in range(self.sizeOfPopulation):
            rouletteSpin = np.random.random_sample()
            currentRoulettePosition += rouletteSpin
            currentRoulettePosition %= 1
            temp = currentRoulettePosition
            for j in range(len(values)):
                temp -= probabilities[j]
                if temp <= 0:
                    self.population.append(values[j][1])
                    break
            else:
                self.population.append(values[len(values)-1][1])

    def cross(self):
        new_pop = []
        cross = []
        values = [x for x in range(self.sizeOfPopulation)]

        for i in range(self.sizeOfPopulation):
            x = random.choice(values)

            if np.random.random_sample() <= self.probabilityOfCross:
                cross.append(x)
                if len(cross) == 2:
                    cross_point = np.random.randint(1, self.amountOfBits * self.amountOfVariables)
                    current = self.population[cross[0]][:cross_point]
                    current += self.population[cross[1]][cross_point:]
                    new_pop.append(current)
                    another = self.population[cross[1]][:cross_point]
                    another += self.population[cross[0]][cross_point:]
                    new_pop.append(another)
                    cross = []
            else:
                new_pop.append(self.population[i])

            values.remove(x)

        if len(cross) == 1:
            new_pop.append(self.population[cross[0]])

        self.population = new_pop

    def mutate(self):
        for i in range(self.sizeOfPopulation):
            if np.random.random_sample() <= self.probabilityOfMutation:
                amountOfMutations = np.random.randint(1, (self.amountOfVariables*self.amountOfBits)//10 + 1)
                mutations = [np.random.randint(self.amountOfVariables*self.amountOfBits) for i in range(amountOfMutations)]
                for mutation in mutations:
                    self.population[i][mutation] += 1
                    self.population[i][mutation] %= 2

    def get_best(self):
        best = 0
        for x in range(1, self.sizeOfPopulation):
            if (self.eval_pop[best] < self.eval_pop[x]):
                best = x
        return self.eval_pop[best]

    def get_average(self, pop):
        sum = 0
        for i in pop:
            sum += i
        return (sum/len(pop))

    def get_plot_values(self):
        return (self.best, self.get_best(), self.get_average(self.eval_pop))

    def make_runtime_plot(self, list):
        x = [i for i in range(len(list))]
        bestAll = [i[0] for i in list]
        bestGeneration = [i[1] for i in list]
        average = [i[2] for i in list]
        plt.plot(x, average, label="Average for generation")
        plt.plot(x, bestGeneration, label="Best for generation")
        plt.plot(x, bestAll, label="Best overall")
        plt.legend(loc='lower right')
        plt.show()

pop = Population(obj_func, 250, 2, 0.7, 0.02, -1.5, 1.5, 0.00000001)
pop.make_generations(1000)
