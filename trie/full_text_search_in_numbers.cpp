#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define null NULL

struct Node {
    set<int> indices;
    Node* child[10];
}*root;


Node* add(Node* root, string s, int cur, int index) {

    if (root == null) {
        root = new Node();
    }
    root->indices.insert(index);
    if (cur != s.size())
        root->child[s[cur] - '0'] = add(root->child[s[cur] - '0'], s, cur + 1, index);
    return root;
}

void createSuffixTree(vector<string> numbers) {
    int N = numbers.size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numbers[i].size(); j++)
            root = add(root, numbers[i].substr(j, numbers[i].size()), 0, i);
    }
}

set<int> count(Node* root, string s, int cur) {
    if (root == null) return set<int>();

    if (cur == (int)s.size())
        return root->indices;
    else
        return count(root->child[s[cur] - '0'], s, cur + 1);
}

int main() {

    vector<string> numbers = { "1234", "567", "890",
                               "4124", "123", "123",
                               "3123", "123", "322" };

    createSuffixTree(numbers);

    string t;
    while (cin >> t) {
        set<int> ans = count(root, t, 0);
        for (auto x : ans)
            cout << numbers[x] << " ";
        cout << endl;
    }

    return 0;
}
