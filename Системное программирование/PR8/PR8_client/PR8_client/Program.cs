using System;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
namespace Klient_Name_1
{
    class Program
    {
        static void Main(string[] args)
        {
            string ss;
            //Создаем именованный канал клиентом.
            NamedPipeClientStream pipestream = new
            NamedPipeClientStream("Kanal_Name_1");
            //Соединяемся с каналом.
            pipestream.Connect();
            StreamReader reader = new StreamReader(pipestream);
            StreamWriter writer = new StreamWriter(pipestream);
            int fl = 0;
            do
            {
                if (fl == 0)
                {
                    ss = reader.ReadLine();
                    Console.WriteLine("Получено сообщение от сервера: " + ss);
                    fl = 1;
                }
                else
                {
                    Console.WriteLine("Сообщение от клиента ?");
                    ss = Console.ReadLine();
                    writer.WriteLine(ss);
                    writer.Flush();
                    fl = 0;
                }
            }
            while (ss != "ДОМОЙ");
            Console.WriteLine("Сеанс связи закончен");
            Console.ReadLine();
            // Закрываем канал.
            pipestream.Close();
        }
    }
}