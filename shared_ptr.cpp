#include <iostream>
#include <atomic>

using namespace std;

template<class T>
class shared_ptr {
    struct aux {
        std::atomic<unsigned> count;

        aux() :count(1) {}
        virtual void destroy()=0;
        virtual ~aux() {} //must be polymorphic
    };

    template<class U, class Deleter>
    struct auximpl: public aux {
        U* p;
        Deleter d;

        auximpl(U* pu, Deleter x) :p(pu), d(x) {}
        virtual void destroy() { d(p); } 
    };

    template<class U>
    struct default_deleter {
        void operator()(U* p) const { delete p; }
    };

    aux* pa;
    T* pt;

    void increment() {++pa->count; }

    void decrement() { 

        if(! --pa->count) 
        {  pa->destroy(); delete pa; }
    }

public:

    shared_ptr() :pa(), pt() {}

    template<class U, class Deleter>
    shared_ptr(U* pu, Deleter d) :pa(new auximpl<U,Deleter>(pu,d)), pt(pu) {}

    template<class U>
    explicit shared_ptr(U* pu) :pa(new auximpl<U,default_deleter<U> >(pu,default_deleter<U>())), pt(pu) {}

    shared_ptr(const shared_ptr& s) :pa(s.pa), pt(s.pt) { increment(); }

    template<class U>
    shared_ptr(const shared_ptr<U>& s) :pa(s.pa), pt(s.pt) { increment(); }

    ~shared_ptr() { decrement(); }

    shared_ptr& operator=(const shared_ptr& s) {
        if(this!=&s) {
            decrement();
            pa = s.pa; pt=s.pt;
            increment();
        }        
        return *this;
    }

    T* operator->() const { return pt; }
    T& operator*() const { return *pt; }
    
    int getRefCount() {return pa->count;}
};


int main()
{
    shared_ptr<int> ptr(new int(5));
    
    shared_ptr<int> ptr2 = ptr;
    shared_ptr<int> ptr3 = ptr2;
    
    cout << ptr.getRefCount() << endl;
}
