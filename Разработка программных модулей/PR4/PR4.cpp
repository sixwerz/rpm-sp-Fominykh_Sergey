#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include <cstdlib>
#include <Windows.h>

using namespace std;

// Базовый класс для зданий
class Building {
protected:
    string name;
    int number;
    int numberFloor;
    int numberEntrance;

public:
    Building() : name(""), number(0), numberFloor(0), numberEntrance(0) {}

    Building(const string& n, const int& num, int numFloor, int numEntrance)
        : name(n), number(num), numberFloor(numFloor), numberEntrance(numEntrance) {
    }

    virtual ~Building() = default;

    // Геттеры
    string getName() const { return name; }
    int getNumber() const { return number; }
    int getNumberFloor() const { return numberFloor; }
    int getNumberEntrance() const { return numberEntrance; }

    // Сеттеры
    void setName(const string& n) { name = n; }
    void setNumber(const int& num) { number = num; }
    void setNumberFloor(const int& numFloor) { numberFloor = numFloor; }
    void setNumberEntrance(const int& numEntrance) { numberEntrance = numEntrance; }

    virtual void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Тип: Здание; номер: " << name << "; улица: " << number
                << "; подъезды: " << numberEntrance << "; этажи: " << numberFloor << "\n";
            file.close();
        }
        else {
            cout << "Ошибка: не удалось открыть файл для записи.\n";
        }
    }

    virtual void displayInfo() const = 0;
};

// Производный класс для жилых домов
class Home : public Building {
private:
    int numberApartment;

public:
    Home() : Building(), numberApartment(0) {}

    Home(const string& n, const int& number, int numberFloor, int numberEntrance, int numberApartment)
        : Building(n, number, numberFloor, numberEntrance), numberApartment(numberApartment) {
    }

    ~Home() = default;

    // Геттеры для Home
    int getNumberApartment() const { return numberApartment; }

    // Сеттеры для Home
    void setNumberApartment(const int& numApartment) { numberApartment = numApartment; }

    void saveToFile(const string& filename) const override {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "номер дома: " << name << "; название улицы: " << number
                << "; количество подъездов: " << numberEntrance
                << "; Количество этажей: " << numberFloor
                << "; Количество квартир: " << numberApartment << "\n";
            file.close();
        }
        else {
            cout << "Ошибка: не удалось открыть файл для записи.\n";
        }
    }

    void displayInfo() const override {
        cout << "--- Информация о доме ---\n";
        cout << "Название: " << name << "\n";
        cout << "Номер: " << number << "\n";
        cout << "Количество этажей: " << numberFloor << "\n";
        cout << "Количество подъездов: " << numberEntrance << "\n";
        cout << "Количество квартир: " << numberApartment << "\n";
    }

    static Home inputFromConsole() {
        string name;
        int number, numberEntrance, numberFloor, numberApartment;

        // Ввод номера дома
        while (true) {
            try {
                cout << "Введите номер дома: ";
                string input;
                getline(cin, input);
                size_t pos;
                number = stoi(input, &pos);
                if (pos != input.size()) throw invalid_argument("лишние символы");
                if (number < 0) throw out_of_range("номер не может быть отрицательным");
                break;
            }
            catch (...) {
                cout << "Ошибка: введите корректный номер (целое число)!\n";
            }
        }

        // Ввод названия улицы
        cout << "Введите название улицы: ";
        getline(cin, name);

        // Ввод подъездов
        while (true) {
            try {
                cout << "Введите количество подъездов: ";
                string input;
                getline(cin, input);
                size_t pos;
                numberEntrance = stoi(input, &pos);
                if (pos != input.size()) throw invalid_argument("лишние символы");
                if (numberEntrance < 0) throw out_of_range("количество не может быть отрицательным");
                break;
            }
            catch (...) {
                cout << "Ошибка: введите корректное количество (целое число)!\n";
            }
        }

        // Ввод этажей
        while (true) {
            try {
                cout << "Введите количество этажей: ";
                string input;
                getline(cin, input);
                size_t pos;
                numberFloor = stoi(input, &pos);
                if (pos != input.size()) throw invalid_argument("лишние символы");
                if (numberFloor < 0) throw out_of_range("количество не может быть отрицательным");
                break;
            }
            catch (...) {
                cout << "Ошибка: введите корректное количество (целое число)!\n";
            }
        }

        // Ввод квартир
        while (true) {
            try {
                cout << "Введите количество квартир: ";
                string input;
                getline(cin, input);
                size_t pos;
                numberApartment = stoi(input, &pos);
                if (pos != input.size()) throw invalid_argument("лишние символы");
                if (numberApartment < 0) throw out_of_range("количество не может быть отрицательным");
                break;
            }
            catch (...) {
                cout << "Ошибка: введите корректное количество (целое число)!\n";
            }
        }

        return Home(name, number, numberFloor, numberEntrance, numberApartment);
    }
};

// Функция добавления записи
void addHomeRecord(const string& filename) {
    Home sf = Home::inputFromConsole();
    sf.saveToFile(filename);
    cout << "Запись успешно добавлена в файл \"" << filename << "\".\n";
}

// Функция для вывода содержимого файла
void displayFileContent(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "\n--- Содержимое файла \"" << filename << "\" ---\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
        cout << "--- Конец файла ---\n";
    }
    else {
        cout << "Ошибка: не удалось открыть файл \"" << filename << "\".\n";
    }
}

int main() {
    cin.exceptions(ios::failbit);
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string filename = "home.txt";
    char choice;

    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Добавить запись о доме\n";
        cout << "2. Просмотреть все записи\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1':
            addHomeRecord(filename);
            break;
        case '2':
            displayFileContent(filename);
            break;
        case '0':
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != '0');

    return 0;
}