import pymc
import numpy as np
import pandas as pd

#ZADANIE_1

Killer = pymc.Bernoulli('Killer', .5, value=np.ones(1))

pFingerprints = pymc.Lambda('pFingerprints', lambda Killer=Killer: np.where(Killer, .7, .3))
pAlibi = pymc.Lambda('pAlibi', lambda Killer=Killer: np.where(Killer, .8, .4))
pMotive = pymc.Lambda('pMotive', lambda Killer=Killer: np.where(Killer, .9, .5))
pWeapon = pymc.Lambda('pWeapon', lambda Killer=Killer: np.where(Killer, .4, .2))
pDescription = pymc.Lambda('pDescription', lambda Killer=Killer: np.where(Killer, .2, .4))

Fingerprints = pymc.Bernoulli('Fingerprints', pFingerprints, value=np.ones(1))
Alibi = pymc.Bernoulli('Alibi', pAlibi, value=np.ones(1))
Motive = pymc.Bernoulli('Motive', pMotive, value=np.ones(1))
Weapon = pymc.Bernoulli('Weapon', pWeapon, value=np.ones(1))
Description = pymc.Bernoulli('Description', pDescription, value=np.ones(1))

model = pymc.Model([Fingerprints, pFingerprints, Alibi, pAlibi, Motive, pMotive, Weapon, pWeapon, Description, pDescription, Killer])
mcmc = pymc.MCMC(model)
mcmc.sample(10000, 200)

tKiller = mcmc.trace('Killer')[:]
tFingerprints = mcmc.trace('Fingerprints')[:]
tAlibi = mcmc.trace('Alibi')[:]
tMotive = mcmc.trace('Motive')[:]
tWeapon = mcmc.trace('Weapon')[:]
tDescription = mcmc.trace('Description')[:]

dictionary = {
    'Killer': [1 if ii[0] else 0 for ii in tKiller.tolist()],
    'Fingerprints': [1 if ii[0] else 0 for ii in tFingerprints.tolist()],
    'Alibi': [1 if ii[0] else 0 for ii in tAlibi.tolist()],
    'Motive': [1 if ii[0] else 0 for ii in tMotive.tolist()],
    'Weapon': [1 if ii[0] else 0 for ii in tWeapon.tolist()],
    'Description': [1 if ii[0] else 0 for ii in tDescription.tolist()],
}
df = pd.DataFrame(dictionary)

print('pKiller:', float(df[df['Killer'] == 1].shape[0]) / len(df))
print('pAlibi:', float(df[df['Alibi'] == 1].shape[0]) / len(df))
print('pFingerprints:', float(df[df['Fingerprints'] == 1].shape[0]) / len(df))
print('pMotive:', float(df[df['Motive'] == 1].shape[0]) / len(df))
print('pWeapon:', float(df[df['Weapon'] == 1].shape[0]) / len(df))
print('pDescription:', float(df[df['Description'] == 1].shape[0]) / len(df))

print('pKillerFingerprints:', float(df[(df['Killer'] == 1) & (df['Fingerprints'] == 1)].shape[0]) / df[df['Fingerprints'] == 1].shape[0])
print('pKillerAlibiMotive:', float(df[(df['Killer'] == 1) & (df['Alibi'] == 1) & (df['Motive'] == 1)].shape[0]) / \
                          df[(df['Alibi'] == 1) & (df['Motive'] == 1)].shape[0])
print('pKillerFingerprintsWeaponDescription:', float(df[(df['Killer'] == 1) & (1 == df['Fingerprints']) & (df['Weapon'] == 1) & (df['Description'] == 0)].shape[0]) / \
                                   df[(df['Fingerprints'] == 1) & (df['Weapon'] == 1) & (df['Description'] == 0)].shape[0])

#ZADANIE_2

Killer = pymc.Bernoulli('Killer', .1 / .3, value=np.ones(1))

pFingerprints = pymc.Lambda('pFingerprints', lambda Killer=Killer: np.where(Killer, .7, .3))
pNoAlibi = pymc.Lambda('pNoAlibi', lambda Killer=Killer: np.where(Killer, .9, .1))
pMotive = pymc.Lambda('pMotive', lambda Killer=Killer: np.where(Killer, .6, .4))
pWrongDescription = pymc.Lambda('pWrongDescription', lambda Killer=Killer: np.where(Killer, .2, .8))
pRespected = pymc.Lambda('pRespected', lambda Killer=Killer: np.where(Killer, .3, .7))

Fingerprints = pymc.Bernoulli('Fingerprints', pFingerprints, value=np.ones(1))
NoAlibi = pymc.Bernoulli('NoAlibi', pNoAlibi, value=np.ones(1))
Motive = pymc.Bernoulli('Motive', pMotive, value=np.ones(1))
WrongDescription = pymc.Bernoulli('WrongDescription', pWrongDescription, value=np.ones(1))
Respected = pymc.Bernoulli('Respected', pRespected, value=np.ones(1))

model = pymc.Model([Fingerprints, pFingerprints, NoAlibi, pNoAlibi, Motive, pMotive, WrongDescription, pWrongDescription, Respected, pRespected, Killer])
mcmc = pymc.MCMC(model)
mcmc.sample(20000, 2000)

tKiller = mcmc.trace('Killer')[:]
tFingerprints = mcmc.trace('Fingerprints')[:]
tNoAlibi = mcmc.trace('NoAlibi')[:]
tMotive = mcmc.trace('Motive')[:]
tWrongDescription = mcmc.trace('WrongDescription')[:]
tRespected = mcmc.trace('Respected')[:]

dictionary = {
    'Killer': [1 if ii[0] else 0 for ii in tKiller.tolist()],
    'Fingerprints': [1 if ii[0] else 0 for ii in tFingerprints.tolist()],
    'NoAlibi': [1 if ii[0] else 0 for ii in tNoAlibi.tolist()],
    'Motive': [1 if ii[0] else 0 for ii in tMotive.tolist()],
    'WrongDescription': [1 if ii[0] else 0 for ii in tWrongDescription.tolist()],
    'Respected': [1 if ii[0] else 0 for ii in tRespected.tolist()],
}
df = pd.DataFrame(dictionary)

print('pKiller:', float(df[df['Killer'] == 1].shape[0]) / len(df))
print('pFingerprints:', float(df[df['Fingerprints'] == 1].shape[0]) / len(df))
print('pNoAlibi:', float(df[df['NoAlibi'] == 1].shape[0]) / len(df))
print('pMotive:', float(df[df['Motive'] == 1].shape[0]) / len(df))
print('pWrongDescription:', float(df[df['WrongDescription'] == 1].shape[0]) / len(df))
print('pRespected:', float(df[df['Respected'] == 1].shape[0]) / len(df))

pA = (float(df[(df['Killer'] == 1) & (df['NoAlibi'] == 1) & (df['Respected'] == 1)].shape[0]) / \
            df[(df['NoAlibi'] == 1) & (df['Respected'] == 1)].shape[0])
pB=(float(df[(df['Killer'] == 1) & (df['NoAlibi'] == 1) & (df['WrongDescription'] == 1)].shape[0]) / \
            df[(df['NoAlibi'] == 1) & (df['WrongDescription'] == 1)].shape[0])
pC=(float(df[(df['Killer'] == 1) & (df['Motive'] == 1) & (df['WrongDescription'] == 0)].shape[0]) / \
            df[(df['Motive'] == 1) & (df['WrongDescription'] == 1)].shape[0])

print('pKillerA:', pA, '\npKillerB:', pB, '\npKillerC:', pC)
print("Bayes should arrest suspect ", end='', sep='')
if pA>pB and pA>pC:
    print("A")
elif pB>pC:
    print("B")
else:
    print("C")
