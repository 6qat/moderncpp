#include <rx.hpp>
#include <thread>
#include <iostream>
auto main() -> int
{
	auto ints = rxcpp::observable<>::create<int>(
			[](const rxcpp::subscriber<int>& s) {
				s.on_next(1);
				s.on_next(2);
				s.on_completed();
			});

	ints.
			subscribe(
			[](int v) { printf("OnNext: %d\n", v); },
			[]() { printf("OnCompleted\n"); });

	auto values1 = rxcpp::observable<>::range(1, 5);

	values1.subscribe(
			[](int v) {
				printf("OnNext: %d\n", v);
			},
			[]() {
				printf("OnCompleted\n");
			}
	);

	auto start = std::chrono::steady_clock::now()+std::chrono::milliseconds(1);
	auto period = std::chrono::milliseconds(1000);
	auto values = rxcpp::observable<>::interval(start, period);
	values.
			take(8).
			subscribe(
			[](int v) { printf("OnNext: %d\n", v); },
			[]() { printf("OnCompleted\n"); });

	// =====================================================

	rxcpp::schedulers::run_loop runloop;
	rxcpp::subjects::subject<int> subject;
	auto observable = subject.get_observable();
	observable
			.map([&](int v) {
				//console->info("thread[{}] - published value: {}", getThreadId(), v);
				std::cout << "Thread[{" << std::this_thread::get_id() << "}] -  published value: {" << v << "}" << std::endl;
				return v;
			})
			.observe_on(rxcpp::observe_on_run_loop(runloop))
			.subscribe([&](int v) {
				//console->info("subscriptionThread[{}] - subscription started: {}", getThreadId(), v);
				std::cout << "subscriptionThread[{" << std::this_thread::get_id() << "}] - subscription ended: {" << v << "}" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "subscriptionThread[{" << std::this_thread::get_id() << "}] - subscription ended: {" << v << "}" << std::endl;
			});

	bool runlooping = true;
	std::thread runloopThread([&] {
		std::cout << "start runloop thread\n";
		while (runlooping) {
			if (!runloop.empty())
				runloop.dispatch();
		}
	});

	auto subscriber = subject.get_subscriber();
	std::cout << "start to publish values\n";
	subscriber.on_next(1);
	subscriber.on_next(2);
	std::cout << "stop publishing\n";

	while (!runloop.empty()) {
		std::cout << "wait until runloop queue is empty...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
	runlooping = false;
	runloopThread.join();

}