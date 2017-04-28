import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from fuzzython.fsets.triangular import Triangular
from fuzzython.fsets.trapezoid import Trapezoid
from fuzzython.adjective import Adjective
from fuzzython.variable import Variable
from fuzzython.ruleblock import RuleBlock
from fuzzython.systems.mamdani import MamdaniSystem
from fuzzython.systems.sugeno import SugenoSystem


#ZADANIE_1

def displayZ1(block):
    mamdani = MamdaniSystem('ms1', block)
    inputs = {'X': 7.4, 'Y': 4.2}
    res = mamdani.compute(inputs)
    print(res)

    sampled = np.linspace(0, 10, 20)
    x, y = np.meshgrid(sampled, sampled)
    z = np.zeros((len(sampled), len(sampled)))

    for i in range(len(sampled)):
        for j in range(len(sampled)):
            inputs = {'X': x[i, j], 'Y': y[i, j]}
            res = mamdani.compute(inputs)
            z[i, j] = res['first']['Z']

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis',
                           linewidth=0.4, antialiased=True)
    cset = ax.contourf(x, y, z, zdir='z', offset=-1, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='x', offset=11, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='y', offset=11, cmap='viridis', alpha=0.5)
    ax.view_init(30, 200)
    plt.show()

a1 = Trapezoid((-0.1,0), (0,1), (3,1), (5,0))
a2 = Triangular((3,0), (5,1), (7,0))
a3 = Trapezoid((5,0), (7,1), (10, 1), (10.1, 0))
a1 = Adjective('a1', a1)
a2 = Adjective('a2', a2)
a3 = Adjective('a3', a3)
X = Variable('X', 'star', a1, a2, a3)

b1 = Trapezoid((-0.1,0), (0,1), (2,1), (6,0))
b2 = Trapezoid((2,0), (6,1), (10,1), (10.1,0))
b1 = Adjective('b1', b1)
b2 = Adjective('b2', b2)
Y = Variable('Y', 'star', b1, b2)

c1 = Trapezoid((-0.1,0), (0,1), (2,1), (3,0))
c2 = Trapezoid((2,0), (3,1), (5,1), (6,0))
c3 = Trapezoid((5,0), (6,1), (10,1), (10.1,0))
c1 = Adjective('c1', c1)
c2 = Adjective('c2', c2)
c3 = Adjective('c3', c3)

rule1 = 'if X is a3 or Y is b1 then Z is c1'
rule2 = 'if X is a2 and Y is b2 then Z is c2'
rule3 = 'if X is a1 then Z is c3'


Z = Variable('Z', '%', c1, c2, c3, defuzzification='COG', default=0)
block = RuleBlock('first', operators=('MIN', 'MAX', 'ZADEH'), activation='MIN', accumulation='MAX')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

Z = Variable('Z', '%', c1, c2, c3, defuzzification='COA', default=0)
block = RuleBlock('first', operators=('FAND', 'FOR', 'ZADEH'), activation='FAND', accumulation='FOR')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

Z = Variable('Z', '%', c1, c2, c3, defuzzification='COA', default=0)
block = RuleBlock('first', operators=('EPROD','ESUM','SUGENO'), activation='EPROD', accumulation='ESUM')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

Z = Variable('Z', '%', c1, c2, c3, defuzzification='LM', default=0)
block = RuleBlock('first', operators=('FAND', 'NSUM', 'ZADEH'), activation='FAND', accumulation='NSUM')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

Z = Variable('Z', '%', c1, c2, c3, defuzzification='LM', default=0)
block = RuleBlock('first', operators=('BDIF','BSUM','ZADEH'), activation='BDIF', accumulation='BSUM')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

Z = Variable('Z', '%', c1, c2, c3, defuzzification='CM', default=0)
block = RuleBlock('first', operators=('MIN','MAX','ZADEH'), activation='MIN', accumulation='MAX')
block.add_rules(rule1, rule2, rule3, scope=locals())
displayZ1(block)

#ZADANIE_2

def displayZ2(block):
    sugeno = SugenoSystem('ss1', block)
    inputs = {'D': 6.5, 'E': 2.6}
    res = sugeno.compute(inputs)
    print(res)

    sampled = np.linspace(0, 10, 20)
    x, y = np.meshgrid(sampled, sampled)
    z = np.zeros((len(sampled), len(sampled)))

    for i in range(len(sampled)):
        for j in range(len(sampled)):
            inputs = {'D': x[i, j], 'E': y[i, j]}
            res = sugeno.compute(inputs)
            z[i, j] = res['second']

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis',
                           linewidth=0.4, antialiased=True)
    cset = ax.contourf(x, y, z, zdir='z', offset=-1, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='x', offset=11, cmap='viridis', alpha=0.5)
    cset = ax.contourf(x, y, z, zdir='y', offset=11, cmap='viridis', alpha=0.5)
    ax.view_init(30, 200)
    plt.show()

d_male = Triangular((-0.1,0), (0,1), (8, 0))
d_duze = Triangular((0,0), (10,1), (10.1,0))
d_male = Adjective('d_male', d_male)
d_duze = Adjective('d_duze', d_duze)
D = Variable('D', 'star', d_male, d_duze)

e_male = Trapezoid((-0.1, 0), (0,1), (2, 1), (5, 0))
e_srednie = Triangular((2,0), (6,1), (10,0))
e_male = Adjective('e_male', e_male)
e_srednie = Adjective('e_srednie', e_srednie)
E = Variable('E', 'star', e_male, e_srednie)

rule4 = 'if D is d_duze and E is e_srednie then F=2+(7*D)+(3*E)'
rule5 = 'if D is d_male and E is e_male then F=(-2*D)+(5*E)'

block = RuleBlock('second', operators=('MIN', 'MAX', 'ZADEH'), activation='MIN')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)

block = RuleBlock('second', operators=('FAND', 'FOR', 'ZADEH'), activation='FAND', accumulation='FOR')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)

block = RuleBlock('second', operators=('EPROD','ESUM','SUGENO'), activation='EPROD', accumulation='ESUM')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)

block = RuleBlock('second', operators=('FAND', 'NSUM', 'ZADEH'), activation='FAND', accumulation='NSUM')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)

block = RuleBlock('second', operators=('BDIF','BSUM','ZADEH'), activation='BSUM')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)

block = RuleBlock('second', operators=('BDIF','BSUM','ZADEH'), activation='BDIF', accumulation='BSUM')
block.add_rules(rule4, rule5, scope=locals())
displayZ2(block)


#PROJEKT

gp_bad = Triangular((-0.1,0), (0,1), (5,0))
gp_avg = Triangular((0,0), (5,1), (10,0))
gp_good = Triangular((5,0), (10,1), (10.1,0))
gp_bad = Adjective('gp_bad', gp_bad)
gp_avg = Adjective('gp_avg', gp_avg)
gp_good = Adjective('gp_good', gp_good)
gameplay = Variable('gameplay', 'star', gp_bad, gp_avg, gp_good)

st_bad = Triangular((-0.1,0), (0,1), (4,0))
st_avg = Triangular((3,0), (5,1), (8,0))
st_good = Triangular((7,0), (10,1), (10.1,0))
st_bad = Adjective('st_bad', st_bad)
st_avg = Adjective('st_avg', st_avg)
st_good = Adjective('st_good', st_good)
story = Variable('story', 'star', st_bad, st_avg, st_good)

sc_bad = Triangular((-0.1,0), (0,1), (3,0))
sc_avg = Triangular((3,0), (5,1), (7,0))
sc_good = Triangular((7,0), (10,1), (10.1,0))
sc_bad = Adjective('sc_bad', sc_bad)
sc_avg = Adjective('sc_avg', sc_avg)
sc_good = Adjective('sc_good', sc_good)
score = Variable('score', '%', sc_bad, sc_avg, sc_good, defuzzification='COG', default=0)

rule1 = 'if gameplay is gp_bad or story is st_bad then score is sc_bad'
rule2 = 'if gameplay is gp_avg or story is st_avg then score is sc_avg'
rule3 = 'if gameplay is gp_good or story is st_good then score is sc_good'

block = RuleBlock('first', operators=('MIN','MAX','ZADEH'), activation='MIN', accumulation='MAX')
block.add_rules(rule1, rule2, rule3, scope=locals())

mamdani = MamdaniSystem('ms1', block)
inputs = {'gameplay': 6.3, 'story': 8}
res = mamdani.compute(inputs)
print(res)

sampled = np.linspace(0, 10, 20)
x, y= np.meshgrid(sampled, sampled)
z = np.zeros((len(sampled),len(sampled)))

for i in range(len(sampled)):
    for j in range(len(sampled)):
        inputs = {'gameplay': x[i, j], 'story': y[i, j]}
        res = mamdani.compute(inputs)
        z[i, j] = res['first']['score']

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis',
                       linewidth=0.4, antialiased=True)
cset = ax.contourf(x, y, z, zdir='z', offset= -1, cmap='viridis', alpha=0.5)
cset = ax.contourf(x, y, z, zdir='x', offset= 11, cmap='viridis', alpha=0.5)
cset = ax.contourf(x, y, z, zdir='y', offset= 11, cmap='viridis', alpha=0.5)
ax.view_init(30, 200)
plt.show()

#ZADANIE_2

rule4 = 'if gameplay is gp_bad or story is st_bad then z=gameplay*0.4 + story*0.7'
rule5 = 'if gameplay is gp_avg or story is st_avg then z=gameplay*0.5 + story*0.5'
rule6 = 'if gameplay is gp_good or story is st_good then z=gameplay*0.4+ story*0.5'

block = RuleBlock('second', operators=('MIN', 'MAX', 'ZADEH'), activation='MIN')
block.add_rules(rule4, rule5, rule6, scope=locals())

sugeno = SugenoSystem('ss1', block)
inputs = {'gameplay': 6.5, 'story': 9.8}
res = sugeno.compute(inputs)
print(res)

sampled = np.linspace(0, 10, 20)
x, y = np.meshgrid(sampled, sampled)
z = np.zeros((len(sampled),len(sampled)))

for i in range(len(sampled)):
    for j in range(len(sampled)):
        inputs = {'gameplay': x[i, j], 'story': y[i, j]}
        res = sugeno.compute(inputs)
        z[i, j] = res['second']

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap='viridis',
                       linewidth=0.4, antialiased=True)
cset = ax.contourf(x, y, z, zdir='z', offset= -1, cmap='viridis', alpha=0.5)
cset = ax.contourf(x, y, z, zdir='x', offset= 11, cmap='viridis', alpha=0.5)
cset = ax.contourf(x, y, z, zdir='y', offset= 11, cmap='viridis', alpha=0.5)
ax.view_init(30, 200)
plt.show()