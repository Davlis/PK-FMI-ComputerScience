#!/usr/bin/env python
from tkinter import *
import tkinter.messagebox as tkMessageBox
from logics import *
from additional import *

class Mastermind:
    def __init__(self):
        self.initVariables()
        self.initLambdas()
        self.initWindow()
        self.initGrids()
        self.initInfoField()
        self.initPlayerInput()
        self.initButtons()
        self.initPreviousAnswers()
        self.root.mainloop()

    def initVariables(self):
        self.amountOfVariables, self.amountOfNumbers, self.amountOfRounds, makeFrame = Conditions().getVariables()
        if not makeFrame:
            quit()
        self.logics = Logika(self.amountOfVariables, self.amountOfNumbers)
        self.buttonElements = [("Check", self.check), ("Liar!", self.liar), ("Reset", self.reset)]
        self.msgboxStrings = [("Winner", "You got correct values!"), ("Loser", "You're out of trials!")]

    def initLambdas(self):
        self.genMsgHeader = lambda: "#" + str(self.logics.amountOfTrials) + ": "
        self.genPrevAns = lambda string, sol: self.genMsgHeader() + string + "  " + str(sol) + "\n"
        self.genInfoText = lambda sol: self.genMsgHeader() + str(sol[0]) + " correct, " + str(sol[1]) + " misplaced, " + str(sol[2]) + " wrong answers"

    def initWindow(self):
        self.root = Tk()
        self.root.title('Mastermind')
        self.root.resizable(width=False, height=False)
        self.root.geometry('{}x{}+{}+{}'.format(350, 180, 400, 300))
        self.window = Frame(self.root)
        self.window.pack()

    def initGrids(self):
        self.infoGrid = Frame(self.window)
        self.numberGrid = LabelFrame(self.window, text=("Your answer (" + str(self.amountOfVariables) + " numbers, 1-" + str(self.amountOfNumbers) + "):"))
        self.buttonGrid = Frame(self.window)
        self.previousGrid = LabelFrame(self.window, text="Previous answers")

        self.infoGrid.grid(column=0, row=0, sticky=E+W)
        self.numberGrid.grid(column=0, row=1, sticky=E+W)
        self.buttonGrid.grid(column=0, row=2, sticky=E+W)
        self.previousGrid.grid(column=0, row=3, sticky=E+W)

    def initInfoField(self):
        self.infoText = StringVar()
        self.infoText.set("Welcome to Mastermind!")
        Message(self.infoGrid, textvariable=self.infoText, justify=LEFT, width=350).pack()

    def initPlayerInput(self):
        self.numberString = StringVar()
        Entry(self.numberGrid, textvariable=self.numberString, width=35, justify=CENTER).pack()

    def initButtons(self):
        self.buttonGridElements = []
        for i in range(4):
            self.buttonGridElements.append(Button(self.buttonGrid, state=NORMAL, text=self.buttonElements[i][0], command=self.buttonElements[i][1]))
            self.buttonGridElements[i].grid(row=0, column=i)

    def initPreviousAnswers(self):
        self.previousAnswers = StringVar()
        Label(self.previousGrid, textvariable=self.previousAnswers, state=DISABLED, height=3, width=35, anchor=NW, justify=LEFT).pack()

    def setButtonState(self, i, statex):
        self.buttonGridElements[i].grid_forget()
        self.buttonGridElements[i] = Button(self.buttonGrid, state=statex, text=self.buttonElements[i][0], command=self.buttonElements[i][1])
        self.buttonGridElements[i].grid(row=0, column=i)

    def endGame(self):
        for i in range(2):
            self.setButtonState(i, DISABLED)
        self.numberString.set(''.join([str(i) for i in self.logics.solution]))

    def check(self):
        try:
            answerString = self.numberString.get()
            assert len(answerString) == self.amountOfVariables
            answer = [int(answerString[i]) for i in range(self.amountOfVariables)]
            checkNumbers(answer, self.amountOfNumbers)
        except (ValueError, AssertionError, WrongNumberException):
            self.infoText.set("Wrong data inserted. Retry...")
            self.numberString.set("")
            return

        logicsReply = self.logics.checkNumbers(answer)
        self.previousAnswers.set(self.genPrevAns(answerString, logicsReply) + self.previousAnswers.get())
        self.infoText.set(self.genInfoText(logicsReply))

        try:
            i=0; assert logicsReply[0] != self.amountOfVariables
            i=1; assert self.logics.amountOfTrials < self.amountOfRounds
        except AssertionError:
            self.endGame()
            tkMessageBox.showinfo(self.msgboxStrings[i][0], self.msgboxStrings[i][1])

    def liar(self):
        if self.logics.correctGame:
            self.infoText.set("Ha, got-imm! Correct answer: ")
        else:
            self.infoText.set("You caught me! Correct answer: ")
        self.endGame()

    def reset(self):
        self.root.destroy()
        self.__init__()