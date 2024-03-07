def block_sort(arr):
    if len(arr) <= 1:
        return arr
    else:
        mid = len(arr) // 2
        # Рекурсивно сортируем левую и правую половины массива
        left = block_sort(arr[:mid])
        right = block_sort(arr[mid:])
        # Объединяем отсортированные половины с помощью функции merge
        return merge(left, right)

# Функция для слияния двух отсортированных массивов
def merge(left, right):
    result = []  
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result += left[i:]
    result += right[j:]

    return result
