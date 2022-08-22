#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int V, P;
    cin >> V >> P;
    int villages[V];
    for (int i = 0; i < V; i++) {
        cin >> villages[i];
    }
    sort(villages, villages + V);
    int dp[V + 1][P + 1], dp_ind[V + 1][P + 1]; int prev[V + 1][P + 1];
    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= P; j++) {
            dp[i][j] = 1e8;
        }
    }
    const int MAX_POS = 1e4 + 1;
    int cst[MAX_POS][V + 1]; //minimum cost to cover villages 0...j using only one post office
    for (int j = 0; j < MAX_POS; j++) {
        cst[j][0] = 0;        
    }
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < MAX_POS; j++) {
            cst[j][i] = cst[j][i - 1] + abs(villages[i - 1] - j);
        }
    }
    int best[V + 1][V + 1], best_ind[V + 1][V + 1]; //minimum cost to cover villages i...j using only one post office
    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= V; j++) {
            best[i][j] = INT_MAX;
            for (int pos = (i ? villages[i - 1] : 0); pos <= (j ? villages[j - 1] : 0); pos++) {
                if (cst[pos][j] - cst[pos][i] < best[i][j]) {
                    best[i][j] = cst[pos][j] - cst[pos][i];
                    best_ind[i][j] = pos;
                }
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= V; i++) { //# of villages accounted for
        for (int p = 1; p <= P; p++) { //# of post offices
            for (int j = i + 1; j <= V; j++) {
                if (dp[i][p - 1] + best[i][j] < dp[j][p]) {
                    dp[j][p] = dp[i][p - 1] + best[i][j];
                    dp_ind[j][p] = best_ind[i][j];
                    prev[j][p] = i;
                }
            }
        }
    }
    cout << dp[V][P] << '\n';
    int x = V, y = P;
    while (y) {
        int p = prev[x][y];
        cout << dp_ind[x][y] << ' ';
        x = p, y--;
    }
}
