// LRU_cache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>
#include <list>

using std::unordered_map;
using std::list;

class LRUCache {
	struct CacheEntry {
		int key;
		int value;
		CacheEntry(int k, int v) : key(k), value(v) {}
	};
	unordered_map<int, list<CacheEntry>::iterator> _cache;
	list<CacheEntry> _queue;
	int _capacity;
public:
	LRUCache(int capacity) :_capacity(capacity) {}

	int get(int key) {
		if (_cache.find(key) == _cache.end())
			return -1;

		MoveToHead(key);
		return _cache[key]->value;
	}

	void put(int key, int value) {
		if (_cache.find(key) == _cache.end()) {
			CacheEntry newItem(key, value);
			if (_queue.size() >= _capacity) {
				_cache.erase(_queue.back().key);
				_queue.pop_back();
			}
			_queue.push_front(newItem);
			_cache[key] = _queue.begin();
			return;
		}
		_cache[key]->value = value;
		MoveToHead(key);
	}
private:
	void MoveToHead(int key) {
		auto temp = *_cache[key];
		_queue.erase(_cache[key]);
		_queue.push_front(temp);
		_cache[key] = _queue.begin();
	}
};


int main()
{
    return 0;
}

