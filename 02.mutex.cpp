#include <iostream>
#include <cstdio>
#include <mutex>
#include <thread>

void function(int id, int& counter, std::mutex& m){
	printf("Thread #%d running\n", id);

	for(int i = 0; i < 100000; i ++){
		//auto lock and unlock
		std::lock_guard<std::mutex> lock(m);
		//m.lock();
		counter ++;
		//m.unlock();
	}
	
	printf("Thread #%d end\n", id);
}

int main(){
	std::mutex m;
	std::thread threads[4];
	int counter = 0;

	for(int i = 0; i < 4; i ++){
		threads[i] = std::thread(function, i, std::ref(counter), std::ref(m));
	}

	for(int i = 0; i < 4; i ++){
		threads[i].join();
	}

	std::cout << "All thread end\nCounter: " << counter << std::endl;

	return 0;
}
