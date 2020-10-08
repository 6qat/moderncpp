#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
using namespace std;

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) {
	cout << "From function: " << std::this_thread::get_id() << endl;
	std::this_thread::sleep_for(5'000'000'000ns);
	return std::pow(x, y);
}

void task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
		cout << "From lambda: " << std::this_thread::get_id() << endl;
		return std::pow(a, b);
	});
	std::future<int> result = task.get_future();

	task(2, 9);

	std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind()
{
	std::packaged_task<int()> task(std::bind(f, 2, 11));
	std::future<int> result = task.get_future();

	task();

	std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread()
{
	std::packaged_task<int(int, int)> task(f);
	std::future<int> result = task.get_future();

	std::thread task_td(std::move(task), 1, 10);
	task_td.join();

	std::cout << "task_thread:\t" << result.get() << '\n';
}

int main()
{
	cout << "Hardware Concurrency: " << std::thread::hardware_concurrency() << endl;
	cout << "From main thread: " << std::this_thread::get_id() << endl;
	task_lambda();
	task_bind();
	task_thread();
}
