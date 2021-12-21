#include <future>
#include <thread>
#include <iostream>
#include <chrono>

void task(){
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return;
}

void parallel(){
	std::future<void> f[3];

	for(int i = 0; i < 3; i ++){
		f[i] = std::async(std::launch::async, task);
	}

	for(int i = 0 ; i < 3; i ++) f[i].get();
}

void sequential(){
	for(int i = 0; i < 3; i ++) task();
}


int main(){

//In linux, if you want to run sequential function, type 'g++ -D seq' 
#if seq
	sequential();
#else
	parallel();
#endif

	return 0;
}
