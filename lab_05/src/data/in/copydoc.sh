#!/bin/bash

# Название исходного файла без номера
filename="tf-idf"

# Расширение файла
extension=".csv"

# Количество копий
count=96

# Цикл для создания копий
for ((i=1; i<=count; i++))
do
    # Создание нового имени файла
    new_filename="${filename}${i}${extension}"
    
    # Копирование файла
    cp "${filename}0${extension}" "$new_filename"
    
    echo "Создана копия: $new_filename"
done

echo "Копирование завершено."
