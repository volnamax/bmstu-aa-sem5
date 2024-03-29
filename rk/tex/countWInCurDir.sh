#!/bin/bash

# Проверяем, был ли передан аргумент (слово для поиска)
if [ "$#" -ne 1 ]; then
    echo "Использование: $0 <слово>"
    exit 1
fi

# Слово для поиска
search_word=$1

# Общее количество вхождений слова
total_count=0

# Перебираем все файлы в текущей директории
for file in *; do
    # Проверяем, является ли элемент файлом
    if [ -f "$file" ]; then
        # Подсчитываем количество вхождений слова в файле
        count=$(grep -o "\b$search_word\b" "$file" | wc -l)
        total_count=$((total_count + count))
    fi
done

# Выводим общее количество вхождений
echo "Слово '$search_word' встречается $total_count раз(а) в файлах текущей директории."

