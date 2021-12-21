#include <future>
#include <iostream>
#include <thread>

int task(int x) { return 10 + x; };

int main(){
	std::packaged_task<int(int)> pt(task);
	std::future<int> f = pt.get_future();

	std::thread t(std::move(pt), 5);

	std::cout << "Result: " << f.get() << std::endl; 

	t.join();
	
	return 0;
}
