#include <iostream>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
bool done = false;
std::string content;

void producer(){
	{
		std::lock_guard<std::mutex> lk(m);
		content = "Download content";
		done = true;
	}

	cv.notify_all();
}


int main(){
	std::thread t(producer);
	
	std::unique_lock<std::mutex> lk(m);

	cv.wait(lk, [] { return done; });
	lk.unlock();

	std::cout << "Get Data: " << content << std::endl;


	t.join();
	return 0;
}

