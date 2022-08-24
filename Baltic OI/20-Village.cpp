#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > adj;
vector<int> ord;
int t = 0;
int c = 0;
vector<int64_t> pre, post, depth, sub;
vector<vector<int> > dp;
 
bool isAncestor(int u, int v) {
    return (pre[u] <= pre[v] && post[u] >= post[v]);
}
 
int lca(int u, int v) {
    if (isAncestor(u, v)) {
        return u;
    }
    if (isAncestor(v, u)) {
        return v;
    }
    for (int i = 19; i >= 0; i--) {
        if (!isAncestor(dp[u][i], v)) {
            u = dp[u][i];
        }
    }
    return dp[u][0];
}
 
void find_sub(int curNode, int prevNode) {
    sub[curNode] = 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            find_sub(i, curNode), sub[curNode] += sub[i];
        }
    }
}
 
int get_centroid(int curNode, int prevNode) {
    for (int i: adj[curNode]) {
        if (i == prevNode) continue;
        if (sub[i] > (int) adj.size() / 2) return get_centroid(i, curNode);
    }
    return curNode;
}
 
void f(int curNode, int prevNode) {
    depth[curNode] = depth[prevNode] + 1;
    dp[curNode].resize(20);
    dp[curNode][0] = prevNode;
    for (int i = 1; i < 20; i++)dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
    ord[curNode] = t++, pre[curNode] = c++;
    for (int i:adj[curNode]) if (i != prevNode)f(i, curNode);
    post[curNode] = c++;
}
 
vector<int> ans;
int tot = 0;
void dfs (int curNode, int prevNode) {
    for (int i: adj[curNode]) {
        if (i == prevNode) continue;
        dfs(i, curNode);
        if (ans[curNode] == -1 && ans[i] == -1) {
            ans[curNode] = i, ans[i] = curNode, tot++;
        } else if (ans[i] == -1) {
            ans[i] = ans[curNode], ans[curNode] = i, tot++;
        }
    }
 
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    adj.resize(n), depth.assign(n, false), dp.resize(n), pre.resize(n), post.resize(n), sub.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--, adj[u].push_back(v), adj[v].push_back(u);
    }
    find_sub(0, -1);
    ord.resize(n), ans.assign(n, -1);
    int centroid = get_centroid(0, -1);
    f(centroid, centroid);
    dfs(0, -1);
    if (ans[0] == -1) {
        ans[0] = ans[adj[0].back()], ans[adj[0].back()] = 0, tot++;
    }
    int64_t al = 0;
    map<int, int> myMap;
    for (int i = 0; i < ord.size(); i++) {
        myMap[ord[i]] = i;
    }
    vector<int> ansr(n);
    for (int i = 0; i < n; i++) {
        ansr[myMap[i]] = myMap[(i + n / 2 + n) % n];
    }
    for (int i = 0; i < n; i++) {
        al += depth[i] + depth[ansr[i]] - 2 * depth[lca(i, ansr[i])];
    }
    cout << tot * 2 << " " << al << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
    for (int i: ansr) {
        cout << i + 1 << ' ';
    }
 
 
}
