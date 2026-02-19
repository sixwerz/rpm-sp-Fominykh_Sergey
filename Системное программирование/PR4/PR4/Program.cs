using System.Diagnostics;
using System.Runtime.InteropServices.Marshalling;

// Получение всех запущенных процессов
foreach (Process process in Process.GetProcesses()) {
    Console.WriteLine($"ID: {process.Id} Name: {process.ProcessName}");
}

// Получение всех потоков
Process proc = Process.GetProcessesByName("devenv")[0];
ProcessThreadCollection processThreads = proc.Threads;

foreach (ProcessThread thread in processThreads) {
    Console.WriteLine($"Thread Id: {thread.Id}");
}

// Добавление стороннего процесса
Process.Start(@"C:\Program Files\Paint.NET\paintdotnet");
Process.Start(@"C:\Program Files\Zen Browser\zen", "https://www.google.com");