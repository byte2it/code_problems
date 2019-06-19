#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& v, int l, int h, int key) {
    if (l > h) return -1;

    int mid = (l + h) / 2;
    if (v[mid] == key) return mid;

    if (v[l] <= v[mid]) {
        if (key >= v[l] && key <= v[mid])
            return search(v, l, mid - 1, key);
        return search(v, mid + 1, h, key);
    }

    if (key >= v[mid] && key <= v[h])
        return search(v, mid + 1, h, key);

    return search(v, l, mid - 1, key);
}

int main() {
    vector<int> v = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
    int key = 6;
    int i = search(v, 0, v.size() - 1, key);

    if (i != -1)
        cout << "Index: " << i << endl;
    else
        cout << "Key not found";
}
