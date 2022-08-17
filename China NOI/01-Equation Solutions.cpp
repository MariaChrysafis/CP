#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<int> ma;
vector<int> p, k;
int M;
int res = 0;
bool b;
int powr[7][151];
vector<pair<int,int> > v;
void generate() {
    while (!ma.empty()) {
        int cur = ma.back();
        int cntr = 0;
        while (!ma.empty() && ma.back() == cur) {
            cntr++;
            ma.pop_back();
        }
        v.push_back(make_pair(cur, cntr));
    }
}
int bs (int x) {
    int l = 0;
    int r = v.size() - 1;
    while (l != r) {
        int m = (l + r)/2;
        if (v[m].first >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if (v[l].first == x) return v[l].second;
    return 0;
}
void rec (int sz, int ans) {
    if (sz == p.size()) {
        if (b) {
        	ma.push_back(ans);
        } else {
            res += bs(-ans);
        }
        return;
    }
    for (int i = 1; i <= M; i++) {
        rec(sz + 1, ans + k[sz] * powr[p[sz]][i]);
    }
}
bool comp (pair<int,int> p, pair<int,int> q) {
    if (q.second == p.second) {
        return (q.first < p.first);
    }
    return (q.second < p.second);
}
int main() {
    for (int i = 1; i < 7; i++) for (int j = 1; j <= 150; j++) powr[i][j] = pow(j, i);
	int n;
    cin >> n >> M;
    vector<pair<int,int> > vec(n);
    for (int i = 0; i < n; i++) cin >> vec[i].first >> vec[i].second;
    for (int i = 0; i < n/2; i++) {
    	p.push_back(vec[i].second), k.push_back(vec[i].first);
    }
    b = true;
    rec(0, 0);
    sort(ma.begin(), ma.end());
    generate();
    reverse(v.begin(), v.end());
    p.clear(), k.clear();
    for (int i = n/2; i < n; i++) {
    	p.push_back(vec[i].second), k.push_back(vec[i].first);
    }
    b = false;
    rec(0, 0);
    cout << res << '\n';
}
