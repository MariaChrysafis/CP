#include <bits/stdc++.h>
using namespace std;
int dp[50][50][50][50];
int sm[50][50][50][50];
int solve (int x1, int x2, int y1, int y2) {
    if (x1 == x2 && y1 == y2) return 0;
    if (dp[x1][x2][y1][y2] != INT_MAX) {
        return dp[x1][x2][y1][y2];
    }
    for (int y = y1; y + 1 <= y2; y++) {
        dp[x1][x2][y1][y2] = min(dp[x1][x2][y1][y2], solve(x1,x2,y1,y) + solve(x1,x2,y+1,y2) + sm[x1][x2][y1][y2]);        
    }
    for (int x = x1; x + 1 <= x2; x++) {
        dp[x1][x2][y1][y2] = min(dp[x1][x2][y1][y2], solve(x1,x,y1,y2) + solve(x+1,x2,y1,y2) + sm[x1][x2][y1][y2]);
    }
    return dp[x1][x2][y1][y2];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    int arr[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
    for (int x1 = 0; x1 < N; x1++) {
        for (int x2 = x1; x2 < N; x2++) {
            for (int y1 = 0; y1 < M; y1++) {
                int res = 0;
                for (int y2 = y1; y2 < M; y2++) {
                    res += arr[x2][y2];
                    if (x1 == x2 && y1 == y2) {
                        sm[x1][x2][y1][y2] = arr[x1][y1];
                    } else if (x1 == x2) {
                        sm[x1][x2][y1][y2] = sm[x1][x2][y1][y2 - 1] + arr[x1][y2];
                    } else {
                        sm[x1][x2][y1][y2] = res + sm[x1][x2 - 1][y1][y2];
                    }
                    dp[x1][x2][y1][y2] = INT_MAX;
                }
            }
        }
    }
    cout << solve(0, N - 1, 0, M - 1) << '\n';
}
