#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>
using namespace std;
struct SparseTable {
    vector<vector<int> > dp;
    int query (int l, int r) {
        int x = log2(r - l + 1);
        return min(dp[l][x], dp[r - (1 << x) + 1][x]);
    }
    SparseTable (vector<int> arr) {
        dp.resize(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            dp[i].resize(32);
            dp[i][0] = arr[i];
        }
        for (int j = 1; j < dp[0].size(); j++) {
            for (int i = 0; i < arr.size(); i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)dp.size() - 1)][j - 1]);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            arr[i] -= (i + 1);
        }
        SparseTable st(arr);
        int64_t c = 0;
        for (int i = 0; i < n; i++) {
            int l = i;
            int r = n - 1;
            while (l != r) {
                int m = (l + r + 1)/2;
                if (st.query(i, m) >= -i) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            c += l - i + 1;
        }
        cout << c << '\n';
    }
}
