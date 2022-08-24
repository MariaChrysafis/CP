#include <bits/stdc++.h>

using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    string arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == '*') {
                bool fine = true;
                if (i != 0 && arr[i - 1][j] == '*') {
                    fine = false;
                }
                if (j != 0 && arr[i][j - 1] == '*') {
                    fine = false;
                }
                if (i != 0 && j != 0 && arr[i - 1][j - 1] == '*') {
                    fine = false;
                }
                ans += fine;
            }
        }
    }
    cout << ans;
}
