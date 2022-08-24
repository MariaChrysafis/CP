#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> adj[(int)5e5];
bool hasVisited[(int)5e5];
bool okay[(int)5e5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        adj[u].emplace_back(v, i), adj[v].emplace_back(u, i);
    }
    for (int i = 0; i < M; i++) {
        okay[i] = true;
    }
    int nodes[(int)5e5];
    for (int i = 0; i < N; i++) {
        int index = 0;
        nodes[index] = i;
        bool upd;
        while (index != -1) {
            int cur = nodes[index];
            hasVisited[cur] = true;
            upd = false;
            while (!adj[cur].empty()) {
                pair<int,int> pr = adj[cur].back();
                adj[cur].pop_back();
                int j = pr.first;
                if (!okay[pr.second]) {
                    continue;
                }
                okay[pr.second] = false;
                if (hasVisited[j]) {
                    while (nodes[index] != j) {
                        hasVisited[nodes[index]] = false;
                        printf("%d ", nodes[index] + 1);
                        index--;
                    }
                    printf("%d\n", j + 1);
                } else {
                    nodes[++index] = j;
                }
                upd = true;
                break;
            }
            if (!upd) {
                index--;
            }
        }
    }
}
