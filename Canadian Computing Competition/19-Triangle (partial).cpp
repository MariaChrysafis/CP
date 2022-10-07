#include <bits/stdc++.h>
using namespace std;
set<int> s;
void rec (int x) {
    if (s.count(x)) {
        return;
    }
    s.insert(x);
    if (x == 0) {
        return;
    }
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
    freopen("inp.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<vector<vector<int> > > up, down;
    vector< vector<int> > arr;
    rec(k);
    s.erase(0);
    arr.resize(n);
    up.resize(n), down.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(n);
        up[i].resize(n), down[i].resize(n);
        for (int j = 0; j < n; j++) {
            up[i][j].resize(s.size());
            down[i][j].resize(s.size());
        }
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
        for (int j = 0; j <= i; j++) {
            cin >> arr[i][j];
        }
    }
    int ind[k + 1];
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
                    if (i - 1 >= 0 and j + 1 < n) {
                        up[i][j][ind[x]] = max(max(arr[i][j], arr[i - 1][j]), arr[i][j + 1]);
                    }
                    if (i + 1 < n and j - 1 >= 0) {
                        down[i][j][ind[x]] = max(max(arr[i][j], arr[i + 1][j]), arr[i][j - 1]);
                    }
                } else {
                    if (x % 2 == 0 and i - x + 1 >= 0 and j + x - 1 <= n - 1) {
                        up[i][j][ind[x]] = max(max(up[i - x/2][j][ind[x/2]], up[i][j][ind[x/2]]), max(down[i - x/2 + 1][j + x/2 - 1][ind[x/2]], up[i][j + x/2][ind[x/2]]));
                    } else if (x % 2 == 1 && i - x + 1 >= 0 && j + x - 1 <= n - 1){
                        up[i][j][ind[x]] = max(max(up[i][j][ind[x/2 + 1]], down[i - x/2][j + x/2][ind[x/2 + 1]]), max(up[i][j + x/2 + 1][ind[x/2]], up[i - (x/2 + 1)][j][ind[x/2]]));
                    }
                    if (x % 2 == 0 and i + x - 1 <= n - 1 and j - (x - 1) >= 0) {
                        down[i][j][ind[x]] = max(max(down[i + x/2][j][ind[x/2]], down[i][j][ind[x/2]]), max(down[i][j - x/2][ind[x/2]], up[i + (x/2 - 1)][j - (x/2 - 1)][ind[x/2]]));
                    } else if (x % 2 == 1 and i + x - 1 <= n - 1 and j - (x - 1) >= 0) {
                        down[i][j][ind[x]] = max(max(down[i][j - (x/2 + 1)][ind[x/2]], down[i + (x/2 + 1)][j][ind[x/2]]), max(down[i][j][ind[x/2 + 1]], up[i + x/2][j - x/2][ind[x/2 + 1]]));
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
