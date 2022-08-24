#include <bits/stdc++.h>
using namespace std;
class Tree {
private:
    int root;
    vector<vector<pair<int64_t,int64_t>>> adj; //node, weight
    vector<int64_t> parent, depth, sub, pre, post;
    map<pair<int64_t,int64_t>,int64_t> weight;
    vector<bool> isVillage;
    vector<vector<int64_t>> jmp, dp;
public:
    Tree (int64_t N, int64_t root) {
        adj.resize(N), this->root = root, parent.resize(N), depth.resize(N), isVillage.assign(N, false), sub.resize(N), pre.resize(N), post.resize(N);
    }
    void add_edge (int64_t u, int64_t v, int64_t w) {
        adj[u].push_back({v, w}), adj[v].push_back({u, w}), weight[{u, v}] = weight[{v, u}] = w;
    }
    void update_village (int u) {
        isVillage[u] = true;
    }
    int64_t cntr = 0;
    void dfs (int64_t curNode, int64_t prevNode) {
        parent[curNode] = prevNode, sub[curNode] = -1, pre[curNode] = cntr++;
        if (curNode == root) {
            depth[curNode] = 0;
        } else {
            depth[curNode] = depth[prevNode] + weight[{curNode, prevNode}];
        }
        for (pair<int64_t,int64_t> p: adj[curNode]) {
            if (p.first != prevNode) {
                dfs(p.first, curNode);
                if (sub[p.first] != -1) {
                    sub[curNode] = chmin(sub[p.first] + weight[{curNode, p.first}], sub[curNode]);
                }
            }
        }
        if (isVillage[curNode]) {
            sub[curNode] = 0;
        }
        post[curNode] = cntr++;
    }
    bool isAncestor (int64_t a, int64_t b) {
        //is a an ancestor of b?
        return (pre[a] <= pre[b] && post[a] >= post[b]);
    }
    int64_t chmin (int64_t a, int64_t b) {
        if (a == -1) return b;
        if (b == -1) return a;
        return min(a, b);
    }
    int64_t query (int64_t a1, int64_t a2, int64_t b) {
        if (parent[a1] != a2) {
            swap(a1, a2);
        }
        if (!isAncestor(a1, b)) {
            return -1;
        }
        int64_t x = b;
        int64_t ans = -1;
        for (int i = 31; i >= 0; i--) {
            if (isAncestor(a1, jmp[x][i])) {
                if (dp[x][i] != -1) {
                    ans = chmin(ans, dp[x][i] + abs(depth[x] - depth[b]));
                }
                x = jmp[x][i];
            }
        }
        if (sub[a1] != -1) {
            ans = chmin(ans, sub[a1] + abs(depth[b] - depth[a1]));
        }
        if (ans == -1) {
            return LLONG_MAX;
        }
        return ans;
    }
    void read () {
        dfs(root, -1);
        jmp.resize(adj.size());
        dp.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            jmp[i].resize(32);
            dp[i].resize(32);
            jmp[i][0] = parent[i];
        }
        jmp[root][0] = root;
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < adj.size(); i++) {
                jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
            }
        }
        for (int j = 0; j < 32; j++) {
            for (int i = 0; i < adj.size(); i++) {
                if (j == 0) {
                    dp[i][j] = sub[i];
                    if (sub[jmp[i][0]] != -1) {
                        dp[i][j] = chmin(dp[i][j], sub[jmp[i][0]] + weight[{jmp[i][0], i}]);
                    }
                    dp[root][0] = sub[root];
                } else {
                    dp[i][j] = dp[i][j - 1];
                    if (dp[jmp[i][j - 1]][j - 1] != -1) {
                        dp[i][j] = chmin(dp[i][j], dp[jmp[i][j - 1]][j - 1] + abs(depth[jmp[i][j - 1]] - depth[i]));
                    }
                }
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, S, Q, E;
    cin >> N >> S >> Q >> E;
    E--;
    Tree myTree(N, E);
    vector<pair<int64_t,int64_t>> edges;
    for (int i = 0; i < N - 1; i++) {
        int64_t u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.emplace_back(u, v), myTree.add_edge(u, v, w);
    }
    while (S--) {
        int64_t x; cin >> x; x--; myTree.update_village(x);
    }
    myTree.read();
    while (Q--) {
        int64_t u, v;
        cin >> u >> v;
        u--, v--;
        int64_t x = myTree.query(edges[u].first, edges[u].second, v);
        if (x == -1) {
            cout << "escaped\n";
        } else if (x == LLONG_MAX) {
            cout << "oo\n";
        } else {
            cout << x << '\n';
        }
    }
}
