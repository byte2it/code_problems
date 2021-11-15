#include <iostream>
using namespace std;

void F(int* A, int* B, int N) {
    // Set prod to the neutral multiplication element
    int prod = 1;

    for (int i = 0; i < N; ++i) {
        // For element "i" set B[i] to A[0] * ... * A[i - 1]
        B[i] = prod;
        // Multiply with A[i] to set prod to A[0] * ... * A[i]
        prod *= A[i];
    }

    // Reset prod and use it for the right elements
    prod = 1;

    for (int i = 0; i < 4; ++i) {
        cout << B[i] << ", ";
    }

    for (int i = N - 1; i >= 0; --i) {
        // For element "i" multiply B[i] with A[i + 1] * ... * A[N - 1]
        B[i] *= prod;
        // Multiply with A[i] to set prod to A[i] * ... * A[N - 1]
        prod *= A[i];
    }
}

int main()
{
    int A[4] = { 2, 1, 5, 9 };
    int B[4] = { 0 };

    F(A, B, 4);

    for (int i = 0; i < 4; ++i) {
        cout << B[i] << ", ";
    }    
}
