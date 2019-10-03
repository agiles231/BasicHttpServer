#pragma once
#include <vector>
#include <thread>
#include <mutex>
class ThreadPool
{
private:
	int maxThreads;
	std::vector<std::thread> threads;

	std::mutex mutex;
public:
	ThreadPool(int numThreads);
	~ThreadPool();

	int getCurrentExecutingThreads() { return threads.size(); }
	int getMaximumExecutingThreads() { return maxThreads; }

	void resize(int numThreads);

	template<typename F, typename ...Others>
	void queueTask(F job, Others&&... rest);

	void clearQueuedTasks();
};

