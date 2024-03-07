from algorithms import *
from measurement import compareTime

PASS = 0
EXIT = -1
LEVENSHTEIN = 1
DAMERAU_LEVENSHTEIN = 2
DLR = 3
DLRC = 4
TIME = 5
QUIT = 6

ERR_COST = -2

MAX_STRING_LENGTH = 10
MAX_MENU_CHOICE = 6


def main():
    num_menu = PASS
    cost_error = -1

    while num_menu != QUIT:
        try:
            num_menu = int(menu())
            if not 1 <= num_menu <= MAX_MENU_CHOICE:
                raise ValueError(f"Неверный выбор. Пожалуйста, введите число от 1 до {MAX_MENU_CHOICE}.")
            if num_menu == TIME:
                compareTime()
                continue

            strx, stry = inputStrs()
            if not checkStrs(strx, stry):
                continue

            if num_menu == LEVENSHTEIN:
                cost_error = levenshtein(strx, stry, True)
            elif num_menu == DAMERAU_LEVENSHTEIN:
                cost_error = damerauLevenshtein(strx, stry, True)
            elif num_menu == DLR:
                cost_error = damerauLevenshteinRecurs(strx, stry)
            elif num_menu == DLRC:
                cost_error = dLRC(strx, stry)
            elif num_menu == EXIT:
                compareTime()
            else:
                print("Неверный выбор")
            
            if num_menu in [DLR, DLRC]:
                cost_error = checkCostCreateMtr(cost_error, strx, stry)

            printRes(cost_error, strx, stry)
        except ValueError as e:
            print(f"Ошибка: {e}")


def checkCostCreateMtr(cost_error, strx, stry):
    if cost_error == damerauLevenshtein(strx, stry):
        return damerauLevenshtein(strx, stry, True)
    return ERR_COST


def printRes(cost_error, strx, stry):
    print("Расстояние    = ", cost_error[len(strx)][len(stry)])
    print()
    # Печать верхней строки
    padding = 4  # ширина ячейки, можно настроить по желанию
    header = " ".ljust(padding) + "|" + " ".ljust(padding) + "|"

    # Подготовка строки с символами stry
    for char in stry:
        header += char.center(padding) + "|"
    print(header)
    print("-" * len(header))

    # Печать строк матрицы
    for i, row in enumerate(cost_error):
        # Если i == 0, то буквы из strx нет, иначе используем символ из strx
        current_char = " " if i == 0 else strx[i - 1]
        line = current_char.center(padding) + "|"

        # Добавление числовых значений из матрицы в строку
        for num in row:
            line += str(num).center(padding) + "|"
        print(line)
        print("-" * len(header))


def checkStrs(strx, stry):
    if len(strx) > MAX_STRING_LENGTH or len(stry) > MAX_STRING_LENGTH:
        print(f"Неверная длина строк. Максимально допустимая длина - {MAX_STRING_LENGTH}.")
        return False
    if not strx.isalpha() or not stry.isalpha():
        print("Неверные строки. Допускаются только буквенные символы.")
        return False
    return True


def inputStrs():
    return input("Введите первую строку > "), input("Введите вторую строку > ")


def checkInt(num):
    try:
        num = int(num)
        if 1 <= num <= MAX_MENU_CHOICE:
            return True
        else:
            print(f"Неверный выбор. Пожалуйста, введите число от 1 до {MAX_MENU_CHOICE}.")
    except ValueError:
        print("Неверный выбор. Пожалуйста, введите действительное число.")
    return False


def menu():
    print("             МЕНЮ       ")
    print("1 - Левенштейн;")
    print("2 - Дамерау-Левенштейн;")
    print("3 - Дамерау-Левенштейн {рекурсивно};")
    print("4 - Дамерау-Левенштейн {рекурсивно, кэш};")
    print("5 - замерный эксперимент;")
    print("6 - выход.")
    print("")
    return input("Выберите пункт меню > ")


if __name__ == '__main__':
    main()
