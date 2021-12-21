#include <chrono>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <cstdio>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

void producer(std::queue<std::string>* wait_queue, std::mutex* m, int idx, std::condition_variable* cv){
	for(int i = 0; i < 5; i ++){
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * idx));

		std::string content = "website: " + std::to_string(i) + " from thread #" + std::to_string(idx) + "\n";

		std::lock_guard<std::mutex> lock(*m);
		wait_queue->push(content);

		cv->notify_one();
	}
}

void consumer(std::queue<std::string>* wait_queue, std::mutex* m, int* num_processed, std::condition_variable* cv){
	while(*num_processed < 25){
		std::unique_lock<std::mutex> lk(*m);

		cv->wait(
				lk, [&] { return !wait_queue->empty() || *num_processed == 25; }
				);

		if(*num_processed == 25){
			lk.unlock();
			return;
		}

		std::string content = wait_queue->front();
		wait_queue->pop();

		(*num_processed)++;
		lk.unlock();

		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
}

int main(){
	std::queue<std::string> wait_queue;
	std::mutex m;
	std::condition_variable cv;

	std::vector<std::thread> producers;

	int num_processed = 0;
	std::vector<std::thread> consumers;

	for(int i = 0; i < 5; i ++){
		producers.push_back(std::thread(producer, &wait_queue, &m, i+1, &cv));
	}

	for(int i = 0; i < 3; i ++){
		consumers.push_back(std::thread(consumer, &wait_queue, &m, &num_processed, &cv));
	}

	for(int i = 0; i < 5; i ++){
		producers[i].join();
	}

	cv.notify_all();

	for(int i = 0; i < 3; i ++){
		consumers[i].join();
	}


}

