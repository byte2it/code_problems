
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::left;

template <class T> struct Node {
    string mKey;
    T mData;
    Node<T> *mNext, *mPrevious;

    Node() : mKey(""), mData(T()), mNext(nullptr), mPrevious(nullptr){}

    Node(string key, T data) : mKey(key), mData(data), mNext(nullptr), 
        mPrevious(nullptr){ }
};
    
template <class T> class Bucket {
private:
    Node<T> *mHead, *mTail;
    int mCount;

public:
    Bucket();
    ~Bucket();

    int getCount() { return mCount; }
    bool isEmpty() { return mCount == 0; }
    bool isExist(string searchKey);
    bool remove(string searchKey);

    void display();
    void insert(string key, T data);

    T getData(string key);
};

template <class T> Bucket<T>::Bucket() : mHead(nullptr), 
        mTail(nullptr), mCount(0){}

template <class T> Bucket<T>::~Bucket() {
    Node<T> *tmp, *toBeDeleted;

    tmp = mHead;

    while (tmp != nullptr) {
        toBeDeleted = tmp;
        tmp = tmp->mNext;
        toBeDeleted->mNext = nullptr;

        delete toBeDeleted;
    }

    mHead = nullptr;
    mTail = nullptr;
    mCount = 0;
}

template <class T> bool Bucket<T>::isExist(string searchKey) {
    Node<T> *tmp = mHead;

    while (tmp != nullptr)     {
        if (tmp->mKey == searchKey)
            return true;

        tmp = tmp->mNext;
    }

    return false;
}


template <class T> bool Bucket<T>::remove(string searchKey) {
    Node<T> *tmp, *prev;

    if (mHead == nullptr)
        return false;
    else if (searchKey < mHead->mKey || searchKey > mTail->mKey)
        return false;

    tmp = mHead;
    prev = nullptr;

    for (int i = 0; i < mCount; i++) {
        if (searchKey == tmp->mKey)
            break;

        prev = tmp;
        tmp = tmp->mNext;
    }

    if (tmp != nullptr) {
        if (tmp == mHead) {
            tmp = mHead;

            mHead = mHead->mNext;
            if (mHead == nullptr)
                mTail = nullptr;

            tmp->mNext = nullptr;
        } else if (tmp == mTail) {
            prev->mNext = nullptr;
            mTail = prev;
        } else {
            prev->mNext = tmp->mNext;
            tmp->mNext = nullptr;
        }

        delete tmp;
        mCount--;

        return true;
    }

    return false;
}


template <class T> void Bucket<T>::display() {
    Node<T> *tmp;

    if (mHead == nullptr) {
        cout << "{ }\n";
        return;
    }

    cout << "{ ";
    tmp = mHead;
    while (tmp != nullptr) {
        cout
            << "["
            << tmp->mKey
            << ", "
            << tmp->mData
            << "]"
            << (tmp != mTail ? ", " : " }");

        tmp = tmp->mNext;
    }
    cout << "\n";
}


template <class T> void Bucket<T>::insert(string key, T data) {
    Node<T> *tmp, *oneBefore, *newNode;

    newNode = new Node<T>(key, data);
    if (newNode == nullptr)
        return;

    if (mHead == nullptr) {
        mHead = newNode;
        mTail = newNode;
    } else {
        if (key < mHead->mKey) {
            newNode->mNext = mHead;

            newNode->mPrevious = nullptr;

            mHead = newNode;
        } else if (key > mTail->mKey) {
            mTail->mNext = newNode;

            newNode->mPrevious = mTail;

            mTail = newNode;
        } else if (key == mHead->mKey || key == mTail->mKey) {
            delete newNode;
            return;
        } else {
            tmp = mHead;
            oneBefore = mHead;

            // Iterate through list to find position
            while (tmp->mKey < key) {
                oneBefore = tmp;

                tmp = tmp->mNext;
            }

            if (tmp->mKey != key) {
                newNode->mNext = tmp;
                tmp->mPrevious = newNode;

                oneBefore->mNext = newNode;
                newNode->mPrevious = oneBefore;
            } else {
                delete newNode;
                return;
            }
        }
    }

    mCount++;
}

template <class T> T Bucket<T>::getData(string key) {
    Node<T> *tmp = mHead;

    while (tmp != nullptr) {
        if (tmp->mKey == key)
            return tmp->mData;

        tmp = tmp->mNext;
    }

    return T();
}


template <class T> class Dictionary {
private:

    Bucket<T>* mBuckets;
    int mCount;

    int hash(string key) {

        int value = 0;

        for (int i = 0; i < key.length(); i++)
            value += key[i];

        return value % mCount;
    }

public:
    Dictionary() : mCount(16), mBuckets(new Bucket<T>[mCount]){}
    Dictionary(int mCount) :
         mCount((mCount >= 0 ? mCount : 16)), mBuckets(new Bucket<T>[mCount]){}
    ~Dictionary() {delete[] mBuckets;}

    bool containsKey(string key);
    void display();
    void displayDistribution();
    int getCount();
    T getData(string key);
    bool insert(string key, T value);
    bool isEmpty() {return getCount() == 0;}
};

template <class T> bool Dictionary<T>::containsKey(string key) {
    int bin = hash(key);
    return mBuckets[bin].isExist(key);
}

template <class T> void Dictionary<T>::display() {
    cout
        << " Dictionary - Items:" << getCount() << "\n"
        << "*********************** \n";

    for (int i = 0; i < mCount; i++) {
        cout << left << i << ": ";

        mBuckets[i].display();

        cout << "\n\n";
    }
}

template <class T> void Dictionary<T>::displayDistribution() {
    cout
        << " Dictionary - Distribution:" << getCount() << "\n"
        << "*********************** \n";

    for (int i = 0; i < mCount; i++) {
        cout 
            << left 
            << i << ": " << mBuckets[i].getCount();

        cout << "\n";
    }
}

template <class T> int Dictionary<T>::getCount() {
    int count = 0;
    for (int i = 0; i < mCount; i++) {
        count += mBuckets[i].getCount();
    }

    return count;
}

template <class T> T Dictionary<T>::getData(string key) {
    int bin = hash(key);
    return mBuckets[bin].getData(key);
}

template <class T> bool Dictionary<T>::insert(string key, T value) {
    int bin = hash(key);
    mBuckets[bin].insert(key, value);
    return true;
}

int main() {
    Dictionary<int> dict(512);
    
    dict.insert("a", 11);
    dict.insert("b", 12);
    dict.insert("aa", 21);
    dict.insert("bb", 22);
    dict.display();
    return 0;
}
