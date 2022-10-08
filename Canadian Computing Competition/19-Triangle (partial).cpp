#include <bits/stdc++.h>
using namespace std;
set<int> s;
void rec (int x) {
    if (s.count(x)) {
        return;
    }
    s.insert(x);
    if (x % 2 == 0) {
        rec(x/2);
    } else {
        rec(x/2);
        rec(x/2 + 1);
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int arr[n][n];
    rec(k);
    s.erase(0);
    int up[n][n][s.size()];
    int down[n][n][s.size()];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
        for (int j = 0; j <= i; j++) {
            cin >> arr[i][j];
        }
    }
    int ind[k + 1];
    for (int i = 0; i <= k; i++) {
        ind[i] = -1;
    }
    int c = 0;
    for (int x: s) {
        ind[x] = c++;
    }
    for (int x: s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (x == 1) {
                    up[i][j][ind[x]] = down[i][j][ind[x]] = arr[i][j];
                } else if (x == 2) {
                    up[i][j][ind[x]] = down[i][j][ind[x]] = arr[i][j];
                    if (i - 1 >= 0) {
                        up[i][j][ind[x]] = max(up[i][j][ind[x]], arr[i - 1][j]);
                    }
                    if (j + 1 < n) {
                        up[i][j][ind[x]] = max(up[i][j][ind[x]], arr[i][j + 1]);
                    }
                    if (i + 1 < n) {
                        down[i][j][ind[x]] = max(down[i][j][ind[x]], arr[i + 1][j]);
                    }
                    if (j - 1 >= 0) {
                        down[i][j][ind[x]] = max(down[i][j][ind[x]], arr[i][j - 1]);
                    }
                } else {
                    if (i - x/2 >= 0 and j + x/2 + 1 < n) {
                        if (x % 2 == 0) {
                            up[i][j][ind[x]] = max(max(up[i - x/2][j][ind[x/2]], up[i][j][ind[x/2]]), max(down[i - x/2 + 1][j + x/2 - 1][ind[x/2]], up[i][j + x/2][ind[x/2]]));
                        } else {
                            up[i][j][ind[x]] = max(max(up[i][j][ind[x/2]], down[i - x/2][j + x/2][ind[x/2]]), max(up[i][j + x/2 + 1][ind[x/2]], up[i - (x/2 + 1)][j][ind[x/2]]));
                            up[i][j][ind[x]] = max(up[i][j][ind[x]], max(up[i - 1][j][ind[x/2]], up[i][j + 1][ind[x/2]]));
                        }
                    }
                    if (i + x/2 + 1 < n and j + x/2 >= 0) {
                        if (x % 2 == 0) {
                            down[i][j][ind[x]] = max(max(down[i + x/2][j][ind[x/2]], down[i][j][ind[x/2]]), max(down[i][j - x/2][ind[x/2]], up[i + (x/2 - 1)][j - (x/2 - 1)][ind[x/2]]));
                        } else {
                            down[i][j][ind[x]] = max(max(down[i][j - (x/2 + 1)][ind[x/2]], down[i + (x/2 + 1)][j][ind[x/2]]), max(down[i][j][ind[x/2 + 1]], up[i + x/2][j - x/2][ind[x/2 + 1]]));
                        }
                    }
                }
            }
        }
    }
    int64_t ans = 0;
    for (int i = k - 1; i < n; i++) {
        for (int j = 0; j + k - 1 <= i; j++) {
            ans += up[i][j][ind[k]];
        }
    }
    cout << ans;


}
