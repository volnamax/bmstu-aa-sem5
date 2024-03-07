from functions import *
from sorts import *
from tests import *

def description():
    print("\n\nМЕНЮ:")
    print("1. Блочная сортировка")
    print("2. Сортировка бусинами")
    print("3. Сортировка выбором")
    print("4. Измерить время")
    print("0. Выход\n")
    print("Выберите пункт: ", end="")


def menu():
    option = -1
    
    while option != 0:
        description()
        try:
            option = int(input())
        except:
            option = 5
            
        if option == 1:
            arr = input_array_keyboard()
            result = block_sort(arr)
            print("\nРезультат:", result)
        
        elif option == 2:
            arr = input_array_keyboard()
            result = bead_sort(arr)
            print("\nРезультат:", result)
            
        elif option == 3:
            arr = input_array_keyboard()
            result = bead_sort(arr)
            print("\nРезультат:", result)
            
        elif option == 4:
            test_time()

        elif option == 0:
            pass
        
        else:
            print("Необходимо ввести цифру от 0 до 4")