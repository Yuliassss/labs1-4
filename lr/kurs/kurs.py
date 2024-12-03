def minimize_cnf(cnf):
  """
  ������������ ���� � ������� ��������� ������-���-������.

  Args:
    cnf: ������ ������� ���������, �������������� ����.

  Returns:
    ������ ������� ���������, �������������� ���������������� ����.
  """

  # ��� 1: �������� ������� ���������
  implicants = []
  for clause in cnf:
    implicants.append(set(clause))

  # ��� 2: ���������� ������� ���������
  prime_implicants = []
  while True:
    new_implicants = []
    for i in range(len(implicants)):
      for j in range(i + 1, len(implicants)):
        # �������� �� ������� ����� ������������ ����������
        diff = implicants[i].symmetric_difference(implicants[j])
        if len(diff) == 2:
          # �������� ������ ����������
          new_implicant = implicants[i].union(implicants[j]).difference(diff)
          # ���������� ������ ���������� � ������
          new_implicants.append(new_implicant)
          # ������� ������ ��������� ��� "��������������"
          implicants[i] = None
          implicants[j] = None

    # �������� "��������������" ���������
    implicants = [implicant for implicant in implicants if implicant is not None]

    # ���������� ����� ���������
    if new_implicants:
      implicants.extend(new_implicants)
    else:
      # ���� �� ���� ������� ����� ���������, �� ��� ���������� � ������� ����������
      prime_implicants = implicants
      break

  # ��� 3: ���������� ������� ��������
  coverage_table = {}
  for i in range(len(cnf)):
    for j in range(len(prime_implicants)):
      if prime_implicants[j].issubset(cnf[i]):
        if i not in coverage_table:
          coverage_table[i] = []
        coverage_table[i].append(j)

  # ��� 4: ���������� ������������ ��������
  minimal_cover = []
  while coverage_table:
    # ���������� ������� � ������������ ����������� "1"
    max_column = max(coverage_table, key=lambda x: len(coverage_table[x]))
    # ����� ���������� ���������� �� ���������� �������
    prime_implicant_index = coverage_table[max_column][0]
    minimal_cover.append(prime_implicants[prime_implicant_index])
    # �������� ���������� ���������� � ���� "1" � ��� ������
    for row in coverage_table:
      if prime_implicant_index in coverage_table[row]:
        coverage_table[row].remove(prime_implicant_index)
        if not coverage_table[row]:
          del coverage_table[row]

  # �������������� ��������� � ������ ���������
  minimized_cnf = []
  for implicant in minimal_cover:
    minimized_cnf.append(list(implicant))

  return minimized_cnf


# ������ �������������:
cnf = [
  ['a', 'b', 'c'],
  ['a', '~b', 'c'],
  ['~a', 'b', 'c'],
  ['~a', '~b', 'c'],
]

minimized_cnf = minimize_cnf(cnf)

print("���������������� ����:", minimized_cnf) 

