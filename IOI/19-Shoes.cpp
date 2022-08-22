#include <bits/stdc++.h>
#include "shoes.h"
 
using namespace std;
 
template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
 
int64_t get_inversions(vector<int> v) {
    SegmentTree<int> st(v.size() + 3);
    int64_t ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans += st.query(v[i] + 1, v.size() + 2);
        st.update(v[i], st.query(v[i], v[i]) + 1);
    }
    return ans;
}
 
long long count_swaps(vector<int> v) {
    map<int, set<int>> myMap;
    for (int i = 0; i < v.size(); i++) {
        myMap[v[i]].insert(i);
    }
    vector<int> vec(v.size());
    int cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        if (myMap[-v[i]].empty()) continue;
        if (myMap[v[i]].count(i) == false) continue;
        int x = *myMap[-v[i]].begin();
        myMap[-v[i]].erase(x);
        myMap[v[i]].erase(i);
        vec[i] = cntr++;
        vec[x] = cntr++;
        if (v[i] > 0) {
            swap(vec[i], vec[x]);
        }
    }
    return get_inversions(vec);
}
