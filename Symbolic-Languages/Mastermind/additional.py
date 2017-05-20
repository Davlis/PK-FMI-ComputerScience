from tkinter import *

class WrongNumberException(Exception):
    pass

def checkNumbers(list, amount):
    for i in list:
        if i not in [x for x in range(1, amount + 1)]:
            raise WrongNumberException

class Conditions:
    def __init__(self):
        self.root = Tk()
        self.root.title("Mastermind: Conditions")
        self.root.resizable(width=False, height=False)
        self.root.geometry('{}x{}+{}+{}'.format(250, 80, 400, 300))
        window = Frame(self.root)
        window.grid()

        self.optionList = [(4, 5, 6, 7, 8), (4, 5, 6, 7, 8), (6, 8, 10, 12, 15, 20, 25)]
        self.chosenNumbers = []
        texts = ["Variables", "Number range", "Rounds"]

        self.amountOfVariables = StringVar()
        self.amountOfVariables.set(self.optionList[0][0])
        self.chosenNumbers.append(self.amountOfVariables)

        self.amountOfNumbers = StringVar()
        self.amountOfNumbers.set(self.optionList[1][2])
        self.chosenNumbers.append(self.amountOfNumbers)

        self.amountOfRounds = StringVar()
        self.amountOfRounds.set(self.optionList[2][3])
        self.chosenNumbers.append(self.amountOfRounds)

        for i in range(3):
            Label(window, text=texts[i]).grid(column=i, row=0)
            OptionMenu(window, self.chosenNumbers[i], *self.optionList[i]).grid(column=i, row=1)
        Button(window, text="Accept", command=self.__conditionButton__).grid(column=0, row=2, rowspan=3)
        self.makeFrame = False
        self.root.mainloop()

    def __conditionButton__(self):
        self.makeFrame = True
        self.root.destroy()

    def getVariables(self):
        return (int(self.amountOfVariables.get()), int(self.amountOfNumbers.get()), int(self.amountOfRounds.get()), self.makeFrame)