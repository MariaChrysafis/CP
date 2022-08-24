#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    bool f[(1 << N)]; for (int i = 0; i < (1 << N); i++) f[i] = true;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        f[(1 << u) + (1 << v)] = false;
    }
    for (int i = 1; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            if ((i & (1 << j)) && !f[i ^ (1 << j)]) {
                f[i] = false;
            }
        }
    }
    int64_t dp[(1 << N)];
    dp[0] = 1;
    for (int i = 1; i < (1 << N); i++) {
        dp[i] = 0;
        for (int j = i; j; j = (j - 1) & i) {
            if (!f[j]) continue;
            if (__builtin_popcount(j) % 2) {
                dp[i] += dp[i ^ j];
            } else {
                dp[i] += MOD - dp[i ^ j];
            }
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
    }
    cout << (((dp[(1 << N) - 1] * M) % MOD) * (MOD + 1)/2) % MOD << '\n';
}
