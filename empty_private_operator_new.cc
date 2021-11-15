#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Test {
private:
    void* operator new(size_t size) {}
    void* operator new[](size_t size) {}
};

int main()
{
    Test *obj = new Test;
    Test *arr = new Test[10];
    return 0;
}
