#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
 
using namespace std;
template<class T>
class SegmentTree {
public:
 
    void resz (int N) {
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
    T ID = 1;
    T merge (T x, T y) {
        return x & y;
    }
    int N;
};
vector<int> arr;
vector<pair<int,int> > queries;
SegmentTree<bool> valid;
vector<int> cnt;
map<int,int> myMap;
void updater (int x, int d) {
    if (!myMap.count(arr[x])) {
        return;
    }
    cnt[myMap[arr[x]]] += d;
    valid.update(myMap[arr[x]], cnt[myMap[arr[x]]] >= queries[myMap[arr[x]]].second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K, R;
    cin >> N >> K >> R;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    queries.resize(R);
    for (int i = 0; i < R; i++) {
        cin >> queries[i].first >> queries[i].second;
        myMap[queries[i].first] = i;
    }
    cnt.resize(R);
    valid.resz(R);
    for (int i = 0; i < R; i++) {
        valid.update(i, 0);
    }
    int l = -1;
    int r = -1;
    int myMin = INT_MAX;
    while (l + 1 < N && r < N) {
        if (l != -1) {
            updater(l, -1);
        }
        l++;
        while (r != N - 1 && !valid.query(0, R - 1)) {
            updater(r + 1, 1);
            r++;
        }
        if (!valid.query(0, R - 1)) {
            break;
        }
        myMin = min(myMin, r - l + 1);
    }
    if (myMin == INT_MAX) {
        cout << "impossible\n";
    } else {
        cout << myMin << '\n';
    }
}
