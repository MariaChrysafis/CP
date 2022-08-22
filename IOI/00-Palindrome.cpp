#include <bits/stdc++.h>
using namespace std;
int main () {
    string s;
    int n;
    cin >> n >> s;
    n = s.size();
    int dp[3][n];
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n; i++) {
            int j = i + len - 1;
            if (j >= n) continue;
            if (len == 1) {
                dp[len][j] = 0; 
            } else if (len == 2) {
                dp[len][j] = (s[i] != s[j]);
            } else {
                dp[len % 3][j] = INT_MAX;
                dp[len % 3][j] = min(dp[len % 3][j], dp[(len - 1) % 3][j] + 1);
                dp[len % 3][j] = min(dp[len % 3][j], dp[(len - 1) % 3][j - 1] + 1);
                dp[len % 3][j] = min(dp[len % 3][j], dp[(len - 2) % 3][j - 1] + (s[i] != s[j]) * 2);
            }
        }
    }
    cout << dp[n % 3][n - 1];
}
