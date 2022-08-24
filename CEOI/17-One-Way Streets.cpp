#include <bits/stdc++.h>
 
using namespace std;
class BridgeFinder {
public:
    int n; // number of nodes
    vector<vector<int>> adj; // adjacency list of graph
    map<pair<int,int>,bool> isBridge;
    vector<bool> visited;
    vector<int> tin, low;
    int timer;
 
    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])
                    isBridge[{v, to}] = isBridge[{to, v}] = true;
            }
        }
    }
 
    void find_bridges() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
        for (int i = 0; i < adj.size(); i++) {
            sort(adj[i].begin(), adj[i].end());
            for (int j = 1; j < adj[i].size(); j++) {
                if (adj[i][j] == adj[i][j - 1]) {
                    isBridge[{i, adj[i][j]}] = isBridge[{adj[i][j], i}] = false;
                }
            }
        }
    }
};
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }
 
public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }
 
    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }
 
    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }
 
    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
class Graph {
public:
    vector<vector<int>> adj;
    vector<bool> hasVisited;
    vector<vector<int>> tree_adj;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                tree_adj[curNode].push_back(i);
                tree_adj[i].push_back(curNode);
                dfs (i);
            }
        }
    }
    Graph (vector<vector<int>> adj) {
        this->adj = adj;
        hasVisited.assign(adj.size(), false);
        tree_adj.resize(adj.size());
        dfs(0);
    }
};
struct segmentTree {
    vector<int64_t> vec;
    vector<int64_t> setLater;
 
    void push(int v, int tl, int tr) {
        if (setLater[v] == -1) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = setLater[v] * (tr - tm);
        setLater[2 * v] = setLater[v];
        vec[2 * v] = setLater[v] * (tm - tl + 1);
        setLater[v] = -1;
    }
 
    const int64_t INF = 0;
 
    int64_t upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            return (vec[dum] = val * (tr - tl + 1));
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
    }
 
    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }
 
    int64_t get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }
 
    int64_t get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }
 
    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, -1);
    }
 
};
class HeavyLightDecomposition {
public:
    vector<vector<int>> adj;
    vector<int> sub;
    vector<int> id;
    vector<int> topchain;
    vector<int> depth;
    vector<int> parent;
    segmentTree st;
    vector<vector<int>> dp;
    vector<int> en;
    vector<int> ex;
    int cntr = 0;
    const int lg2 = 30;
 
    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
 
    void rec(int curNode, int prevNode) {
        parent[curNode] = prevNode;
        en[curNode] = cntr++;
        if (prevNode != -1) {
            depth[curNode] = depth[prevNode] + 1;
        } else {
            depth[curNode] = 0;
        }
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                rec(i, curNode);
                sub[curNode] += sub[i];
            }
        }
        ex[curNode] = cntr++;
    }
 
    HeavyLightDecomposition(int n) {
        adj.resize(n);
        sub.resize(n);
        id.resize(n);
        topchain.assign(n, -1);
        parent.resize(n);
        st.resz(n + 1);
        ex.resize(n), en.resize(n);
    }
 
    void dfs(int curNode, int prevNode) {
        id[curNode] = cntr++;
        vector<pair<int, int>> vec;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                vec.push_back({sub[i], i});
            }
        }
        dp[curNode].resize(32);
        dp[curNode][0] = max(prevNode, 0);
        for (int i = 1; i < dp[curNode].size(); i++) {
            dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
        }
        if (!vec.empty()) {
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
            topchain[vec[0].second] = topchain[curNode];
            for (int i = 1; i < vec.size(); i++) {
                topchain[vec[i].second] = vec[i].second;
            }
            for (auto &p: vec) {
                dfs(p.second, curNode);
            }
        }
    }
 
    void f (int a, int b, int d) {
        if (a == b) {
            return;
        }
        if (topchain[a] == topchain[b]) {
            st.upd(id[b] + 1, id[a], d);
        } else if (topchain[a] != a) {
            st.upd(id[topchain[a]] + 1, id[a], d);
            f(topchain[a], b, d);
        } else {
            st.upd(id[a], id[a], d);
            f(parent[a], b, d);
        }
    }
 
    bool isAncestor(int u, int v) {
        return (en[u] <= en[v] && ex[u] >= ex[v]);
    }
 
    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
 
 
    void read() {
        depth.resize(adj.size());
        dp.resize(adj.size());
        rec(0, -1); //fill in all of the subtrees
        topchain[0] = 0;
        cntr = 0;
        dfs(0, -1); //fill in all of the ids and stuff
    }
};
 
string ans;
 
void proccess (vector<pair<pair<int,int>,int>> edges, vector<pair<int,int>> queries) {
    set<int> s;
    for (auto& p: edges) s.insert(p.first.first), s.insert(p.first.second);
    map<int,int> myMap; int cntr = 0;
    for (int i: s) myMap[i] = cntr++;
    for (int i = 0; i < edges.size(); i++) {
        edges[i].first.first = myMap[edges[i].first.first], edges[i].first.second = myMap[edges[i].first.second];
    }
    for (int i = 0; i < queries.size(); i++) {
        queries[i].first = myMap[queries[i].first], queries[i].second = myMap[queries[i].second];
    }
    vector<vector<int>> adj(s.size());
    for (int i = 0; i < edges.size(); i++) {
        adj[edges[i].first.first].push_back(edges[i].first.second);
        adj[edges[i].first.second].push_back(edges[i].first.first);
    }
    BridgeFinder bf; bf.n = adj.size(); bf.adj = adj; bf.find_bridges();
    Graph gr(adj);
    adj = gr.tree_adj;
    HeavyLightDecomposition hld(gr.tree_adj.size());
    hld.adj = adj; hld.read();
    for (int i = 0; i < queries.size(); i++) {
        int lca = hld.leastCommonAncestor(queries[i].first, queries[i].second);
        hld.f(queries[i].first, lca, 1);
        hld.f(queries[i].second, lca, 2);
    }
    for (int i = 1; i < adj.size(); i++) {
        if (!bf.isBridge[{i, hld.parent[i]}]) {
            hld.st.upd(hld.id[i], hld.id[i], 0);
        }
    }
    for (int i = 0; i < edges.size(); i++) {
        int nd;
        if (hld.isAncestor(edges[i].first.second, edges[i].first.first)) {
            nd = edges[i].first.first;
        } else {
            nd = edges[i].first.second;
        }
        if (hld.st.get(hld.id[nd], hld.id[nd]) == 0) {
            ans[edges[i].second] = 'B';
        } else if (hld.st.get(hld.id[nd], hld.id[nd]) == 1) {
            if (nd == edges[i].first.first) ans[edges[i].second] = 'R';
            else ans[edges[i].second] = 'L';
        } else {
            if (nd == edges[i].first.first) ans[edges[i].second] = 'L';
            else ans[edges[i].second] = 'R';
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<pair<pair<int,int>,int>> edges;
    DisjointSetUnion dsu(N);
    map<pair<int,int>,int> cnt;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cnt[{u, v}]++, cnt[{v, u}]++;
        assert(u != v);
        edges.emplace_back(make_pair(u, v), i), dsu.join(u, v);
    }
    int Q; cin >> Q; vector<pair<int,int>> queries;
    for (int i = 0; i < Q; i++) {
        int u, v; cin >> u >> v; u--, v--;
        queries.emplace_back(u, v);
    }
 
    vector<pair<pair<int,int>,int>> edges1[N];
    vector<pair<int,int>> queries1[N];
    for (int i = 0; i < M; i++) {
        edges1[dsu.find_head(edges[i].first.first)].push_back(edges[i]);
    }
    for (int i = 0; i < Q; i++) {
        queries1[dsu.find_head(queries[i].first)].push_back(queries[i]);
    }
    ans.assign(edges.size(), '?');
    for (int i = 0; i < N; i++) {
        if (!edges1[i].empty()) {
            proccess(edges1[i], queries1[i]);
        }
    }
    for (int i = 0; i < edges.size(); i++) {
        if (cnt[edges[i].first] >= 2) {
            ans[i] = 'B';
        }
    }
    cout << ans << '\n';
}
