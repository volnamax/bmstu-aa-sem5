import pandas as pd

def round_and_save_csv(input_path, output_path):
    # Загрузка CSV-файла в DataFrame
    df = pd.read_csv(input_path)

    # Преобразование чисел в формат научной нотации и округление до двух знаков после запятой
    rounded_df = df.apply(lambda x: x if x.name == 'len' else x.map(lambda y: format(float('%.2e' % y), ".2e")))
    # Сохранение измененного DataFrame обратно в CSV
    rounded_df.to_csv(output_path, index=False)


# Пример использования
input_file_path = 'time.csv'
output_file_path = 'округленный_ваш_файл.csv'
round_and_save_csv(input_file_path, output_file_path)
