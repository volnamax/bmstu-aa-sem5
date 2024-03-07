from time import process_time
import matplotlib.pyplot as plt
import string
import random
import csv

from algorithms import *


def generateStr(string_length=5):
    s1 = ''
    s2 = ''

    for _ in range(string_length):
        s1 += 'a'
        s2 += 'b'
    print(s1, s2)
    return s1, s2


def timeAnalys(function, iterations, length):
    string_1, string_2 = generateStr(length)

    time_start = process_time()

    for i in range(iterations):
        function(string_1, string_2, False)

    time_stop = process_time()

    return (time_stop - time_start) / iterations


def printMeasurementRes(sizes, time_lev_table, time_dam_lev_table,
                        time_lev_recursion, time_dam_lev_recursion):
    print(
        "\n  Длина  | Левенштейн (м) | Дамерау-Левенштейн (м) | Дамерау-Левенштейн  (р) | Дамерау-Левенштейн c кэш (р) \n"
        "---------------------------------------------------------------------------------------------------------")

    ind = 0

    for num in sizes:
        print("%5d    %s%s|%s%s%13.2e   %s%s|%s%s%17.2e       %s%s|%s%s%22.2e   %s%s|%s%s%17.2e       " \
              % (num, set_color, base_color, set_color, base_color,
                 time_lev_table[ind], set_color, base_color, set_color, base_color,
                 time_dam_lev_table[ind], set_color, base_color, set_color, base_color,
                 time_lev_recursion[ind], set_color, base_color, set_color, base_color,
                 time_dam_lev_recursion[ind]))

        ind += 1


def build_graph(sizes, time_lev_table, time_dam_lev_table,
                time_lev_recursion, time_dam_lev_recursion):
    fig1 = plt.figure(figsize=(10, 7))
    plot = fig1.add_subplot()
    plot.plot(sizes, time_lev_table, marker='o', label="Левенштейн (матричная)", )
    plot.plot(sizes, time_dam_lev_table, marker='s', label="Дамерау-Левенштейн (матричная)")
    plot.plot(sizes, time_lev_recursion, marker='^', label="Дамерау-Левенштейн (рекурсивная)")
    plot.plot(sizes, time_dam_lev_recursion, marker='*', label="Дамерау-Левенштейн (рекурсивная с кэшем)")

    plt.legend()
    plt.grid()
    plt.title("Сравнение алгоритмом по времени")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина (кол-во букв)")
    plt.yscale("log")
    plt.savefig('graph.svg', format='svg')  # Сохраняем в векторный форма
    plt.show()


def saveTableToCSV(table_time):
    file_name = "table_time.csv"
    name_rows = ['size', 'lev', 'dam-lev', 'dam-lev-rec', 'dam-lev-rec-cash']
    with open(file_name, mode='w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(name_rows)
        writer.writerows(table_time)


def compareTime():
    time_lev_table = []
    time_dam_lev_table = []
    time_dam_lev_recursion = []
    time_dam_lev_recursion_cash = []

    sizes = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
    time_all = [[0 for _ in range(4)] for _ in range(len(sizes))]

    for n in sizes:
        time_lev_table.append(timeAnalys(levenshtein, 10000, n))
        time_dam_lev_table.append(timeAnalys(damerauLevenshtein, 10000, n))
        if n < 4:
            time_dam_lev_recursion.append(timeAnalys(damerauLevenshteinRecurs, 10000, n))
        else:
            time_dam_lev_recursion.append(timeAnalys(damerauLevenshteinRecurs, 200, n))

        time_dam_lev_recursion_cash.append(timeAnalys(dLRC, 10000, n))

    for i in range(len(sizes)):
        time_all[i][0] = i + 1
        time_all[i][1] = (time_lev_table[i])
        time_all[i][2] = (time_dam_lev_table[i])
        time_all[i][3] = (time_dam_lev_recursion[i])
        time_all[i][4] = (time_dam_lev_recursion_cash[i])

    printMeasurementRes(sizes, time_lev_table, time_dam_lev_table,
                        time_dam_lev_recursion, time_dam_lev_recursion_cash)

    build_graph(sizes, time_lev_table, time_dam_lev_table,
                time_dam_lev_recursion, time_dam_lev_recursion_cash)

    saveTableToCSV(time_all)

set_color = "\x1B"
base_color = "[0m"
green = "[32m"
red = "[31m"
yellow = "[33m"
blue = "[34m"
purple = "[35m"
