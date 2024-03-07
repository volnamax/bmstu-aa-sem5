import matplotlib.pyplot as plt

from sorts import *
from functions import *


def random_arr_graph(arr_random_block, arr_random_quick, arr_random_selection):
    lengths = [i for i in range(100, 1001, 100)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_random_block, label = "Блочная")
    plot.plot(lengths, arr_random_quick, label = "Быстрая")
    plot.plot(lengths, arr_random_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()


def reversed_arr_graph(arr_reversed_block, arr_reversed_quick, arr_reversed_selection):
    lengths = [i for i in range(100, 1001, 100)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_reversed_block, label = "Блочная")
    plot.plot(lengths, arr_reversed_quick, label = "Быстрая")
    plot.plot(lengths, arr_reversed_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()


def sorted_arr_graph(arr_sorted_block, arr_sorted_quick, arr_sorted_selection):
    lengths = [i for i in range(100, 1001, 100)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_sorted_block, label = "Блочная")
    plot.plot(lengths, arr_sorted_quick, label = "Быстрая")
    plot.plot(lengths, arr_sorted_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()


def random_arr_graph_big(arr_random_block, arr_random_selection):
    lengths = [i for i in range(2000, 5001, 1000)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_random_block, label = "Блочная")
    plot.plot(lengths, arr_random_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()


def reversed_arr_graph_big(arr_reversed_block, arr_reversed_selection):
    lengths = [i for i in range(2000, 5001, 1000)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_reversed_block, label = "Блочная")
    plot.plot(lengths, arr_reversed_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()


def sorted_arr_graph_big(arr_sorted_block, arr_sorted_selection):
    lengths = [i for i in range(2000, 5001, 1000)]
    
    fig = plt.figure(figsize=(7, 5))
    plot = fig.add_subplot()
    plot.plot(lengths, arr_sorted_block, label = "Блочная")
    plot.plot(lengths, arr_sorted_selection, label = "Выбором")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина массива")

    plt.show()
    

def test_time():
    arr_random_block = []
    arr_random_quick = []
    arr_random_selection = []

    arr_reversed_block = []
    arr_reversed_quick = []
    arr_reversed_selection = []

    arr_sorted_block = []
    arr_sorted_quick = []
    arr_sorted_selection = []
    
    for i in range(100, 1001, 100):
        arr_random_block.append(get_time(block_sort, get_random_array, i))
        arr_random_quick.append(get_time(bead_sort, get_random_array, i))
        arr_random_selection.append(get_time(bead_sort, get_random_array, i))

        arr_reversed_block.append(get_time(block_sort, get_reversed_array, i))
        arr_reversed_quick.append(get_time(bead_sort, get_reversed_array, i))
        arr_reversed_selection.append(get_time(bead_sort, get_reversed_array, i))

        arr_sorted_block.append(get_time(block_sort, get_sorted_array, i))
        arr_sorted_quick.append(get_time(bead_sort, get_sorted_array, i))
        arr_sorted_selection.append(get_time(bead_sort, get_sorted_array, i))

        print("Выполнено", i // 100, "/ 10 замеров\n")
        
    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ, БЫСТРОЙ СОРТИРОВОК, СОРТИРОВКИ ВЫБОРОМ (НЕОТСОРТИРОВАННЫЙ МАССИВ)")
    print(" %3s | %8s | %8s | %8s\n" %("i", "Блочная", "Быстрая", "Выбором"))
    for i in range(10):
        print(" %3d | %8f | %8f | %8f\n" %((i + 1) * 100, arr_random_block[i] * 1000, arr_random_quick[i] * 1000, arr_random_selection[i] * 1000)) 
    print("\n")

    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ, БЫСТРОЙ СОРТИРОВОК, СОРТИРОВКИ ВЫБОРОМ (ОТСОРТИРОВАННЫЙ В ОБРАТНОМ ПОРЯДКЕ МАССИВ)")
    print(" %3s | %8s | %8s | %8s\n" %("i", "Блочная", "Быстрая", "Выбором"))
    for i in range(10):
        print(" %3d | %8f | %8f | %8f\n" %((i + 1) * 100, arr_reversed_block[i] * 1000, arr_reversed_quick[i] * 1000, arr_reversed_selection[i] * 1000)) 
    print("\n")

    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ, БЫСТРОЙ СОРТИРОВОК, СОРТИРОВКИ ВЫБОРОМ (ОТСОРТИРОВАННЫЙ МАССИВ)")
    print(" %3s | %8s | %8s | %8s\n" %("i", "Блочная", "Быстрая", "Выбором"))
    for i in range(10):
        print(" %3d | %8f | %8f | %8f\n" %((i + 1) * 100, arr_sorted_block[i] * 1000, arr_sorted_quick[i] * 1000, arr_sorted_selection[i] * 1000)) 
    print("\n")
        
    random_arr_graph(arr_random_block, arr_random_quick, arr_random_selection)
    reversed_arr_graph(arr_reversed_block, arr_reversed_quick, arr_reversed_selection)
    sorted_arr_graph(arr_sorted_block, arr_sorted_quick, arr_sorted_selection)

    arr_random_block = []
    arr_random_selection = []

    arr_reversed_block = []
    arr_reversed_selection = []

    arr_sorted_block = []
    arr_sorted_selection = []

    for i in range(2000, 5001, 1000):
        arr_random_block.append(get_time(block_sort, get_random_array, i))
        arr_random_selection.append(get_time(bead_sort, get_random_array, i))

        arr_reversed_block.append(get_time(block_sort, get_reversed_array, i))
        arr_reversed_selection.append(get_time(bead_sort, get_reversed_array, i))

        arr_sorted_block.append(get_time(block_sort, get_sorted_array, i))
        arr_sorted_selection.append(get_time(bead_sort, get_sorted_array, i))

        print("Выполнено", (i - 1000) // 1000, "/ 4 замеров\n")

    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ СОРТИРОВКИ И СОРТИРОВКИ ВЫБОРОМ (НЕОТСОРТИРОВАННЫЙ МАССИВ)")
    print(" %3s | %8s | %8s\n" %("i", "Блочная", "Выбором"))
    for i in range(4):
        print(" %3d | %8f | %8f\n" %(2000 + i * 1000, arr_random_block[i] * 1000, arr_random_selection[i] * 1000)) 
    print("\n")

    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ СОРТИРОВКИ И СОРТИРОВКИ ВЫБОРОМ (ОТСОРТИРОВАННЫЙ В ОБРАТНОМ ПОРЯДКЕ МАССИВ)")
    print(" %3s | %8s | %8s\n" %("i", "Блочная", "Выбором"))
    for i in range(4):
        print(" %3d | %8f | %8f\n" %(2000 + i * 1000, arr_reversed_block[i] * 1000, arr_reversed_selection[i] * 1000)) 
    print("\n")

    print("ТАБЛИЦА ДЛЯ АЛГОРИТМОВ БЛОЧНОЙ СОРТИРОВКИ И СОРТИРОВКИ ВЫБОРОМ (ОТСОРТИРОВАННЫЙ МАССИВ)")
    print(" %3s | %8s | %8s\n" %("i", "Блочная", "Выбором"))
    for i in range(4):
        print(" %3d | %8f | %8f\n" %(2000 + i * 1000, arr_sorted_block[i] * 1000, arr_sorted_selection[i] * 1000)) 
    print("\n")

    random_arr_graph_big(arr_random_block, arr_random_selection)
    reversed_arr_graph_big(arr_reversed_block, arr_reversed_selection)
    sorted_arr_graph_big(arr_sorted_block, arr_sorted_selection)
