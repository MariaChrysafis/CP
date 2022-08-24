#include <bits/stdc++.h>
#include <map>
 
using namespace std;
int64_t dp[50050][32][5][5];
int K, N, M, O;
vector<vector<int64_t>> f (int in1, int in2) {
    vector<vector<int64_t>> cur(K);
    for (int i = 0; i < K; i++) {
        cur[i].assign(K, INT_MAX);
        cur[i][i] = 0;
    }
    int dif = abs(in1 - in2);
    while (dif > 0) {
        vector<vector<int64_t>> new_cur = cur;
        for (int i = 0; i < K; i++) {
            new_cur[i].assign(K, INT_MAX);
        }
        int lg2 = log2(dif);
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                for (int k = 0; k < K; k++) {
                     new_cur[i][j] = min(new_cur[i][j], cur[i][k] + dp[in1][lg2][k][j]);
                }
            }
        }
        dif -= (1 << lg2);
        in1 += (1 << lg2);
        cur = new_cur;
    }
    return cur;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> K >> N >> M >> O;
    N++;
    while (N % K != K - 1) {
        N++;
    }
    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < N/K; i++) {
            for (int x = 0; x < K; x++) {
                for (int y = 0; y < K; y++) {
                    dp[i][j][x][y] = INT_MAX;
                }
            }
        }
    }
    while (M--) {
        int64_t a, b, w;
        cin >> a >> b >> w;
        dp[a/K][0][a % K][b % K] = min(w, dp[a/K][0][a % K][b % K]);
    }
    for (int j = 1; j < 32; j++) {
        for (int i = 0; i < N/K; i++) {
            for (int x = 0; x < K; x++) {
                for (int y = 0; y < K; y++) {
                    for (int z = 0; z < K; z++) {
                        if (i + (1 << (j - 1)) < N/K)
                        dp[i][j][x][y] = min(dp[i][j][x][y], dp[i][j - 1][x][z] + dp[i + (1 << (j - 1))][j - 1][z][y]);
                    }
                }
            }
        }
    }
    while (O--) {
        int a, b;
        cin >> a >> b;
        if (a/K == b/K) {
            cout << "-1\n";
            continue;
        }
        vector<vector<int64_t>> vec = f(a/K, b/K);
        if (vec[a % K][b % K] == INT_MAX) {
            cout << "-1\n";
            continue;
        }
        cout << vec[a % K][b % K] << '\n';
    }
}
