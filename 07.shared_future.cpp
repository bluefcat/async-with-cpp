#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void unit(std::shared_future<void>* sig){
	sig->get();
	std::cout << "Get signal\n";
}

int main(){
	std::promise<void> p;
	std::shared_future<void> f = p.get_future();

	std::thread t[4];

	for(int i = 0; i < 4; i ++) t[i] = std::thread(unit, &f);

	std::cerr << "Ready to signal\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << "Broadcast signal\n";

	p.set_value();

	for(int i = 0; i < 4; i ++) t[i].join();

	return 0;
}
