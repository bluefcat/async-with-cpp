#include <future>
#include <iostream>
#include <string>
#include <thread>

void worker(std::promise<std::string>* p){
	p->set_value("some data");
}

int main(){
	std::promise<std::string> p;
	std::future<std::string> data = p.get_future();

	std::thread t(worker, &p);

	data.wait();

	std::cout << "Get data: " << data.get() << std::endl;

	t.join();

	return 0;
}
