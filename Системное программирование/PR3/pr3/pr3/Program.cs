using System;
using ClosedXML.Excel;

class Program
{
    static void Main()
    {
        string filePath = @"C:\files\github\rpm-Fominykh_Sergey\rpm-sp-Fominykh_Sergey\Системное программирование\PR3\excel.xlsx";
        using (var workbook = new XLWorkbook(filePath))
        {
            var worksheet = workbook.Worksheet(1);
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
}