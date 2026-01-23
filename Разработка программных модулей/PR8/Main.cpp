#include <iostream>
#include <chrono>
#include <algorithm>
#include "Vector.hpp"
#include "Stack.hpp"
#include <Windows.h>
using namespace std;
using namespace chrono;

void demoVector() {
    cout << "\nVector:" << endl;

    Vector<int> vec1;

    auto start_one = high_resolution_clock::now();
    vec1.push_back(10);
    auto end_one = high_resolution_clock::now();
    auto one_time_ms = duration<double, micro>(end_one - start_one).count() / 1000.0;

    cout << "Время добавления 1 элемента в Vector: " << fixed << one_time_ms << " мс" << endl;
}

void demoStack() {
    cout << "\nStack:" << endl;

    Stack<int> s;

    auto start_one = high_resolution_clock::now();
    s.push(10);
    auto end_one = high_resolution_clock::now();
    auto one_time_ms = duration<double, micro>(end_one - start_one).count() / 1000.0;

    cout << "Время добавления 1 элемента в Stack: " << fixed << one_time_ms << " мс" << endl;
}

void comparePerformance() {

    const size_t N = 100000000;

    cout << "\nVector:" << endl;

    Vector<int> vec;

    //auto start_million_vec = high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        vec.push_back(static_cast<int>(i));
    }
    //auto end_million_vec = high_resolution_clock::now();
    //auto million_time_vec_s = duration<double, micro>(end_million_vec - start_million_vec).count() / 1000000.0;

    auto start_one = high_resolution_clock::now();
    vec.push_back(10);
    auto end_one = high_resolution_clock::now();
    auto one_time_ms = duration<double, micro>(end_one - start_one).count() / 1000.0;

    cout << "Время добавления 10 элементов после " << N  << " Элементов в Vector: " << fixed << one_time_ms << " мс" << endl;
    //cout << "Время добавления " << N << " элементов: " << fixed << million_time_vec_s << " сек" << endl;

    cout << "\nStack:" << endl;

    Stack<int> stk;

    //auto start_million_stk = high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        stk.push(static_cast<int>(i));
    }
    auto start_onee = high_resolution_clock::now();
    stk.push(10);
    auto end_onee = high_resolution_clock::now();
    auto one_time_mss = duration<double, micro>(end_onee - start_onee).count() / 1000.0;

    cout << "Время добавления 10 элементов после " << N << " Элементов в Stack: " << fixed << one_time_mss << " мс" << endl;
    /*auto end_million_stk = high_resolution_clock::now();
    auto million_time_stk_s = duration<double, micro>(end_million_stk - start_million_stk).count() / 1000000.0;*/
    //cout << "Время добавления " << N << " элементов: " << fixed << million_time_stk_s << " сек" << endl;

}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);;

    demoVector();
    demoStack();
    comparePerformance();

    return 0;
}
