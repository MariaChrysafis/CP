#include <bits/stdc++.h>

using namespace std;
const int MOD = 1000000007;
int64_t add (int64_t x, int64_t y) {
    return (x + y) % MOD;
}
int64_t mult (int64_t x, int64_t y) {
    return (x * y) % MOD;
}
int64_t sub (int64_t x, int64_t y) {
    return (x - y + MOD) % MOD;
}
void solve() {
    int N; cin >> N;
    int64_t A[N], B[N];
    int64_t tot_a = 0, tot_b = 0, tot = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        tot = add(tot, add(mult(A[i], A[i]), mult(B[i], B[i])));
        tot_a = add(tot_a, A[i]), tot_b = add(tot_b, B[i]);
    }
    int Q;
    cin >> Q;
    int64_t ans = 0;
    while (Q--) {
        int64_t x, y; 
        cin >> x >> y;
        int64_t a = tot;
        a = add(a, mult(N, add(mult(x, x), mult(y, y))));
        ans = add(ans,sub(sub(a, mult(tot_a, mult(2ll, x))), mult(tot_b, mult(2ll, y))));
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}
