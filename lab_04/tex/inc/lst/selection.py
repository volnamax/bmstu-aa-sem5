def selection_sort(arr):
    size = len(arr)

    for ind in range(size):
        min_ind = ind

        for j in range(ind + 1, size):
            if arr[j] < arr[min_ind]:
                min_ind = j
        arr[ind], arr[min_ind] = arr[min_ind], arr[ind]

    return arr