#include <bits/stdc++.h>

using namespace std;
int parent[60], pre[60], post[60];
int64_t dp[60][60];
vector<int> adj[60];
int cntr = 0;
map<pair<int,int>,int> myMap;
void dfs (int curNode, int prevNode) {
    pre[curNode] = cntr++;
    parent[curNode] = prevNode;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
        }
    }
    post[curNode] = cntr++;
}
bool isAncestor (int u, int v) {
    return (pre[u] <= pre[v] && post[u] >= post[v]);
}
int64_t get_mask (int u, int v) {
    if (dp[u][v] != -1) {
        return dp[u][v];
    }
    if (u == v) {
        return (dp[u][v] = 0);
    }
    if (isAncestor(u, v)) {
        swap(u, v);
    }
    return get_mask(parent[u], v) | ((int64_t)1 << myMap[make_pair(u, parent[u])]);
}
const int MOD = 1e9 + 7;
int mult (int x, int y) {
    return ((int64_t) x * (int64_t) y) % MOD;
}
int64_t binPow (int64_t x, int y) {
    int64_t res = x, ans = 1;
    while (y > 0 ) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res), y /= 2;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            dp[i][j] = -1;
        }
    }
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int,int> > edges;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
        edges.push_back(make_pair(a, b));
        myMap[make_pair(a, b)] = myMap[make_pair(b, a)] = i;
    }
    dfs(0, 0);
    vector<pair<int,int> > paths;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        paths.push_back(make_pair(a, b));
    }
    int64_t ans = 0;
    for (int64_t i = 0; i < ((int64_t)1 << m); i++) {
        vector<int64_t> vec;
        for (int j = 0; j < m; j++) {
            if (i & ((int64_t)1 << j)) {
                vec.push_back(get_mask(paths[j].first, paths[j].second));
            }
        }
        int64_t tot = 0;
        for (int x = 0; x < vec.size(); x++) {
            for (int y = 0; y < vec.size(); y++) {
                if (vec[x] & vec[y]) {
                    vec[x] = vec[y] = vec[x] | vec[y];
                    tot = tot | vec[x];
                }
            }
        }
        set<int64_t> s;
        tot ^= (((int64_t)1 << (n - 1)) - 1);
        for (int64_t x: vec) {
            s.insert(x);
        }
        ans += (int64_t)binPow(k, (int)__builtin_popcountll(tot) + (int)s.size()) * pow(-1, __builtin_popcountll(i));
        ans += MOD, ans %= MOD;
    }
    cout << ans << '\n';
}
