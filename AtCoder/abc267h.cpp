#include <bits/stdc++.h>
#include <atcoder/convolution.hpp>
#include <atcoder/modint.hpp>
 
using namespace std;
using namespace atcoder;
using mint = modint998244353;
 
const int MOD = 998244353;
vector<mint> fact;
mint binPow (mint x, int y) {
    mint res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
           ans *= res;
        }
        res *= res, y /= 2;
    }
    return ans;
}
mint inv (mint x) {
    return binPow(x, MOD - 2);
}
mint combo (int x, int y) {
    return fact[x] * inv(fact[y]) * inv(fact[x - y]);
}
vector<mint> sum (vector<mint> a, vector<mint> b) {
    vector<mint> v(max(a.size(), b.size()));
    for (int i = 0; i < v.size(); i++) {
        v[i] = 0;
        if (i < a.size()) {
            v[i] += a[i];
        }
        if (i < b.size()) {
            v[i] += b[i];
        }
    }
    return v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while (fact.size() != 2e5 + 1) {
        fact.push_back(fact.back() * (mint)fact.size());
    }
    mint ms;
    int cnt[11];
    for (int i = 1; i <= 10; i++) {
        cnt[i] = 0;
    }
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<vector<mint> > vec0, vec1;
    for (int i = 1; i <= 10; i++) {
        if (!cnt[i]) {
            continue;
        }
        vector<mint> v[2];
        v[0].assign(cnt[i] * i + 1, 0);
        v[1].assign(cnt[i] * i + 1, 0);
        for (int j = 0; j <= cnt[i]; j++) {
            v[j % 2][j * i] = combo(cnt[i], j);
        }
        vec1.push_back(v[1]);
        vec0.push_back(v[0]);
    }
    vector<mint> a0, a1;
    a0.push_back(1), a1.push_back(0);
    for (int i = 0; i < vec1.size(); i++) {
        vector<mint> new_a0, new_a1;
        new_a0 = sum(convolution(vec1[i], a1), convolution(a0, vec0[i]));
        new_a1 = sum(convolution(vec1[i], a0), convolution(a1, vec0[i]));
        a0 = new_a0, a1 = new_a1;
    }
    if (a1.size() <= M) {
        cout << 0;
    } else {
        cout << a1[M].val() << '\n';
    }
}
