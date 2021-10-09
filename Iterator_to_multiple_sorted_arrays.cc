
#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

template<> struct hash<std::set<int>::iterator>
{
	std::size_t operator()(std::set<int>::iterator const& iter) const noexcept
	{
		return  (std::size_t) & (*iter);
	}
};

class MyIterator {

	set<int> mq;
	unordered_map<set<int>::iterator, int> mmap;
	vector<int> cur_idxs;

	vector<vector<int> > m_arrs;

public:
	MyIterator(vector<vector<int> >& arrs, int n) : m_arrs(arrs), cur_idxs(n){
		for (int i = 0; i < n; ++i) {
			auto it = mq.insert(arrs[i][0]);
			mmap[it.first] = i;
			cur_idxs[i] = 0;
	   }
	}

	int next() {
		if (hasNext()) {
			
			auto iter = mq.begin();
			int res = *iter;
			auto idx_iter = mmap.find(iter);
			int arr_idx = idx_iter->second;
			mmap.erase(idx_iter);
			mq.erase(iter);

			if ((cur_idxs[arr_idx] + 1) < m_arrs[0].size()) {
				auto new_it = mq.insert(m_arrs[arr_idx][++cur_idxs[arr_idx]]);
				mmap[new_it.first] = arr_idx;
			}
			return res;

		}

		return -1;

	}
	bool hasNext() {
		return !mq.empty();
	}
};

int main()
{
	vector<vector<int> > vv = { {1,5,7},{2,3,10},{4,6,9} };

	MyIterator it(vv, 3);

	while (it.hasNext())
		std::cout << it.next() << ", ";
    std::cout << "Hello World!\n";
}
