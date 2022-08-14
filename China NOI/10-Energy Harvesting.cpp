#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n, m;
    cin >> n >> m;
    int64_t ans = 0;
    int64_t cnt[max(n, m) + 1];
    cnt[0] = 0;
    for (int i = max(n, m); i >= 1; i--) {
        cnt[i] = floor(n/i) * floor(m/i);
        for (int j = 2 * i; j <= max(n, m); j += i) {
            if (j % i == 0) {
                cnt[i] -= cnt[j];
            }
        }
        ans += i * cnt[i];
    }
    cout << ans * 2 - n * m;
}
