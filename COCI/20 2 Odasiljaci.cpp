#include <bits/stdc++.h>

using namespace std;
vector<pair<int64_t,int64_t> > points;
struct DisjointSetUnion {
    vector<int> parent, sz;
    int c;
    void join (int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u != v) {
            c--;
            if (sz[u] > sz[v]) {
                swap(u, v);
            }
            parent[u] = v, sz[u] = sz[v] = sz[u] + sz[v];
        }
    }
    int find_head (int x) {
        return ((x == parent[x]) ? x : find_head(parent[x]));
    }
    DisjointSetUnion (int n) {
        c = n;
        for (int i = 0; i < n; i++) {
            parent.push_back(i), sz.push_back(1);
        }
    }
};
int64_t dist (pair<int64_t,int64_t> a, pair<int64_t, int64_t> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}
bool okay (int64_t r) {
    DisjointSetUnion dsu(points.size());
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            if (dist(points[i], points[j]) <= r) {
                dsu.join(i, j);
            }
        }
    }
    return (dsu.c == 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    int64_t l = 0;
    int64_t r = 1e18;
    while (l != r) {
        int64_t m = (l + r )/2;
        if (okay(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << setprecision(30) << sqrt(l)/2.0 << '\n';
}
