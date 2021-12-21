#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>

void producer(std::promise<void>* p){
	std::this_thread::sleep_for(std::chrono::seconds(10));
	p->set_value();
}

int main(){
	std::promise<void> p;
	std::future<void> f = p.get_future();

	std::thread t(producer, &p);

	while(true){
		std::future_status status = f.wait_for(std::chrono::seconds(1));

		if(status == std::future_status::timeout){
			std::cerr << ">";
		}
		else if(status == std::future_status::ready){
			std::cerr << "\n";
			break;
		}
	}
	t.join();
	return 0;

}
