#include <iostream>

using namespace std;

class smartpointer
{
private:
        int* p; // ordinary pointer
public:
        smartpointer(int n)
    {
        p = new int[n];
        int* t = p;
        for (int i = 0; i <= 9; i++)
            *t++ = i * i;
    }
    int* operator ++ (int)
    {
        return p++;
    }
    int operator * ()
    {
        return *p;
    }
};
void main()
{
    smartpointer sp(10);
    for (int i = 0; i <= 9; i++)
        cout << *sp++ << endl;
}
