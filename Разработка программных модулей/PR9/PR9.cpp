#include <iostream>
#include <list>
#include <forward_list>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

int main() {
	setlocale(LC_ALL, "");

	list<int> listTest;
	forward_list<int> forward_listTest;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 1000000);

	auto list_start_push = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		listTest.push_back(dist(gen));
	}
	auto list_end_push = high_resolution_clock::now();
	auto list_time_push = duration_cast<milliseconds>(list_end_push - list_start_push);

	auto forward_list_start_push = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		forward_listTest.push_front(dist(gen));
	}
	auto forward_list_end_push = high_resolution_clock::now();
	auto forward_list_time_push = duration_cast<milliseconds>(forward_list_end_push - forward_list_start_push);

	auto list_start_pop = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		listTest.pop_front();
	}
	auto list_end_pop = high_resolution_clock::now();
	auto list_time_pop = duration_cast<milliseconds>(list_end_pop - list_start_pop);

	auto forward_list_start_pop = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		forward_listTest.pop_front();
	}
	auto forward_list_end_pop = high_resolution_clock::now();
	auto forward_list_time_pop = duration_cast<milliseconds>(forward_list_end_pop - forward_list_start_pop);

	auto list_start_push_back = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		listTest.push_back(2);
	}
	auto list_end_push_back = high_resolution_clock::now();
	auto list_time_push_back = duration_cast<milliseconds>(list_end_push_back - list_start_push_back);

	auto forward_list_start_push_back = high_resolution_clock::now();
	auto it = forward_listTest.before_begin();
	while (next(it) != forward_listTest.end()) ++it;
	forward_listTest.insert_after(it, 2);
	auto forward_list_end_push_back = high_resolution_clock::now();
	auto forward_list_time_push_back = duration_cast<microseconds>(forward_list_end_push_back - forward_list_start_push_back);

	auto list_start_pop_back = high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++)
	{
		listTest.pop_back();
	}
	auto list_end_pop_back = high_resolution_clock::now();
	auto list_time_pop_back = duration_cast<milliseconds>(list_end_pop_back - list_start_pop_back);

	cout << "Добавление в начало:" << endl;
	cout << "list (push_back):        " << list_time_push.count() << " мс" << endl;
	cout << "forward_list (push_front): " << forward_list_time_push.count() << " мс" << endl;
	cout << endl;

	cout << "Удаление из начала:" << endl;
	cout << "list (pop_front):        " << list_time_pop.count() << " мс" << endl;
	cout << "forward_list (pop_front):  " << forward_list_time_pop.count() << " мс" << endl;
	cout << endl;

	cout << "Добавление в конец:" << endl;
	cout << "list (push_back):        " << list_time_push_back.count() << " мс" << endl;
	cout << "forward_list (insert_after): " << forward_list_time_push_back.count() << " мс" << endl;
	cout << endl;

	cout << "Удаление из конца:" << endl;
	cout << "list (pop_back):         " << list_time_pop_back.count() << " мс" << endl;
	cout << "forward_list:            не поддерживает pop_back()" << endl;
	cout << endl;

	return 0;
}
