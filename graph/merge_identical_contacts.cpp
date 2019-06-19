#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Item {
    vector<string> list;
    int index;
    bool visited;
};

vector<vector<int> > merge(vector<vector<string> >& v) {

    vector<vector<int> > res(v.size());

    multimap<string, Item*> m;
    vector<Item*> items;

    for (int i = 0; i < v.size(); ++i) {

        Item* item = new Item();
        item->index = i;
        item->visited = false;
        for (int j = 1; j < v[i].size(); ++j) {
            item->list.push_back(v[i][j]);
            m.insert(make_pair(v[i][j], item));
        }

        items.push_back(item);
    }

    for (int i = 0; i < items.size(); ++i) {
        queue<Item*> st;

        st.push(items[i]);
        Item* p;
        while (!st.empty()) {
            p = st.front();
            st.pop();

            if (p->visited)
                break;

            res[i].push_back(p->index);
            p->visited = true;
            for (int j = 0; j < p->list.size(); ++j) {
                auto pI = m.find(p->list[j]);

                while (pI != m.end() && pI->first == p->list[j]) {
                    if (!pI->second->visited) {
                        st.push(pI->second);
                    }
                    ++pI;
                }
            }
        }
    }

    return res;
}

int main() {

    vector<vector<string> > vs =
    { {"John", "john@gmail.com", "john@fb.com"},
        {"Dan", "dan@gmail.com", "+1234567"},
        {"john123", "+5412312", "john123@skype.com"},
        {"john1985", "+5412312", "john@fb.com"} };

    vector<vector<int > > res = merge(vs);
    return 0;
}
