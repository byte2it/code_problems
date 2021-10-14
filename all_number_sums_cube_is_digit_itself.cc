#include<stdio.h>
#include <algorithm>



int main() {
    int num, sum = 0, i;
    scanf_s("%d", &num);
    for (i = num; i != 0; i /= 10)
        sum += pow(i % 10, 3);
    if (sum == num)
        return(1);
    else
        return(0);
}all_number_
