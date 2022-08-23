#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>


using namespace std;

const int MOD = 998244353;
const int BASE = 293;
const int inv = 705244304;

int64_t binPow (int64_t x, int64_t y) {
    int64_t ans = 1; int64_t res = x;
    while (y) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}


class Tree {
public:
    vector<int> sub, depth, parent;
    vector<int64_t> dp1, dp2;
    vector<bool> hasVisited;
    vector<int> adj[(int)5e4];
    vector<int64_t> powr, ipowr;
    int dp[(int)5e4][17];
    string s;
    int sz;
    int dfs1 (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode) sub[curNode] += dfs1(i, curNode);
        return (sz = sub[curNode]);
    }
    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode && sub[i] > sz/2) return get_centroid(i, curNode);
        return curNode;
    }
    int max_len; int fine = 0;
    void fill (int curNode, int prevNode, int d, int64_t val1, int64_t val2) {
        dp1[curNode] = val1 = (BASE * val1 + s[curNode]) % MOD;
        dp2[curNode] = val2 = (powr[d] * s[curNode] + val2) % MOD;
        fine += (dp1[curNode] == dp2[curNode] && d + 1 == max_len);
        dp[curNode][0] = prevNode;
        for (int i = 1; i < 17; i++) {
            dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
        }
        depth[curNode] = d;
        parent[curNode] = prevNode;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                fill(i, curNode, d + 1, val1, val2);
            }
        }
    }

    int64_t go_up (int l, int d) {
        while (d) {
            l = dp[l][(int)log2(d & -d)];
            d -= (d & -d);
        }
        return l;
    }

    int centroid;

    __gnu_pbds::gp_hash_table<int, bool> m1;
    vector<int> to_do;
    void dfs (int curNode, int prevNode) {
        if (depth[curNode] + 1 >= max_len) {
            return;
        }
        to_do.push_back(dp1[curNode]);
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i]) {
                dfs (i, curNode);
            }
        }
        if (2 * depth[curNode] + 1 >= max_len) {
            int x = go_up(curNode, max_len - depth[curNode] - 2);
            if (dp1[parent[x]] == dp2[parent[x]]) {
                if (m1.find(((dp1[curNode] - (powr[max_len - depth[curNode] - 1] * dp1[parent[x]]) % MOD + MOD) % MOD + powr[max_len - depth[curNode] - 1] * s[centroid]) % MOD) != m1.end()) {
                    fine ++;
                    return;
                }
            }
        }
    }

    bool solve (int curNode) {
        dfs1(curNode, curNode);
        centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        depth[centroid] = 0;
        for (int i = 0; i < 17; i++) dp[centroid][i] = centroid;
        dp1[centroid] = s[centroid], dp2[centroid] = s[centroid];
        fine += (max_len == 1);
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                fill(i, centroid, 1, s[centroid], s[centroid]);
            }
        }
        m1.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                dfs (i, centroid);
                for (int j: to_do) m1[j] = 1;
                to_do.clear();
            }
        }
        if (fine) return true;
        reverse(adj[centroid].begin(), adj[centroid].end());
        m1.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                dfs (i, centroid);
                for (int j: to_do) m1[j] = 1;
                to_do.clear();
            }
        }
        if (fine) return true;
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                if (solve(i)) {
                    return true;
                }
            }
        }
        return false;
    }
    Tree (int n) {
        sub.resize(n), hasVisited.assign(n, false); powr.push_back(1); for (int i = 0; i <= n + 5; i++) powr.push_back(powr.back() * BASE), powr.back() %= MOD;
        ipowr.push_back(1); for (int i = 0; i <= n + 5; i++) ipowr.push_back(ipowr.back() * inv), powr.back() %= MOD;
        parent.resize(n), depth.resize(n), dp1.resize(n), dp2.resize(n);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.adj[u].push_back(v), myTree.adj[v].push_back(u);
    }
    myTree.s = s;
    int myMax = 0;
    int l = 0;
    int r = s.length()/2;
    while (l != r) {
        int m = (l + r + 1)/2;
        myTree.max_len = 2 * m; myTree.fine = 0; myTree.hasVisited.assign(n, false);
        myTree.solve(0);
        if (myTree.fine) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    myMax = max(myMax, 2 * l); l = 0;
    r = s.length()/2;
    while (l < r) {
        int m = (l + r + 1)/2;
        myTree.max_len = 2 * m + 1; myTree.fine = 0; myTree.hasVisited.assign(n, false);
        myTree.solve(0);
        if (myTree.fine) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    myMax = max(myMax, 2 * l + 1);
    cout << myMax;
}
