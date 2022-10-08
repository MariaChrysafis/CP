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
    int ind[k + 1];
    for (int i = 0; i <= k; i++) {
        ind[i] = -1;
    }
    int c = 0;
    for (int x: s) {
        ind[x] = c++;
        ind[x] %= 2;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            up[i][j][0] = down[i][j][0] = arr[i][j];
        }        
    }
    s.erase(1);
    for (int x: s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                    if (i - (x - 1) >= 0 and j + (x - 1) < n) {
                        if (x % 2 == 0) {
                            up[i][j][ind[x]] = max(max(up[i - x/2][j][ind[x/2]], up[i][j][ind[x/2]]), max(down[i - x/2 + 1][j + x/2 - 1][ind[x/2]], up[i][j + x/2][ind[x/2]]));
                        } else {
                            up[i][j][ind[x]] = max(max(up[i][j][ind[x/2]], down[i - x/2][j + x/2][ind[x/2]]), max(up[i][j + x/2 + 1][ind[x/2]], up[i - (x/2 + 1)][j][ind[x/2]]));
                            up[i][j][ind[x]] = max(up[i][j][ind[x]], max(up[i - 1][j][ind[x/2]], up[i][j + 1][ind[x/2]]));
                        }
                    }
                    if (i + (x - 1) < n and j - (x - 1) >= 0) {
                        if (x % 2 == 0) {
                            down[i][j][ind[x]] = max(max(down[i + x/2][j][ind[x/2]], down[i][j][ind[x/2]]), max(down[i][j - x/2][ind[x/2]], up[i + (x/2 - 1)][j - (x/2 - 1)][ind[x/2]]));
                        } else {
                            down[i][j][ind[x]] = max(max(down[i][j - (x/2 + 1)][ind[x/2]], down[i + (x/2 + 1)][j][ind[x/2]]), max(down[i][j][ind[x/2]], up[i + x/2][j - x/2][ind[x/2]]));
                            down[i][j][ind[x]] = max(down[i][j][ind[x]], max(down[i + 1][j][ind[x/2]], down[i][j - 1][ind[x/2]]));
                        }
                    }
            }
        }
    }
    long long ans = 0;
    for (int i = k - 1; i < n; i++) {
        for (int j = 0; j + k - 1 <= i; j++) {
            ans += up[i][j][ind[k]];
        }
    }
    return ans;
}
