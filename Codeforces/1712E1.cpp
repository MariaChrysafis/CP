#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>
using namespace std;
vector<int> mu;
vector<int> lpf;
vector<vector<int> > factors;
void fill_mobius () {
    mu.resize(2e5 + 10), lpf.assign(2e5 + 10, 0), factors.resize(2e5 + 10);
    for (int i = 2; i < lpf.size(); i++) {
        if (!lpf[i]) {
            for (int j = i; j < lpf.size(); j += i) {
                if (!lpf[j]) {
                    lpf[j] = i;
                }
            }
        }
    }
    for (int i = 1; i < mu.size(); i++) {
        for (int j = i; j < mu.size(); j += i) {
            factors[j].push_back(i);
        }
    }
    mu[1] = 1;
    for (int i = 2; i < mu.size(); i++) {
        if (lpf[i/lpf[i]] == lpf[i]) {
            mu[i] = 0;
        } else {
            mu[i] = -1 * mu[i/lpf[i]];
        }
    }
}
int64_t gcd (int64_t x, int64_t y) {
    if (!x || !y) {
        return max(x, y);
    }
    return gcd(max(x, y) % min(x, y), min(x, y));
}
int64_t lcm (int64_t x, int64_t y) {
    return x * y/gcd(x, y);
}
int64_t g (int64_t l, int64_t r) {
    assert(l != 0);
    int64_t ans = 0;
    for (int i = 1; i <= r; i++) {
        ans += (3 * i >= l and 3 * i <= r and 6 * i >= l and 6 * i <= r);
        ans += (6 * i >= l and 6 * i <= r and 15 * i >= l and 15 * i <= r);
    }
    set<pair<pair<int,int>,int> > s;
    for (int i = l; i <= r; i++) {
        if (i == 1) {
            continue;
        }
        for (int j: factors[i]) {
            if (j < l || j > r || j == i || j == 1) {
                continue;
            }
            for (int k: factors[i]) {
                if (k < l || k > r || j <= k || i == k || k == 1) {
                    continue;
                }
                ans += (lcm(k, i) < i + j + k);
            }
        }
    }
    if (l == 1) {
        for (int x = l; x <= r; x++) {
            for (int y: factors[x]) {
                if (lcm(x, y) < x + y + 1 and y < x and r >= 1 and x != 1 and y != 1) {
                    ans++;
                }
            }
        }
    }
    return ans;
}
int64_t f (int64_t l, int64_t r) {
    return ((r - l + 1) * (r - l) * (r - l - 1))/6 - g(l, r);
}
int main() {
    fill_mobius();
    int t;
    cin >> t;
    while (t--) {
        int l,r ;
        cin >> l >> r;
        cout << f(l, r) << '\n';
    }
    return 0;
}
