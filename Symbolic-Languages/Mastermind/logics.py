import numpy as np

class RegulyGry:
    def __init__(self, amountOfVariables, amountOfNumbers):
        self.amountOfVariables = amountOfVariables
        self.amountOfNumbers = amountOfNumbers
        self.solution = [np.random.randint(1, amountOfNumbers + 1) for i in range(amountOfVariables)]

    def checkNumbers(self, listOfAnswers):
        correct = sum((1 if listOfAnswers[i] == self.solution[i] else 0) for i in range(self.amountOfVariables))
        misplaced = sum(min(self.solution.count(i), listOfAnswers.count(i)) for i in range(1, self.amountOfNumbers+1)) - correct
        wrong = self.amountOfVariables - correct - misplaced
        return [correct, misplaced, wrong]

class Logika(RegulyGry):
    def __init__(self, amountOfVariables, amountOfNumbers):
        super().__init__(amountOfVariables, amountOfNumbers)
        self.amountOfTrials = 0
        self.previousAnswers = [0 for i in range(amountOfVariables)]
        self.correctGame = np.random.randint(0, 4) != 0

        print(self.solution)
        print(self.correctGame)

    def checkNumbers(self, listOfAnswers):
        self.amountOfTrials += 1
        try:
            assert self.correctGame
            return super().checkNumbers(listOfAnswers)
        except AssertionError:
            if listOfAnswers != self.previousAnswers:
                self.fakeAnswers = super().checkNumbers([np.random.randint(1, self.amountOfNumbers + 1) for i in range(self.amountOfVariables)])
                self.previousAnswers = listOfAnswers
            return self.fakeAnswers









"""
        if self.correctGame or sol[0] == self.amountOfVariables:
            return sol
        elif listOfAnswers == self.previousAnswers:
            return self.previousSol
        else:
            correct = np.random.randint(0, self.amountOfVariables)
            misplaced = np.random.randint(0, self.amountOfVariables+1-correct)
            wrong = self.amountOfVariables - correct - misplaced
            self.previousAnswers = listOfAnswers
            self.previousSol = [correct, misplaced, wrong]
            return self.previousSol
"""