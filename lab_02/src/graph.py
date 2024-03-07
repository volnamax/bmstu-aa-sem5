import pandas as pd
import matplotlib.pyplot as plt

def plot_graph(file_path, title, count):
    # Считываем данные из CSV файла
    df = pd.read_csv(file_path)

    # Извлекаем данные из DataFrame
    sizes = df['Size']
    classic_times = df['Classic']
    winograd_times = df['Winograd']
    winograd_opt_times = df['WinogradOpt']
    # Сделаем y-ось логарифмической

    if count == 4:
        stassen_times = df['Strassen']
        plt.plot(sizes, stassen_times, label='Штрассена', marker='*')

    # Строим графики с разными маркерами
    plt.plot(sizes, classic_times, label='Классический', marker='o')
    plt.plot(sizes, winograd_times, label='Винограда', marker='s')
    plt.plot(sizes, winograd_opt_times, label='Винограда (опт.)', marker='^')
    plt.grid(True)
    # Добавляем легенду
    plt.legend()
    if (count == 4):
        plt.yscale('log')
    # Добавляем заголовок и подписи осей
    plt.xlabel('Размер матриц (элементов)')
    plt.ylabel('Время (нс))')




    # Сохраняем график в формате PDF
    plt.savefig(f'{title}.pdf')
    plt.show()

# Построение графика для файла 'oneToHundred.csv'
plot_graph('oneToHundred.csv', 'График для oneToHundred', 3)

# Построение графика для файла 'twoToHundred.csv'
plot_graph('twoToHundred.csv', 'График для twoToHundred', 4)
