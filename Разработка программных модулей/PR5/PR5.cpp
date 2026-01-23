#include <iostream>
#include <memory>
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Figure {
protected:
    double height = 0;
    double width = 0;

public:
    Figure() = default;
    virtual void setHeight(int h) {
        height = h;
    }

    virtual void setWidth(int w) {
        width = w;
    }

    virtual int getHeight() const {
        return height;
    }

    virtual int getWidth() const {
        return width;
    }

    virtual string getName() = 0;
    virtual string getArea() const = 0;
};

class Ellipse : public Figure {
public:
    Ellipse(double width, double height) {
        setWidth(width);
        setHeight(height);
    }

    string getName() override {
        return "Эллипс";
    }

    string getArea() const override {  // const защщищает от изменения данных, override - способствует полиморфизму
        const double PI = 3.14159265358979323846;
        double area = PI * getWidth() * getHeight();
        return to_string(area);
    }

};

class PentagonPP : public Figure {
public:
    PentagonPP(double width) {
        setWidth(width);
    }

    string getName() override {
        return "Пентагон-ПП";
    }

    string getArea() const override {
        double area = 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * getWidth() * getWidth();
        return to_string(area);
    }
};

unique_ptr<Figure> Factory(string& figure) {
    if (figure == "Эллипс") {
        double width;
        cout << "Введите большую полуось: ";
        cin >> width;

        double height;
        cout << "Введите малую полуось: ";
        cin >> height;
        cout << endl;
        cout << "Создался объект эллипс" << endl;

        return make_unique<Ellipse>(width, height);
    }
    if (figure == "Пентагон-ПП") {
        double width;
        cout << "Введите длину стороны: ";
        cin >> width;
        cout << "Создался объект Пентагон-ПП" << endl;

        return make_unique<PentagonPP>(width);
    }
    else { cout << "Неверная фигура" << endl; }
    
    return nullptr;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        vector<unique_ptr<Figure>> figures;
        int choice = 0;

        do {
            string figure;
            cout << "Выберите фигуру(Эллипс, Пентагон-ПП): ";
            cin >> figure;

            figures.push_back(move(Factory(figure)));

            cout << "Добавить еще? (1 - да, 0 - нет): ";
            cin >> choice;
            cout << endl;

        } while (choice == 1);

        cout << "Вычисление площади" << endl;

        for (const unique_ptr<Figure>& item : figures) {
            if (item != nullptr) {
                cout << "Площадь фигуры " << item->getName() << ": " << item->getArea() << endl;
            }
        }

        cout << endl;
        return 0;
    }
    catch (const invalid_argument& ex) {
        cerr << ex.what() << endl;
    }
    catch (const exception& ex) {
        cerr << ex.what() << endl;
    }
}