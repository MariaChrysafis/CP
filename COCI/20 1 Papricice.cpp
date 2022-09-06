#include <bits/stdc++.h>

using namespace std;
vector<int> parent, sub;
vector<vector<int> > adj;
int n;
void dfs (int curNode, int prevNode) {
    sub[curNode] = 1;
    parent[curNode] = prevNode;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
            sub[curNode] += sub[i];
        }
    }
}
set<int> pos;
int ans = INT_MAX;
void rec (int curNode, int prevNode) {
    if (prevNode != -1) pos.insert(sub[prevNode]);
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            rec (i, curNode);
        }
    }
    auto it = pos.lower_bound((n + sub[curNode] + 1)/2);
    int a = sub[curNode];
    if (it != pos.end()) {
        int b = *it;
        if (a <= n - b) {
            ans = min(ans, b - 2 * a);
        }
    }
    it = pos.lower_bound((n + sub[curNode] + 1)/2);
    if (it != pos.end()) {
        //n - b <= b - a <= a
        int b = *it;
        if (b - a <= a) {
            ans = min(ans, a + b - n);
        }
    }
    it = pos.upper_bound(min(2 * a, n - a));
    if (it != pos.begin()) {
        it--;
        int b = *it;
        ans = min(ans, n - b - (b - a));
    }
    if (prevNode != -1) pos.erase(sub[prevNode]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    adj.resize(n), parent.resize(n), sub.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    int t = 13;
    while (t--) {
        int i = rand() % n;
        dfs (i, -1), rec(i, -1);
    }
    cout << ans;
}
