#include <bits/stdc++.h>
using namespace std;
set<int> s;
void rec (int x) {
    if (s.count(x)) {
        return;
    }
    s.insert(x);
    rec(x/2);
}
long long sum_subtriangles (int N, int K, vector<vector<int> > arr) {
    int n = N; 
    int k = K;
    rec(k);
    s.erase(0);
    int up[n][n][2];
    int down[n][n][2];
    for (int i = 0; i < n; i++) {
        while (arr[i].size() != n) {
            arr[i].push_back(0);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            up[i][j][0] = down[i][j][0] = arr[i][j];
        }        
    }
    int a = 0;
    for (int x: s) {
        a++, a %= 2;
        for (int i = x - 1; i < n; i++) {
            for (int j = 0; j + x - 1 <= i; j++) {
                if (x % 2 == 0) {
                    up[i][j][a] = max(max(up[i - x/2][j][!a], up[i][j][!a]), max(down[i - x/2 + 1][j + x/2 - 1][!a], up[i][j + x/2][!a]));
                } else {
                    up[i][j][a] = max(max(up[i][j][!a], down[i - x/2][j + x/2][!a]), max(up[i][j + x/2 + 1][!a], up[i - (x/2 + 1)][j][!a]));
                    up[i][j][a] = max(up[i][j][a], max(up[i - 1][j][!a], up[i][j + 1][!a]));
                }
            }
        }
        for (int i = 0; i + x - 1 < n; i++) {
            for (int j = x - 1; j <= i; j++) {
                if (x % 2 == 0) {
                    down[i][j][a] = max(max(down[i + x/2][j][!a], down[i][j][!a]), max(down[i][j - x/2][!a], up[i + (x/2 - 1)][j - (x/2 - 1)][!a]));
                } else {
                    down[i][j][a] = max(max(down[i][j - (x/2 + 1)][!a], down[i + (x/2 + 1)][j][!a]), max(down[i][j][!a], up[i + x/2][j - x/2][!a]));
                    down[i][j][a] = max(down[i][j][a], max(down[i + 1][j][!a], down[i][j - 1][!a]));
                }
            }
        }
    }
    long long ans = 0;
    for (int i = k - 1; i < n; i++) {
        for (int j = 0; j + k - 1 <= i; j++) {
            ans += up[i][j][a];
        }
    }
    return ans;
}
