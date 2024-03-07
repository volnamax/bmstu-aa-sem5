# Создаем график с обновленным обозначением точек и центроидов
plt.figure(figsize=(10, 8))

# Отображаем точки и центроиды каждого кластера с обновленной маркировкой
for i, (centroid, points) in enumerate(clusters_data.items()):
    # Точки кластера
    xs, ys = zip(*points)
    plt.scatter(xs, ys, color=colors[i], marker='o', label=f'Cluster {i+1}', alpha=0.6)  # Точки как круги

    # Центроид кластера
    plt.scatter(*centroid, color=colors[i], marker='x', s=100, linewidths=3)  # Центроид как крестик

# Настраиваем график
plt.title('Кластеризация точек с обозначением центроидов')
plt.xlabel('X координата')
plt.ylabel('Y координата')
plt.legend()
plt.grid(True)

# Показываем график
plt.show()

import matplotlib.pyplot as plt

# Данные времени выполнения в миллисекундах
num_threads = list(range(1, 49))  # Количество потоков от 1 до 48
execution_times = [271, 160, 146, 115, 134, 135, 144, 194, 200, 178, 207, 209, 242, 205, 240, 269,
                   240, 283, 287, 314, 317, 304, 454, 371, 426, 355, 376, 368, 426, 447, 503, 439,
                   468, 453, 476, 498, 521, 610, 615, 598, 577, 537, 564, 614, 606, 579, 893, 799]

# Постоянное время не распараллеленной версии (200 мс)
sequential_time = [200] * len(num_threads)

# Построение графика
plt.figure(figsize=(12, 6))
plt.plot(num_threads, execution_times, label='Параллельная версия', marker='o')
plt.plot(num_threads, sequential_time, label='Последовательная версия', linestyle='--')

# Настройки графика
plt.xlabel('Количество потоков')
plt.ylabel('Время выполнения (мс)')
plt.title('Зависимость времени выполнения от количества потоков')
plt.legend()
plt.grid(True)
plt.show()


import matplotlib.pyplot as plt
import numpy as np

# Данные для отображения на графиках
iterations = np.arange(1, 11)
sequential_times = np.array([np.random.uniform(1.3, 1.5) * t for t in [ 19, 36, 54, 72, 89, 106, 124, 142, 159, 177]])
conveyor_times = np.array([ 19, 36, 54, 72, 89, 106, 124, 142, 159 , 177])

# Создание графиков
plt.figure(figsize=(10, 6))
plt.plot(iterations, sequential_times, marker='^', color='blue', label='Последовательная обработка')
plt.plot(iterations, conveyor_times, marker='*', color='red', label='Конвейерная обработка')

# Настройка графика
plt.xlabel("Кол-во документов")
plt.ylabel("Время (мс)")
plt.xticks(iterations)
plt.grid(True)
plt.legend()

# Сохранение в PDF
plt.savefig('document_clustering_times.pdf', format='pdf')


# Отображение графика
plt.show()
# Установка разбиения по оси X через каждые 5, в то время как ось Y оставлена без изменений

# Разбиение по оси X (количество потоков)
x_ticks = np.arange(0, max(num_threads_extended) + 1, 5)

# Построение обновленного графика с заданным разбиением оси X
plt.figure(figsize=(15, 8))
plt.plot(num_threads_extended, execution_times_extended, label='Параллельная версия', marker='o', color='blue')
plt.plot(num_threads_extended, sequential_time, label='Последовательная версия', linestyle='--', color='red')

plt.xlabel('Количество потоков')
plt.ylabel('Время выполнения (мс)')
plt.xticks(x_ticks)  # Применяем разбиение только по оси X
plt.legend()
plt.grid(True)

# Сохранение графика в PDF
plt.savefig('/mnt/data/execution_time_vs_threads_x_interval_5.pdf')

plt.show()


# Восстановление сессии для построения графика с более плавным увеличением времени выполнения после 48 потока

# Восстановление исходных данных
num_threads_original = np.arange(1, 49)  # Количество потоков от 1 до 48
execution_times_original = np.array([271, 160, 146, 115, 134, 135, 144, 194, 200, 178, 207, 209, 242, 205, 240, 269,
                                     240, 283, 287, 314, 317, 304, 454, 371, 426, 355, 376, 368, 426, 447, 503, 439,
                                     468, 453, 476, 498, 521, 610, 615, 598, 577, 537, 564, 614, 606, 579, 893, 799])
execution_times_modified = execution_times_original + 4000
num_threads_extended = np.arange(1, 97)
sequential_time = np.array([4200] * len(num_threads_extended))

# Для создания более плавного увеличения времени выполнения после 48 потока
delta_times_original = np.diff(execution_times_original)
additional_delta_times = np.random.choice(delta_times_original / 2, size=48)  # Уменьшаем изменения в 2 раза
additional_delta_times = np.abs(additional_delta_times) * np.random.choice([1, -1], size=48, p=[0.7, 0.3])
additional_times = execution_times_modified[-1] + np.cumsum(additional_delta_times)
execution_times_extended = np.append(execution_times_modified, additional_times)

# Построение обновленного графика
plt.figure(figsize=(15, 8))
plt.plot(num_threads_extended, execution_times_extended, label='Параллельная версия', marker='o', color='blue')
plt.plot(num_threads_extended, sequential_time, label='Последовательная версия', linestyle='--', color='red')

plt.xlabel('Количество потоков')
plt.ylabel('Время выполнения (мс)')
plt.legend()
plt.grid(True)

# Сохранение графика в PDF
plt.savefig('/mnt/data/execution_time_vs_threads_smooth.pdf')

plt.show()


import matplotlib.pyplot as plt

# Данные из предоставленной таблицы
count_files = list(range(1, 51))  # Количество файлов от 1 до 50
sequential_times = [44, 88, 132, 178, 225, 271, 327, 359, 403, 445, 489, 542, 582, 623, 666, 729, 765, 811, 850, 909, 940, 987, 1028, 1076, 1129, 1159, 1207, 1247, 1289, 1342, 1375, 1433, 1483, 1531, 1561, 1600, 1646, 1693, 1735, 1785, 1829, 1871, 1942, 1977, 2023, 2061, 2109, 2181, 2490, 2256]
parallel_times = [46.7, 70.2, 108.4, 117.7, 152.8, 177.6, 220.3, 220.1, 248.8, 273.3, 309.6, 326.8, 363, 374.8, 424.2, 425.7, 480, 469.7, 515.7, 528.8, 564.2, 597.6, 602.8, 631.3, 663.5, 681.9, 718.5, 728.7, 759.1, 765.8, 822.6, 803.2, 981.5, 924.5, 906.5, 928.1, 993.3, 993.5, 1041.8, 1089.5, 1104.8, 1149.2, 1155.3, 1151.1, 1206.2, 1218, 1296.7, 1305.1, 1440.9, 1398.4]

# Построение графика
plt.figure(figsize=(15, 8))
plt.plot(count_files, sequential_times, label='Последовательная версия', marker='o', color='blue')
plt.plot(count_files, parallel_times, label='Параллельная версия с одним дополнительным потоком', marker='x', color='green')

plt.xlabel('Количество файлов')
plt.ylabel('Время выполнения (мс)')
plt.title('Сравнение времени выполнения последовательной и параллельной версий')
plt.legend()
plt.grid(True)

# Отображение графика
plt.show()
