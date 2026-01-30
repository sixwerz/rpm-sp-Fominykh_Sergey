# массив из 10 элементов
my_list = ['apple', 'banana', 'cherry', 'date', 'elderberry', 'fig', 'grape', 'cherry', 'apple', 'kiwi']

print("Оригинальный список:")
print(my_list)

# Вывод предпоследнего элемента
print(f"\nПредпоследний элемент: {my_list[-2]}")

# Вывод нескольких элементов по выбору с помощью индекса
print(f"\nЭлемент с индексом 0: {my_list[0]}")
print(f"Элемент с индексом 4: {my_list[4]}")
print(f"Элемент с индексом 7: {my_list[7]}")

# Измените элемента в определённой позиции
my_list[2] = 'coconut'
print(f"\nСписок после изменения элемента с индексом 2:")
print(my_list)

# Выведите элементы в определённом диапазоне
print(f"\nЭлементы с индекса 3 по 6: {my_list[3:7]}")

# Добавление в конец списка список
my_list.append('lemon')
print(f"\nСписок после добавления элемента 'lemon' в конец:")
print(my_list)

# Добавление элемента в середину списка
length = len(my_list) // 2;
my_list.insert(length, 'mango')
print(f"\nСписок после добавления 'mango' в индекс 5:")
print(my_list)

# Подсчет одинаковых элементов
count_apple = my_list.count('apple')
print(f"\nКоличество элементов 'apple': {count_apple}")

# Новый список, и измененный первый элемент
new_list = my_list.copy()
new_list[0] = 'avocado'

print(f"\nОригинальный список:")
print(my_list)
print("Новый список (скопирован и изменен):")
print(new_list)

# Сравнение списков
print(f"\nСписки равны? {my_list == new_list}")
