import random


def block_sort(arr):
    block_size = 10
    blocks = []

    i = 0
    while i < len(arr):
        block = []
        j = i
        while j < i + block_size and j < len(arr):
            block.append(arr[j])
            j += 1
        block.sort()
        blocks.append(block)
        i += block_size

    arr_ind = 0
    while blocks:
        min_ind = 0
        for i in range(1, len(blocks)):
            if blocks[i][0] < blocks[min_ind][0]:
                min_ind = i

        arr[arr_ind] = blocks[min_ind][0]
        arr_ind += 1
        blocks[min_ind].pop(0)

        if not blocks[min_ind]:
            blocks.pop(min_ind)

    return arr


def quick_sort(arr):
    less = []
    equal = []
    greater = []

    if len(arr) > 1:
        pivot = arr[random.randint(0, len(arr) - 1)]
        for x in arr:
            if x < pivot:
                less.append(x)
            elif x == pivot:
                equal.append(x)
            elif x > pivot:
                greater.append(x)
        return quick_sort(less) + equal + quick_sort(greater)

    else:
        return arr


def bead_sort(arr):
    if arr and len(arr) > 0:
        max_value = max(arr)
        # Создаем матрицу бусин: каждая строка представляет число, а столбцы - бусины
        beads = [[0] * max_value for _ in range(len(arr))]

        # Расставляем бусины в матрице в соответствии с значениями массива
        i = 0
        while i < len(arr):
            num = arr[i]
            for j in range(num):
                beads[i][j] = 1
            i += 1
        # Симулируем "падение" бусин
        for j in range(max_value):
            sum = 0
            # Считаем количество бусин в каждом столбце
            for i in range(len(arr)):
                sum += beads[i][j]
                beads[i][j] = 0
            # Опускаем бусины вниз матрицы
            for i in range(len(arr) - sum, len(arr)):
                beads[i][j] = 1
        # Преобразуем матрицу бусин обратно в отсортированный массив
        for i in range(len(arr)):
            arr[i] = beads[i].count(1)
    return arr
