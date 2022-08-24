#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
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
        return max(x, y);
    }
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, D; cin >> N >> D;
    vector<int64_t> arr(N); set<int64_t> s;
    for (int i = 0; i < N; i++) {
        cin >> arr[i]; s.insert(arr[i]), s.insert(arr[i] + D);
    }
    unordered_map<int64_t,int> myMap; 
    int cntr = 1;
    for (int64_t i: s) {
        myMap[i] = cntr++;
    }
    cntr++;
    SegmentTree<int> st1(cntr);
    vector<int> remove(N);
    for (int i = 0; i < N; i++) {
        remove[i] = st1.query(myMap[arr[i]], myMap[arr[i]]);
        st1.update(myMap[arr[i]], st1.query(0, myMap[arr[i]] - 1) + 1);
    }
    SegmentTree<int> st2(cntr);
    vector<int> v;
    for (int i = N - 1; i >= 0; i--) {
        st1.update(myMap[arr[i]], remove[i]);
        st2.update(myMap[arr[i] + D], st2.query(myMap[arr[i] + D] + 1, cntr - 1) + 1);
        v.push_back(st1.query(0, myMap[D + arr[i]] - 1) + st2.query(myMap[D + arr[i]] + 1, cntr - 1) + 1);
    }
    int myMax = 0;
    for (int i: v) {
        myMax = max(myMax, i);
    }
    cout << myMax;
}
