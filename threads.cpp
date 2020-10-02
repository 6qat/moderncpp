#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

auto hello() -> void
{
	cout << "From another thread: " << std::this_thread::get_id() << endl;
	//std::this_thread::sleep_for(chrono::nanoseconds(3'000'000'000));
	std::this_thread::sleep_for(3'000'000'000ns);

}

auto main() -> int
{
	cout << "Hardware Concurrency: " << std::thread::hardware_concurrency() << endl;
	cout << "From main thread: " << std::this_thread::get_id() << endl;
	auto t = std::jthread(hello);
	t.join();
	return 0;
}
