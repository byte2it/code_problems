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
	unordered_map<int, list<CacheEntry>::iterator> cache;
	list<CacheEntry> queue;
	int capacity;
public:
	LRUCache(int cap) :capacity(cap) {}

	int get(int key) {
		if (cache.find(key) == cache.end())
			return -1;

		MoveToHead(key);
		return cache[key]->value;
	}

	void put(int key, int value) {
		if (cache.find(key) == cache.end()) {
			CacheEntry newItem(key, value);
			if (queue.size() >= capacity) {
				cache.erase(queue.back().key);
				queue.pop_back();
			}
			queue.push_front(newItem);
			cache[key] = queue.begin();
			return;
		}
		cache[key]->value = value;
		MoveToHead(key);
	}
private:
	void MoveToHead(int key) {
		auto temp = *cache[key];
		queue.erase(cache[key]);
		queue.push_front(temp);
		cache[key] = queue.begin();
	}
};


int main()
{
    return 0;
}

