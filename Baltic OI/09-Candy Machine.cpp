#include <bits/stdc++.h>
 
using namespace std;
vector<pair<int,int>> vec;
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
    T ID = -5;
    T merge (T x, T y) {
        return max(x, y);
    }
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n; vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].second >> vec[i].first;
    }
    sort(vec.begin(), vec.end());
    bool vis[vec.size()];
    for (int i = 0; i < n; i++) {
        int slot = vec[i].second;
        int time = vec[i].first;
        vec[i].first = -slot + time;
        vec[i].second = slot + time;
        vis[i] = false;
    }
    sort(vec.begin(), vec.end());
    vector<pair<pair<int,int>,int>> ans;
    set<pair<int,int>> s;
    for (int i = 0; i < vec.size(); i++) {
        s.insert({vec[i].second, i});
    }
    SegmentTree<int> st(n);
    for (int i = 0; i < n; i++) {
        st.update(i, vec[i].second);
    }
    int cntr = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (st.query(i, i) == -1) continue;
        cntr++;
        int ind = i;
        while (true) {
            st.update(ind, -1);
            ans.push_back({{(vec[ind].second - vec[ind].first)/2, (vec[ind].second + vec[ind].first)/2}, cntr});
            if (st.query(ind + 1, n - 1) < vec[ind].second) {
                break;
            }
            int l = ind + 1;
            int r = n - 1;
            while (l != r) {
                int m = (l + r)/2;
                if (st.query(ind + 1, m) >= vec[ind].second) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            ind = l;
        }
    }
    cout << cntr << '\n';
    for (auto& p: ans) {
        cout << p.first.first << " " << p.first.second << " " << p.second << '\n';
    }
}
