#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int64_t adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 1e17;
        }
    }
    for (int i = 0; i < m; i++) {
        int64_t a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        adj[a][b] = min(adj[a][b], t);
    }
    int64_t cur[n][n], prev[n][n];
    bool change[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cur[i][j] = 1e17, prev[i][j] = 1e17;
            change[i][j] = true;
        }
        prev[i][i] = cur[i][i] = 0;
    }
    int k; cin >> k;
    k = min(k, (n * n - n)/2);
    for (int d = 1; d <= k; d++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < n; l++) {
                    cur[i][j] = min(cur[i][j], prev[i][l] + adj[l][j]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                prev[i][j] = cur[i][j];
            }
        }
    }   
    int q; cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (cur[x][y] == 1e17) {
            cur[x][y] = -1;
        }
        cout << cur[x][y] << '\n';
    }
}
