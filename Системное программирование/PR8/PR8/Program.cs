using System;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
namespace Server_Name_1
{
    class Program
    {
        static void Main(string[] args)
        {
            string clientfileExe = "C:\\files\\github\\rpm-Fominykh_Sergey\\rpm-sp-Fominykh_Sergey\\Системное программирование\\PR8\\PR8_client\\PR8_client\\bin\\Debug\\net9.0\\PR8_client";
            Process p = Process.Start(clientfileExe);
            // Создание именованного канала сервером.
            NamedPipeServerStream pipestream = new
            NamedPipeServerStream("Kanal_Name_1");
            // Ждем соединения с клиентом.
            Console.WriteLine("Ждем соединения с клиентом");
            pipestream.WaitForConnection();
            StreamReader reader = new StreamReader(pipestream);
            StreamWriter writer = new StreamWriter(pipestream);
            string ss = "";
            int fl = 0;
            while (ss != "ДОМОЙ")
            {
                if (fl == 0)
                {
                    Console.WriteLine("Ваше сообщение ?");
                    ss = Console.ReadLine();
                    writer.WriteLine(ss);
                    writer.Flush();
                    fl = 1;
                }
                else
                {
                    ss = reader.ReadLine();
                    Console.WriteLine("Получено сообщение от клиента : " + ss);
                    fl = 0;
                }
            }
            Console.WriteLine("Сеанс связи закончен");
            Console.ReadLine();
            // Закрываем канал.
            pipestream.Close();
        }
    }
}