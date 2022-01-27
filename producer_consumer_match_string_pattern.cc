#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class WaitableQueue
{
private:
	mutex mutex_;
	condition_variable signal_;
	queue<char> queue_;

public:
	void push(char item)
	{
		{
			unique_lock<mutex> cs(mutex_);
			queue_.push(item);
		}
		signal_.notify_one();
	}

	char pop()
	{
		unique_lock<mutex> cs(mutex_);
		signal_.wait(cs, [&]() { return queue_.size() > 0; });
		char result = queue_.front();
		queue_.pop();
		return result;
	}
};

class Consumer
{
private:
	WaitableQueue queue_;
	string pattern_;
	string buffer_;
	int bufferEnd_;
	int counter_;
	thread thread_;

public:
	Consumer(const string& pattern) : counter_(0),
		bufferEnd_(0), pattern_(pattern)
	{
		thread_ = thread([&] {
			while (true) {
				char item = queue_.pop();
				if (item == '\0') break; // end signal
				if (matchNext(item)) counter_++;
			}
			});
	}

	WaitableQueue* getQueue() { return &queue_; }
	int getCounter() const { return counter_; }
	string getPattern() const { return pattern_; }
	void join() { thread_.join(); }

private:
	bool matchNext(char next)
	{
		// this match code is inefficient, improvements possible 
		// by using Rabin-Karp or an automaton based approach
		int m = pattern_.length();
		if (buffer_.length() < bufferEnd_ + 1) buffer_.append(1, next);
		else buffer_[bufferEnd_] = next;
		bufferEnd_ = (bufferEnd_ + 1) % m;
		bool match = buffer_.length() == m;
		for (int i = 0; i < m && match; ++i)
			match = buffer_[(bufferEnd_ + i) % m] == pattern_[i];
		return match;
	}
};

class Producer
{
private:
	vector<WaitableQueue*> queues_;
	string input_;
	thread thread_;

public:
	Producer(const vector<WaitableQueue*>& queues, const string& input)
		: queues_(queues), input_(input)
	{
		thread_ = thread([&] {
			// send input
			for (auto ch : input_) {
				for (auto co : queues) co->push(ch);
			}

			// signal end of input
			for (auto co : queues) co->push('\0');
			});
	}

	void join() { thread_.join(); }
};


int main()
{
	// create consumers
	vector<Consumer*> consumers({
		new Consumer("ab"),
		new Consumer("aa"),
		new Consumer("ffff")
		});

	// get queues from consumers
	vector<WaitableQueue*> queues;
	for (auto& co : consumers) queues.push_back(co->getQueue());

	// create producer
	Producer p(queues, "abcdegabccaabbaacv");

	// wait for producer
	p.join();

	//  wait and print result of consumer
	for (auto& co : consumers) {
		co->join();
		cout << "pattern: " << co->getPattern()
			<< " count: "
			<< co->getCounter() << endl;
	}
}
