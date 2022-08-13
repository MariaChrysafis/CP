#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
 

struct SparseTable {
    vector<vector<int > > dp;
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTable (vector<int> v) {
        int n = v.size();
        dp.assign(n, vector<int>(32));
        for (int i = 0; i < n; i++) {
            dp[i][0] = v[i];
        }
        for (int j = 1; j < dp[0].size(); j++) {
            for (int i = 0; i < n; i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), n - 1)][j - 1]);
            }
        }
    }
};

bool comp (pair<char,int> p1, pair<char,int> p2) {
    if ((p1.first == 'I') == (p2.first == 'I')) return false;
    if (p1.first == 'I') return true;
    return false; 
}
void alter (vector<pair<char,int> > &vec, vector<vector<int> > & del, vector<pair<int,int> > indices) {
    vector<pair<char,int> > v;
    vector<int> ind;
    ind.assign(vec.size(), -1);
    for (auto& p: indices) {
        ind[p.first] = p.second;
    }
    int cntr = 0;
    for (int i = 0; i < vec.size(); i++) {
        v.push_back(vec[i]);
        for (auto& x: del[i]) {
            v.push_back(make_pair('R', x));
        }
    }
    vec = v;
}
 
int main () {
    int n, mn;
    cin >> n >> mn;
    vector<pair<char,int> > vec;
    vector<pair<int,int> > indices;
    int sum = 0;
    vector<int> pref;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        int x; cin >> x;
        if (c == 'I') {
            ans -= (x < mn);
            x -= sum;
            indices.push_back(make_pair(i, x));
        } else if (c == 'S') {
            sum -= x;
        } else if (c == 'A') {
            sum += x;
        } 
        pref.push_back(sum);
        vec.push_back(make_pair(c, x));
    }
    SparseTable st(pref);
    vector<vector<int> > del(n);
    int cntr = -1;
    for (auto& p: indices) {
        int l = p.first;
        int r = n - 1;
        cntr++;
        if (st.query(p.first, n - 1) + p.second >= mn) {
            continue;
        }
        while (l != r) {
            int m = (l + r)/2;
            if (st.query(p.first, m) + p.second < mn) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        del[l].push_back(cntr);
    }
    alter(vec, del, indices);
    ordered_set mySet;
    vector<int> val; val.assign(indices.size(), 0);
    cntr = 0;
    for (auto& p: indices) {
        val[cntr++] = p.second;
    }
    cntr = 0;
    sum = 0;
    for (auto& p: vec) {
        if (p.first == 'I') {
            mySet.insert(make_pair(val[cntr], cntr));
            cntr++;
        } else if (p.first == 'S') {
            sum -= p.second;
        } else if (p.first == 'R') {
           mySet.erase(make_pair(val[p.second], p.second));
           ans++;
        } else if (p.first == 'F') {
            if (p.second > mySet.size()) {
                cout << -1 << '\n';
                continue;
            }
            auto q = *mySet.find_by_order(mySet.size() - p.second);
            cout << q.first + sum << '\n';
        } else if (p.first == 'A') {
            sum += p.second;
        }
    }
    cout << ans << '\n';
}
