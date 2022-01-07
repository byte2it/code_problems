
class MyCircularQueue {
    int front, rear;
    int size;
    int* arr;
public:
    MyCircularQueue(int k) {
        front = rear = -1;
        size = k;
        arr = new int[k];
        
    }
    ~MyCircularQueue() {
        delete[] arr;
    }
    
    bool enQueue(int value) {
        if(front == (rear+1) % size){
            //cout << "Queue is full" << "\n";
            return false;
        }
        
        else if ( front == -1) {
            front = rear = 0;
            arr[rear] = value;
        }

        else {
            rear = (rear+1) % size;
            arr[rear] = value;
        }
        return true;
        
        
    }
    
    bool deQueue() {
        if(front == -1){
            //cout << "Queue is empty\n";
            return false;
        }
        
        int data = arr[front];
        arr[front] = -1;
        if(front == rear) {
            front = -1;
            rear = -1;
        }
        else if (front == size-1)
            front = 0;
        else
            ++front;
        
        return true;
        
    }
    
    int Front() {
        if (isEmpty())
            return -1;
        return arr[front];
        
    }
    
    int Rear() {
        if (isEmpty())
            return -1;
        return arr[rear];
    }
    
    bool isEmpty() {
        return (front == -1) ;  
    }
    
    bool isFull() {
        return (front == (rear+1) % size) ;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
