#include <future>
#include <iostream>
#include <thread>
#include <functional>

int async_sum(){
	std::function<int(int, int)> f = [](int a, int b){
		int r = 0;
		for(int i = a; i < b; i ++) r += i;

		return r;
	};
	
	std::future<int> sum[100];
	
	for(int i = 0; i < 100; i ++){
		sum[i] = std::async(std::launch::async, f, (i*100)+1, ((i+1)*100+1));
	}
	
	int result = 0;

	for(int i = 0; i < 100; i ++){
		result += sum[i].get();
	}

	return result;
}

int main(){
	std::cout << "sum 1 of 10000: " << async_sum() << std::endl;
	return 0;
}
