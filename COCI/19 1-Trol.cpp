#include <bits/stdc++.h>

using namespace std;
int64_t res (int64_t x) {
    return x % 9 + (x % 9 == 0) * 9;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--) {
        int64_t l, r;
        cin >> l >> r;
        if (l > r) {
            cout << 0 << '\n';
            continue;
        }
        int64_t base = 0;
        if (r - l <= 30) {
            for (int64_t i = l; i <= r; i++) {
                base += res(i);
            }
            cout << base << '\n';
            continue;
        }
        while (l % 9 != 0) {
            base += res(l);
            l++;
        }
        while (r % 9 != 8) {
            base += res(r);
            r--;
        }
        base += (r - l + 1) * 5ll;
        cout << base << '\n';
    }
    
}
