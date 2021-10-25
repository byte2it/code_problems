#include <iostream>
#include <vector>

using namespace std;

class CircularBuffer {

	int capacity = 0;
	int size = 0;
	int head = 0;

	int tail = -1;
	vector<int> data;

public:
	CircularBuffer(int cap) : capacity(cap), data(cap) {
	}

	void add(int element) {

		int index = (tail + 1) % capacity;

		size++;

		if (size == capacity) {
			throw std::exception("Circular Buffer Overflow");
		}

		data[index] = element;

		tail++;
	}

	int get() {

		if (size == 0) {
			throw std::exception("Empty Circular Buffer");
		}

		int index = head % capacity;

		int element = data[index];
		head++;
		size--;
		return element;
	}


	int peek() {

		if (size == 0) {
			throw std::exception("Empty CIrcular Buffer");
		}

		int index = head % capacity;

		int element = data[index];

		return element;
	}

	void print() {
		if (size == 0) {
			cout << "empty" << std::endl;
			return;
		}
		for (int i = head; i < (head+size); ++i)
			cout << data[i] << ", ";
		cout << std::endl;
	}


	bool isEmpty() { return size == 0; }

	int get_size() { return size; }
};

int main() {

	CircularBuffer cb(10);

	cb.add(5);
	cb.add(6);
	cb.add(7);
	cb.add(1);
	cb.add(4);

	cb.print();

	cout << "The elements are printed in the order :-" << std::endl;
	cout << cb.get() << std::endl;

	cb.print();
	cout << cb.get() << std::endl;
	cb.print();
	cout << cb.get() << std::endl;
	cb.print();
	cout << cb.get() << std::endl;
	cb.print();
	cout << cb.get() << std::endl;
	cb.print();

	return 0;
}
