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


import matplotlib.pyplot as plt

# Data from the table
count_file = list(range(1, 25))
sequential_version = [44, 88, 133, 177, 222, 264, 309, 354, 402, 443, 484, 530, 573, 690, 661, 713, 763, 798, 846, 898, 930, 970, 1024, 1061]
conveyor_version = [35, 69, 79, 108, 123, 149, 164, 193, 208, 229, 249, 268, 292, 326, 368, 390, 384, 406, 443, 478, 491, 489, 503, 577]

# Plotting the graph
plt.figure(figsize=(10, 6))
plt.plot(count_file, sequential_version, label='Sequential Version (ms)', marker='o')
plt.plot(count_file, conveyor_version, label='Conveyor Version (ms)', marker='x')
plt.title('Performance Comparison: Sequential vs Conveyor Versions')
plt.xlabel('Count File (request)')
plt.ylabel('Execution Time (ms)')
plt.xticks(count_file)
plt.grid(True)
plt.legend()
plt.show()
