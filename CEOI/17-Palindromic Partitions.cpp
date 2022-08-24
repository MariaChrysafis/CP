#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int64_t binPow (int64_t x, int64_t y) {
    int64_t ans = 1;
    int64_t res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y >>= 1;
    }
    return ans;
}
void solve() {
    string s;
    cin >> s;
    int64_t l = 0;
    int64_t r = 0;
    int64_t len = 0;
    int cnt = 0;
    for (int i = 0; i < s.length()/2; i++) {
        l += (binPow(10, len) * (s[i] - 'a')) % MOD;
        r = ((10 * r) % MOD + (s[s.length() - i -1 ] - 'a')) % MOD;
        l %= MOD, r %= MOD;
        len++;
        if (l == r) {
            cnt += 2;
            l = r = len = 0;
        } else if (s.length() % 2 == 0 && i == s.length()/2 - 1) {
            cnt++;
        }
    }
    if (s.length() % 2 == 1) {
        cnt++;
    }
    cout << cnt << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
