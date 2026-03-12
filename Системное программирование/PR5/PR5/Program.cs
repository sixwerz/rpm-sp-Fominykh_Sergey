using System.IO;
using System.Net;

// Загрузка файла
WebClient Client = new WebClient();
Client.DownloadFile("https://professorweb.ru/my/ASP_NET/sites/level1/", "1_1.php");
Console.WriteLine("PHP скачан!");


// Загрузка картинки
string url = "https://i.pinimg.com/736x/2f/ae/8e/2fae8e3fcbd1ffffac0dd64f65de2811.jpg".Trim();
WebClient сlient = new WebClient();
byte[] image = сlient.DownloadData(url);
File.WriteAllBytes("downloaded_image.jpg", image);
Console.WriteLine("картинка скачана!");

// Загрузка CSV файла
string urlCsv = "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv";
string fileName = "open_statistics.csv";

using (WebClient client = new WebClient())
{
    client.DownloadFile(urlCsv, fileName);
}

Console.WriteLine("файл загружен. вывожу первые 10 строк содержимого:\n");

string[] lines = File.ReadAllLines(fileName);

int linesToShow = Math.Min(10, lines.Length);
for (int i = 0; i < linesToShow; i++)
{
    Console.WriteLine(lines[i]);
}