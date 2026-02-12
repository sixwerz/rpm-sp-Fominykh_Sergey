import os
import pandas as pd

df = pd.read_excel(r'C:\files\github\rpm-Fominykh_Sergey\rpm-sp-Fominykh_Sergey\Системное программирование\PR3\excel.xlsx', sheet_name=['Лист1', 'Лист2'])
print(df['Лист1'].head())
print(df['Лист2'].head())
