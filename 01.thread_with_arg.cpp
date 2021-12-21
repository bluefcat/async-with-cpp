#include <iostream>
#include <cstdio>
#include <thread>

void function(int id, int& counter){
	printf("Thread #%d running\n", id);

	for(int i = 0; i < 100000; i ++){
		counter ++;
	}
	
	printf("Thread #%d end\n", id);
}

int main(){
	std::thread threads[4];
	int counter = 0;

	for(int i = 0; i < 4; i ++){
		threads[i] = std::thread(function, i, std::ref(counter));
	}

	for(int i = 0; i < 4; i ++){
		threads[i].join();
	}

	std::cout << "All thread end\nCounter: " << counter << std::endl;

	return 0;
}
