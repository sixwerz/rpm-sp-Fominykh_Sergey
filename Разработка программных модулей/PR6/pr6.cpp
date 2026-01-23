#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

struct Animals {
    string AnimalSpecies;
    int AnimalAge;
    string AnimalName;
    int AnimalCheck;
};

Animals animals[100];
int col = 0;

void showMenu() {
    cout << "=== Животные в зоопарке ===" << endl;
    cout << "1. Ввод массива структур" << endl;
    cout << "2. Сортировка по возрасту" << endl;
    cout << "3. Поиск по виду" << endl;
    cout << "4. Изменение записи" << endl;
    cout << "5. Удаление записи" << endl;
    cout << "6. Вывод всех" << endl;
    cout << "7. Сохранить в файл (CSV)" << endl;
    cout << "8. Выход" << endl;
    cout << "Выбери: ";
}

string inputString(const string& invite) {
    string s;
    while (true) {
        cout << invite;
        getline(cin, s);
        if (s.empty()) {
            cout << "Поле не может быть пустым. Повторите ввод.\n";
            continue;
        }
        return s;
    }
}

int inputNumberCheck(const string& invite) {
    string s;
    while (true) {
        cout << invite;
        getline(cin, s);
        bool ok = !s.empty();
        for (char c : s) {
            if (c < '0' || c > '1') { ok = false; break; }
        }
        if (ok) return stoi(s);
        cout << "Введите корректный номер (только цифры).\n";
    }
}

int inputNumber(const string& invite) {
    string s;
    while (true) {
        cout << invite;
        getline(cin, s);
        bool ok = !s.empty();
        for (char c : s) {
            if (c < '0' || c > '9') { ok = false; break; }
        }
        if (ok) return stoi(s);
        cout << "Введите корректный номер (только цифры).\n";
    }
}

void inputArray() {
    int n;
    cout << "Сколько животных добавить ? (макс. " << (100 - col) << ")? ";
    n = inputNumber("");
    if (n <= 0 || col + n > 100) {
        cout << "Некорректное количество.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "\n--- Животное " << (col + 1) << " ---\n";
        animals[col].AnimalSpecies = inputString("Введите вид животного: ");
        animals[col].AnimalAge = inputNumber("Введите возраст животного: ");
        animals[col].AnimalName = inputString("Введите имя животного: ");
        animals[col].AnimalCheck = inputNumberCheck("Является ли исчезающим (0 - нет; 1 - да): ");
        col++;
    }
    cout << "Добавлено " << n << " животных.\n";
}

void outputAll() {
    if (col == 0) {
        cout << "Список пуст.\n";
        return;
    }
    for (int i = 0; i < col; i++) {
        cout << i + 1 << ". " << animals[i].AnimalSpecies
            << " | возраст: " << animals[i].AnimalAge
            << " | Имя: " << animals[i].AnimalName
            << " | Является ли исчезающим: " << animals[i].AnimalCheck << endl;
    }
}

void sortByAge() {
    for (int i = 0; i < col - 1; i++) {
        for (int j = i + 1; j < col; j++) {
            if (animals[i].AnimalAge > animals[j].AnimalAge) {
                Animals temp = animals[i];
                animals[i] = animals[j];
                animals[j] = temp;
            }
        }
    }
    cout << "Отсортировано по возрасту животного!\n";
}
void findByName() {
    string фио = inputString("Введите вид животного для поиска: ");
    bool найдено = false;
    for (int i = 0; i < col; i++) {
        if (animals[i].AnimalSpecies == фио) {
            cout << i + 1 << ". " << animals[i].AnimalSpecies
                << " | возраст №" << animals[i].AnimalAge
                << " | Имя: " << animals[i].AnimalName
                << " | Является ли исчезающим: " << animals[i].AnimalCheck << endl;
            найдено = true;
        }
    }
    if (!найдено) cout << "животное не найдено.\n";
}

void editNote() {
    string номер = inputString("Введите имя животного для изменения: ");
    for (int i = 0; i < col; i++) {
        if (animals[i].AnimalName == номер) {
            cout << "Изменение данных для: " << animals[i].AnimalSpecies << endl;
            animals[i].AnimalSpecies = inputString("Введите вид животного: ");
            animals[i].AnimalAge = inputNumber("Введите возраст животного: ");
            animals[i].AnimalName = inputString("Введите имя животного: ");
            animals[i].AnimalCheck = inputNumberCheck("Является ли исчезающим (0 - нет; 1 - да): ");
            cout << "Данные обновлены.\n";
            return;
        }
    }
    cout << "Животное с таким именем не найдено.\n";
}

void deleteNote() {
    string номер = inputString("Введите имя животного для удаления: ");
    for (int i = 0; i < col; i++) {
        if (animals[i].AnimalName == номер) {
            for (int j = i; j < col - 1; j++) {
                animals[j] = animals[j + 1];
            }
            col--;
            cout << "Животное удалено.\n";
            return;
        }
    }
    cout << "Животное с таким именем не найдено.\n";
}

void saveIntoFile() {
    ofstream file("животные.csv");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    for (int i = 0; i < col; i++) {
        file << "\"" << animals[i].AnimalSpecies << "\","
            << animals[i].AnimalAge << ","
            << "\"" << animals[i].AnimalName << "\","
            << "\"" << animals[i].AnimalCheck << "\"\n";
    }
    file.close();
    cout << "Данные сохранены в животные.csv\n";
}

void loadFromFile() {
    ifstream file("животные.csv");
    if (!file.is_open()) return;

    col = 0;
    string line;
    while (getline(file, line) && col < 100) {
        if (line.empty()) continue;

        size_t pos1 = line.find('\"');
        if (pos1 == string::npos) continue;
        size_t pos2 = line.find('\"', pos1 + 1);
        if (pos2 == string::npos) continue;
        string spec = line.substr(pos1 + 1, pos2 - pos1 - 1);

        size_t pos3 = line.find(',', pos2 + 1);
        if (pos3 == string::npos) continue;
        size_t pos4 = line.find(',', pos3 + 1);
        if (pos4 == string::npos) continue;
        string age = line.substr(pos3 + 1, pos4 - pos3 - 1);
        bool ok = true;
        for (char c : age) if (c < '0' || c > '9') ok = false;
        if (!ok) continue;
        int num = stoi(age);

        size_t pos5 = line.find('\"', pos4 + 1);
        if (pos5 == string::npos) continue;
        size_t pos6 = line.find('\"', pos5 + 1);
        if (pos6 == string::npos) continue;
        string name = line.substr(pos5 + 1, pos6 - pos5 - 1);

        size_t pos7 = line.find('\"', pos6 + 1);
        if (pos7 == string::npos) continue;
        size_t pos8 = line.find('\"', pos7 + 1);
        if (pos8 == string::npos) continue;
        string срок = line.substr(pos7 + 1, pos8 - pos7 - 1);

        animals[col].AnimalSpecies = spec;
        animals[col].AnimalAge = num;
        animals[col].AnimalName = name;
        col++;
    }
    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadFromFile();

    int choice;
    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) inputArray();
        else if (choice == 2) sortByAge();
        else if (choice == 3) findByName();
        else if (choice == 4) editNote();
        else if (choice == 5) deleteNote();
        else if (choice == 6) outputAll();
        else if (choice == 7) saveIntoFile();
        else if (choice == 8) break;
        else cout << "Неверный выбор!\n";
    }

    return 0;
}