#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int M, Q; cin >> M >> Q;
    vector<int> p(M);
    for (int i = 0; i < M; i++) {
        cin >> p[i];
    }
    int mx = 10000001;
    int res[mx];
    int lpf[mx];
    for (int i = 0; i < mx; i++) {
        lpf[i] = -1;
    }
    for (int j = 0; j < p.size(); j++) {
        for (int i = p[j]; i < mx; i += p[j]) {
            lpf[i] = j;
        }
    }
    int dp[M];
    priority_queue<int, vector<int>, greater<int> > ms;
    for (int i = 0; i < M; i++) {
        dp[i] = 0;
        ms.push(dp[i]);
    }
    for (int i = 1; i < mx; i++) {
        int ans = 1e9;
        if (lpf[i] == -1) {
            ans = ms.top() + 1;
        } else {
            vector<int> invalid;
            int x = i;
            while (lpf[x] != -1) {
                if (dp[lpf[x]] == ms.top()) {
                    invalid.push_back(lpf[x]);
                    ms.pop();
                }
                int a = p[lpf[x]];
                while (x % a == 0) {
                    x /= a;
                }
            }
            if (!ms.empty()) {
                ans = ms.top() + 1;
            }
            for (int j: invalid) {
                dp[j] = ans;
                ms.push(dp[j]);
            }
        }
        res[i] = ans;
    }
    while (Q--) {
        int x;
        cin >> x;
        if (res[x] >= (int)1e9) {
            cout << "oo\n";
        } else {
            cout << res[x] << '\n';
        }
    }
}
