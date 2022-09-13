#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > adj;
vector<int> leaves, parent;
void dfs (int cur, int prev) {
    parent[cur] = prev;
    if (adj[cur].size() == 1) {
        leaves.push_back(cur);
    }
    for (int i: adj[cur]) {
        if (i != prev) {
            dfs (i, cur);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    adj.resize(n), parent.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    int rt = -1;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() != 1) {
            dfs (i, i);
            rt = i;
            break;
        }
    }
    int sz = ((int)leaves.size() + 1)/2;
    cout << sz << '\n';
    if (leaves.size() % 2 == 1) {
        cout << leaves.back() + 1 << " " << leaves[0] + 1 << '\n';
        leaves.pop_back();
    }
    for (int i = 0; i < leaves.size()/2; i++) {
        cout << leaves[i] + 1 << " " << leaves[i + (int)leaves.size()/2] + 1 << '\n';
    }
}
