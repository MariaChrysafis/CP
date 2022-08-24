#include <bits/stdc++.h>
 
using namespace std;
const int MOD = 1e9 + 9;
 
struct segmentTreePoint {
    vector<int> v;
    vector<int> vec;
    vector<int> addLater;
 
    void upd(int dum, int tl, int tr, int &l, int &r, int val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }
 
    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }
 
    int get(int x) {
        int cur = x + v.size();
        int ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }
 
    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
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
    segmentTreePoint st;
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
 
    void increment (int a, int b) {
        if (topchain[a] == topchain[b]) {
            st.upd(id[b] + 1, id[a], 1);
            return;
        }
        if (topchain[a] != a) {
            increment(topchain[a], b);
            st.upd(id[topchain[a]] + 1, id[a], 1);
        } else {
            increment(parent[a], b);
            st.upd(id[a], id[a], 1);
        }
    }
 
    bool isAncestor(int u, int v) {
        return (en[u] <= en[v] && ex[u] >= ex[v]);
    }
 
    int lca(int u, int v) {
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
 
    void read () {
        depth.resize(adj.size());
        dp.resize(adj.size());
        rec(0, -1); //fill in all of the subtrees
        topchain[0] = 0;
        cntr = 0;
        dfs(0, -1); //fill in all of the ids and stuff
    }
};
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    vector<pair<int,int>> paths;
    HeavyLightDecomposition hld(N);
    map<pair<int,int>,int> myMap;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myMap[{u, v}] = myMap[{v, u}] = i;
        hld.add_edge(u, v);
    }
    hld.read();
    while (M--) {
        int sz; cin >> sz;
        vector<pair<int,int>> nodes(sz);
        for (int i = 0; i < sz; i++) {
            int x; cin >> x; x--;
            nodes[i] = {hld.en[x], x};
        }
        sort(nodes.begin(), nodes.end());
        for (int i = 0; i < nodes.size(); i++) {
            if (hld.isAncestor(nodes[(i + 1) % nodes.size()].second, nodes[i].second)) {
                paths.emplace_back(nodes[(i + 1) % nodes.size()].second, nodes[i].second);
            } else if (hld.isAncestor(nodes[i].second, nodes[(i + 1) % nodes.size()].second)) {
                paths.emplace_back(nodes[i].second, nodes[(i + 1) % nodes.size()].second);
            } else {
                int l = hld.lca(nodes[i].second, nodes[(i + 1) % nodes.size()].second);
                paths.emplace_back(l, nodes[i].second);
                paths.emplace_back(l,nodes[(i + 1) % nodes.size()].second);
                //hld.st.upd(hld.id[l], hld.id[l], -1);
            }
        }
    }
    for (auto& p: paths) {
        hld.increment(p.second, p.first);
    }
    vector<int> ans;
    for (int i = 0; i < hld.adj.size(); i++) {
        int x = hld.st.get(hld.id[i]);
        if (x / 2 >= K) {
            ans.push_back(myMap[{i, hld.parent[i]}] + 1);
        }
    }
    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (int i: ans) {
        cout << i << " ";
    }
}
