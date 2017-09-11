#include <string>
#include <iostream>

using namespace std;

template<class T> struct Node {
    Node(){ val = 0; next = nullptr; }
    Node(const T& item, Node<T>* ptrnext = nullptr);
    
    T val;
    Node<T> * next;
};

template<class T> Node<T>::Node(const T& item, Node<T>* ptrnext) {
    val = item;
    next = ptrnext;
}

template<class T> class LinkedList {
private:
    Node<T> * front;
    Node<T> * rear;
    int count;
public:
    LinkedList();
    ~LinkedList();
    void InsertFront(const T Item);
    void InsertRear(const T Item);
    void PrintList();
};
    
template<class T> LinkedList<T>::LinkedList() {
    front = nullptr;
    rear = nullptr;
 }

 template<class T> void LinkedList<T>::InsertFront(const T  item) {
    if (front == nullptr) {
        front = new Node<T>();
        front->val = item;
        front->next = nullptr;
        rear = new Node<T>();
        rear = front;
    } else {
        Node<T> * newNode = new Node<T>();
        newNode->val = item;
        newNode->next = front;
        front = newNode;
    }
 }

template<class T> void LinkedList<T>::InsertRear(const T  item) {
    if (rear == nullptr) {
        rear = new Node<T>();
        rear->val = item;
        rear->next = nullptr;
        front = new Node<T>();
        front = rear;
    } else {
        Node<T> * newNode = new Node<T>();
        newNode->val = item;
        rear->next = newNode;
        rear = newNode;
    }
}
    
template<class T> void LinkedList<T>::PrintList() {
    Node<T> *  temp = front;
    while (temp != nullptr) {
        cout << " " << temp->val << "";
        temp = temp->next;
    }
}

int main() {
    LinkedList<int> * llist = new LinkedList<int>();
    llist->InsertFront(40);
    llist->InsertFront(30);
    llist->InsertFront(20);
    llist->InsertFront(10);
    llist->InsertRear(50);
    llist->InsertRear(60);
    llist->InsertRear(70);
    llist->PrintList();
