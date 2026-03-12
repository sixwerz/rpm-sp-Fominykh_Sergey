using System;
using System.Threading;
using ClosedXML.Excel;

string filePath = @"C:\files\github\rpm-Fominykh_Sergey\rpm-sp-Fominykh_Sergey\Системное программирование\PR6\excel.xlsx";

Thread thread1 = new Thread(func1);
Thread thread2 = new Thread(func2);

thread1.Start();
thread2.Start();

thread1.Join();
thread2.Join();

Console.WriteLine("\nВсе потоки завершены!");


void func1()  // Первый лист
{
    Thread.Sleep(5000);
    ReadExcelSheet(filePath, 1);
}

void func2()  // 🔹 Второй лист
{
    ReadExcelSheet(filePath, 2);
}
void ReadExcelSheet(string filePath, int sheetNumber)
{

    using (var workbook = new XLWorkbook(filePath))
    {
        var worksheet = workbook.Worksheet(sheetNumber);
        var firstCell = worksheet.FirstCellUsed();
        var lastCell = worksheet.LastCellUsed();
        var range = worksheet.Range(firstCell.Address, lastCell.Address);

        foreach (var row in range.Rows())
        {
            foreach (var cell in row.Cells())
            {
                Console.Write($"{cell.Value}\t");
            }
            Console.WriteLine();
        }
    }
}

