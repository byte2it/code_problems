#include <iostream>

using namespace std;

struct Node {

	int data;
	Node* next;

	Node(int d) { data = d; }
};

class CircularBuffer {

	Node* head;

	Node* tail;
	int size = 0;
	int capacity = 0;

public:

	CircularBuffer(int cap) : capacity(cap) {}

	void add(int element) {

		size++;

		if (size == capacity) {
			throw std::exception("Buffer Overflow");
		}

		if (head == 0) {
			head = new Node(element);
			tail = head;
			return;
		}

		Node* temp = new Node(element);
		temp->next = head;

		tail->next = temp;

		tail = temp;
	}

	int get() {

		if (size == 0) {
			throw std::exception("Empty Buffer");
		}

		int element = head->data;
		head = head->next;
		tail->next = head;
		size--;
		if (size == 0) {
			head = tail = 0;
		}
		return element;
	}

	int peek() {

		if (size == 0) {
			throw std::exception("Empty Buffer");
		}

		int element = head->data;
		return element;
	}

	bool isEmpty() { return size == 0; }

	int get_size() { return size; }

	void print() {
		if (size == 0 || head ==0) {
			cout << "empty" << std::endl;
			return;
		}

		int i = 0;
		for (Node* it = head; it != 0, i < size; it = it->next, ++i)
			cout << it->data << ", ";
		cout << std::endl;
	}
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
