def minimize_cnf(cnf):
  """
  Минимизирует СКНФ с помощью алгоритма Квайна-Мак-Класки.

  Args:
    cnf: Список списков литералов, представляющий СКНФ.

  Returns:
    Список списков литералов, представляющий минимизированную СКНФ.
  """

  # Шаг 1: Создание таблицы импликант
  implicants = []
  for clause in cnf:
    implicants.append(set(clause))

  # Шаг 2: Построение таблицы импликант
  prime_implicants = []
  while True:
    new_implicants = []
    for i in range(len(implicants)):
      for j in range(i + 1, len(implicants)):
        # Проверка на наличие одной отличающейся переменной
        diff = implicants[i].symmetric_difference(implicants[j])
        if len(diff) == 2:
          # Создание нового импликанта
          new_implicant = implicants[i].union(implicants[j]).difference(diff)
          # Добавление нового импликанта в список
          new_implicants.append(new_implicant)
          # Пометка старых импликант как "использованных"
          implicants[i] = None
          implicants[j] = None

    # Удаление "использованных" импликант
    implicants = [implicant for implicant in implicants if implicant is not None]

    # Добавление новых импликант
    if new_implicants:
      implicants.extend(new_implicants)
    else:
      # Если не было создано новых импликант, то все оставшиеся — главные импликанты
      prime_implicants = implicants
      break

  # Шаг 3: Построение таблицы покрытия
  coverage_table = {}
  for i in range(len(cnf)):
    for j in range(len(prime_implicants)):
      if prime_implicants[j].issubset(cnf[i]):
        if i not in coverage_table:
          coverage_table[i] = []
        coverage_table[i].append(j)

  # Шаг 4: Нахождение минимального покрытия
  minimal_cover = []
  while coverage_table:
    # Нахождение столбца с максимальным количеством "1"
    max_column = max(coverage_table, key=lambda x: len(coverage_table[x]))
    # Выбор случайного импликанта из выбранного столбца
    prime_implicant_index = coverage_table[max_column][0]
    minimal_cover.append(prime_implicants[prime_implicant_index])
    # Удаление выбранного импликанта и всех "1" в его строке
    for row in coverage_table:
      if prime_implicant_index in coverage_table[row]:
        coverage_table[row].remove(prime_implicant_index)
        if not coverage_table[row]:
          del coverage_table[row]

  # Преобразование импликант в список литералов
  minimized_cnf = []
  for implicant in minimal_cover:
    minimized_cnf.append(list(implicant))

  return minimized_cnf


# Пример использования:
cnf = [
  ['a', 'b', 'c'],
  ['a', '~b', 'c'],
  ['~a', 'b', 'c'],
  ['~a', '~b', 'c'],
]

minimized_cnf = minimize_cnf(cnf)

print("Минимизированная СКНФ:", minimized_cnf) 

