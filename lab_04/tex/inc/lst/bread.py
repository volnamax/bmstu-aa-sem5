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
