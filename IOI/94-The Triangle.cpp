#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    int dp[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            int x; cin >> x;
            if (i == 0 && j == 0) {
                dp[i][j] = x;
                continue;
            }
            assert(i >= 1);
            dp[i][j] = 0;
            if (i - 1 >= j) dp[i][j] = max(dp[i][j], dp[i - 1][j] + x);
            if (i - 1 >= j - 1 && j >= 1) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + x);
        }
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        myMax = max(myMax, dp[n - 1][i]);
    }
    cout << myMax;
}
