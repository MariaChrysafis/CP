#include <bits/stdc++.h>
using namespace std;
int m;
vector<int> pos[59049];
void rec (int from, int to, int sz, int des_sz) {
    if (sz >= 1 && to/(int)pow(3, sz - 1) % 3 == 0) {
        if (sz >= 2 && (to/(int)pow(3, sz - 2)) % 3 == 0) {
            return;
        }
        if (sz >= 3 && (to/(int)pow(3, sz - 3)) % 3 == 0) {
            return;
        }
    }
    if (sz == des_sz) {
        pos[from].push_back(to);
        return;
    }
    if ((from/(int)pow(3, sz)) % 3 == 0) {
        rec(from, to + pow(3, sz) * 1, sz + 1, des_sz);
    } else if (from/(int)pow(3, sz) % 3 == 1) {
        rec(from, to + pow(3, sz) * 2, sz + 1, des_sz);
    } else if (from/(int)pow(3, sz) % 3 == 2) {
        rec(from, to + pow(3, sz) * 0, sz + 1, des_sz);
        rec(from, to + pow(3, sz) * 2, sz + 1, des_sz);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n >> m;
    for (int i = 0; i < pow(3, m); i++) {
        rec(i, 0, 0, m);
    }
    int msk[(int)pow(3, m)], cst[(int)pow(3, m)];
    for (int i = 0; i < pow(3, m); i++) {
        msk[i] = 0, cst[i] = 0;
        int x = i;
        for (int j = 0; j < m; j++) {
            if (x % 3 == 0) {
                msk[i] += (1 << j), cst[i]++;
            }
            x /= 3;
        }
    }
    int dp[n + 1][(int)pow(3, m)];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < (int)pow(3, m); j++) {
            dp[i][j] = 0;
        }
    }
    int myMax = 0;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        int mask = 0;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == 'H') {
                mask += (1 << j);
            }
        }
        for (int from = 0; from < pow(3, m); from++) {
            for (int to: pos[from]) {
                if (!(mask & msk[to])) {
                    dp[i][to] = max(dp[i][to], dp[i - 1][from] + cst[to]);
                }
            }
        }
    }
    for (int from = 0; from < pow(3, m); from++) {
        myMax = max(myMax, dp[n][from]);
    }
    cout << myMax;
}
