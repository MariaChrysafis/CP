#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<int> new_adj[5000];
int val[5000];
void dfs (int curNode, int prevNode) {
    val[curNode] = 1;
    for (int i: new_adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
            val[curNode] += val[i];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> adj[5000];
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int a;
            cin >> a;
            a--;
            adj[a].push_back(i);
        }
    }
    int myMin = INT_MAX;
    for (int i = 0; i < n; i++) {
        queue<int> q;
        q.push(i);
        vector<bool> hasVisited; hasVisited.assign(n, false);
        hasVisited[i] = true;
        for (int j = 0; j < n; j++) {
            new_adj[j].clear();
        }
        while (!q.empty()) {
            int curNode = q.front();
            q.pop();
            for (int j: adj[curNode]) {
                if (!hasVisited[j]) {
                    q.push(j);
                    hasVisited[j] = true;
                    new_adj[curNode].push_back(j);
                }
            }
        }
        bool fine = true;
        for (bool j: hasVisited) {
            if (!j) {
                fine = false;
            }
        }
        if (!fine) {
            continue;
        }
        dfs(i, i);
        int ans = 0;
        for (int j: val) {
            ans += j;
        }
        myMin = min(myMin, ans);
    }
    cout << myMin << '\n';
}
