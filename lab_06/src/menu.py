from constants import *
from utils import parseFullCombinations, parseAntAlg, parseAll, updateFile, printMatrix
from test import parametrization, testTime

def menu():
    option = -1
    while (option != EXIT):
        try:
            option = int(input(MESSAGE))
        except:
            option = -1
        if (option == ALL_COMB):
            parseFullCombinations()
        elif (option == ANT_ALG):
            parseAntAlg()
        elif (option == ALG_ALL):
            parseAll()
        elif (option == PARAMETRIC):
            parametrization(type)
        elif (option == TEST):
            testTime()
        elif (option == UPDATE_DATA):
            updateFile()
        elif (option == SHOW_DATA):
            printMatrix()
        elif (option == EXIT):
            print("Завершение выполнения")
        else:
            print("Повторите ввод")
