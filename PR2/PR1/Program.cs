using System;

public class Person
{
    // Поля базового класса
    protected string Name;  // Защищенное поле — доступно в подклассах
    protected int Age;  // Защищенное поле — доступно в подклассах

    // Конструктор базового класса
    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    // Метод, помеченный как виртуальный, чтобы можно было переопределить в подклассе
    public virtual void DisplayInfo()
    {
        Console.WriteLine($"Имя: {Name} | Возраст: {Age}");
    }
}

// Подкласс Сотрудник
public class Employee : Person
{
    private string Role;    // должность

    // Конструктор подкласса
    public Employee(string name, int age, string role) : base(name, age)
    {
        // Передача данных в базовый класс через вызов base
        Role = role; // Инициализация собственного поля
    }

    // Переопределяем метод базового класса
    public override void DisplayInfo()
    {
        // Данные из базового класса доступны благодаря модификатору protected
        Console.WriteLine($"Имя сотрудника: {Name} | Возраст: {Age} | Должность: {Role}");
    }
}

// Подкласс ребенок
public class Baby : Person
{
    private string Parents; // Кто мама

    // Конструктор подкласса
    public Baby(string name, int age, string parents) : base(name, age)
    {
        // Передача данных в базовый класс через вызов base
        Parents = parents;
    }

    // Переопределяем метод базового класса
    public override void DisplayInfo()
    {
        // Данные из базового класса доступны благодаря модификатору protected
        Console.WriteLine($"Младенец: {Name} | Возраст: {Age} месяцев | Мама: {Parents}");
    }
}

// Основной класс программы
class Program
{
    static void Main(string[] args)
    {
        // Создаем объекты
        Person person = new Person("Виталя", 20);
        Employee employee = new Employee("Серега", 22, "Программист");
        Baby baby = new Baby("Семен", 9, "Натаьля");

        Console.WriteLine("--- Результат ---");

        person.DisplayInfo();   // Вызывает базовую версию
        employee.DisplayInfo(); // Вызывает переопределенную версию из Employee
        baby.DisplayInfo(); // Вызывает переопределенную версию из Baby
    }
}