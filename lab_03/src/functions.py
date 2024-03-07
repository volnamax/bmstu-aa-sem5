import random
import time

def input_array_keyboard():
    arr = []

    print("Введите элементы массива (в одну строку через пробел):")
    numbers = input().split()

    for i in range(len(numbers)):
        arr.append(int(numbers[i]))
        
    return arr


def get_random_array(size):
    arr = []
    for _ in range(size):
        arr.append(random.randint(-1000, 1000))

    return arr


def get_sorted_array(size):
    arr = get_random_array(size)
    arr.sort()

    return arr


def get_reversed_array(size):
    arr = get_sorted_array(size)
    arr.reverse()

    return arr


def get_time(function_sort, function_arr, size):
    arr = function_arr(size)
    count = 1000
    time_res = 0
    
    for _ in range(count):
        time_1 = time.process_time()
        function_sort(arr)
        time_2 = time.process_time()
        
        time_res += (time_2 - time_1)
        
    return time_res / count