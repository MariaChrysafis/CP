#include <bits/stdc++.h>
using namespace std;
vector<int> ma;
vector<int> p, k;
int M;
int res = 0;
bool b = true;
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
        if (v[m].first <= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return ((v[l].first != x) ? 0 : v[l].second);
}
void rec (int sz, int ans) {
    if (sz == p.size()) {
        if (b) {
        	ma.push_back(ans);
        } else {
            res += bs(-ans);
        }
    } else {
        for (int i = 1; i <= M; i++) {
            rec(sz + 1, ans + k[sz] * pow(i, p[sz]));
        }
    }
}
int main() {
	int n;
    cin >> n >> M;
    vector<pair<int,int> > vec(n);
    for (int i = 0; i < n/2; i++) {
        int K, P; cin >> K >> P;
    	p.push_back(P), k.push_back(K);
    }
    rec(0, 0);
    sort(ma.begin(), ma.end());
    generate();
    p.clear(), k.clear();
    for (int i = n/2; i < n; i++) {
    	int K, P; cin >> K >> P;
    	p.push_back(P), k.push_back(K);
    }
    b = false;
    rec(0, 0);
    cout << res << '\n';
}
