#include <iostream>

#include <iostream>
#include <math.h>
using namespace std;

class Node {
public:
	int data;
	Node* next;
};

Node* newNode(int data)
{
	Node* new_node = new Node();
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void push(Node** head_ref, int new_data)
{
	Node* new_node = newNode(new_data);

	new_node->next = (*head_ref);

	(*head_ref) = new_node;
}

Node* addTwoLists(Node* first, Node* second)
{
	Node* res = NULL;
	Node* temp = NULL, * prev = NULL;
	int carry = 0, sum;

	while (first != NULL
		|| second != NULL) {
		sum = (carry + (first ? first->data : 0)
			+ (second ? second->data : 0)) % 2;

		carry = (carry + (first ? first->data : 0)
			+ (second ? second->data : 0)) / 2;

		temp = newNode(sum);

		if (res == NULL)
			res = temp;

		else
			prev->next = temp;

		prev = temp;

		if (first)
			first = first->next;
		if (second)
			second = second->next;
	}

	if (carry > 0)
		temp->next = newNode(carry);

	return res;

}

Node* reverse(Node* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	Node* rest = reverse(head->next);
	head->next->next = head;

	head->next = NULL;

	return rest;
}

void printList(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

int main()
{
	Node* res = NULL;
	Node* first = NULL;
	Node* second = NULL;

	push(&first, 1);
	push(&first, 0);
	push(&first, 1);
	push(&first, 1);

	cout << "First List is ";
	printList(first);

	push(&second, 0);
	push(&second, 0);
	push(&second, 1);
	cout << "Second List is ";
	printList(second);

	first = reverse(first);
	second = reverse(second);

	res = addTwoLists(first, second);

	res = reverse(res);
	cout << "Resultant list is ";
	printList(res);

	return 0;
}
