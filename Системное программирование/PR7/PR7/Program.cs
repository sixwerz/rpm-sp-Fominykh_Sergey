using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using PR7.Models;

var id = 1; // для генерации id объектов


// Начальные данные
var users = new List<Person>
{
    new() { Id = id++, Name = "Apple"},
    new() { Id = id++, Name = "Banana"},
    new() { Id = id++, Name = "Cherry"},
    new() { Id = id++, Name = "grape"}
};


var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

// Вывод всех элементов
app.MapGet("/api/users", () => users);


// предпоследний элемент
app.MapGet("/api/users/one", () =>
{
    var user = users[^2];
    return Results.Json(user);
});


// Определенный ID
app.MapGet("/api/users/{id}", (int id) =>
{
    Person? user = users.FirstOrDefault(u => u.Id == id);
    if (user == null)
        return Results.NotFound(new { message = "Пользователь не найден" });
    return Results.Json(user);
});


// Изменение элементов
app.MapPut("/api/users/{id}", (int id, Person userData) =>
{
    Person? user = users.FirstOrDefault(u => u.Id == id);
    if (user == null)
        return Results.NotFound(new { message = "Пользователь не найден" });
    user.Name = userData.Name;
    user.Age = userData.Age;
    return Results.Json(user);
});


// Элементы с 1 по 3
app.MapGet("api/users/two", () =>
{
    var range = users.GetRange(1, 3); // (индекс начала, количество)
    return Results.Json(range);
});


// Добавление в массив
app.MapPost("/api/users", (Person user) =>
{
    user.Id = id++;
    users.Add(user);
    return Results.Created($"/api/users/{user.Id}", user);
});


// Удаление из массива
app.MapDelete("/api/users/{id}", (int id) =>
{
    Person? user = users.FirstOrDefault(u => u.Id == id);
    if (user == null)
        return Results.NotFound(new { message = "Пользователь не найден" });
    users.Remove(user);
    return Results.Json(user);
});

app.Run();