#include <bits/stdc++.h>
using namespace std;
const int M = 11380;
struct modint {
    modint() : n(0) {}
    template <class T> modint(T n) { n %= M; if (n < 0) n += M; this->n = n; }
 
    modint & operator+=(const modint &r) { n += r.n; if (n >= M) n -= M; return *this; }
    modint & operator-=(const modint &r) { n -= r.n; if (n < 0) n += M; return *this; }
    modint & operator*=(const modint &r) { n = (int) ((long long) n * r.n % M); return *this; }
 
    modint & operator--() { if (--n == -1) n = M - 1; return *this; }
    modint & operator++() { if (++n == M) n = 0; return *this; }
    modint operator--(int) { modint t = *this; --*this; return t; }
    modint operator++(int) { modint t = *this; ++*this; return t; }
 
    modint operator-() const { return 0 - *this; }
    modint operator+() const { return *this; }
 
    modint pow(long long k = M - 2) const {
        modint f = *this, p = 1;
        while (k > 0) {
            if (k % 2 == 1) f *= p;
            p *= p, k /= 2;
        }
        return f;
    }
 
    int mod() const { return M; }
 
    friend modint operator+(modint l, const modint &r) { return l += r; }
    friend modint operator-(modint l, const modint &r) { return l -= r; }
    friend modint operator*(modint l, const modint &r) { return l *= r; }
    
    friend bool operator==(const modint &l, const modint &r) { return l.n == r.n; }
    friend bool operator!=(const modint &l, const modint &r) { return l.n != r.n; }
 
    friend ostream & operator<<(ostream &out, const modint &r) { return out << r.n; }
 
    int n;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int L1, L2, L3, D;
    cin >> L1 >> L2 >> L3 >> D;
    swap(L1, L3);
    modint dp[2][L1 + 1][L2 + 1][L2 + 1][L3 + 1][L3 + 1][D + 2];
    for (int o1 = 0; o1 <= 1; o1++) {
        for (int c1 = 0; c1 <= L1; c1++) {
            for (int o2 = 0; o2 <= L2; o2++) {
                for (int c2 = 0; c2 <= L2; c2++) {
                    for (int o3 = 0; o3 <= L3; o3++) {
                        for (int c3 = 0; c3 <= L3; c3++) {
                            for (int d = 0; d <= D; d++) {
                                dp[o1][c1][o2][c2][o3][c3][d] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0][0][0] = 1;
    for (int o1 = 0; o1 <= L1; o1++) {
        for (int c1 = 0; c1 <= L1; c1++) {
            for (int o2 = 0; o2 <= L2; o2++) {
                for (int c2 = 0; c2 <= L2; c2++) {
                    for (int o3 = 0; o3 <= L3; o3++) {
                        for (int c3 = 0; c3 <= L3; c3++) {
                            for (int d = 0; d <= D; d++) {
                                dp[(o1 + 1) % 2][c1][o2][c2][o3][c3][d] = 0;
                            }
                        }
                    }
                }
            }
        }
        for (int c1 = 0; c1 <= o1; c1++) {
            for (int o2 = 0; o2 <= L2; o2++) {
                for (int c2 = 0; c2 <= o2; c2++) {
                    for (int o3 = 0; o3 <= L3; o3++) {
                        for (int c3 = 0; c3 <= o3; c3++) {
                            int cur_depth = o1 - c1 + o2 - c2 + o3 - c3;
                            if (cur_depth > D) continue;
                            for (int d = 0; d <= D; d++) {
                                bool p1, p2, p3;
                                if (c1 != o1) {
                                    p1 = true, p2 = false, p3 = false;
                                } else if (c2 != o2) {
                                    p1 = true, p2 = true, p3 = false;
                                } else {
                                    p1 = true, p2 = true, p3 = true;
                                }
                                assert(max(d, cur_depth + 1) <= D + 1);
                                if (p1) {
                                    if (o1 + 1 <= L1) dp[(o1 + 1) % 2][c1][o2][c2][o3][c3][max(d, cur_depth + 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                    if (c1 + 1 <= L1) dp[o1 % 2][c1 + 1][o2][c2][o3][c3][max(d, cur_depth - 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                }
                                if (p2) {
                                    if (o2 + 1 <= L2) dp[o1 % 2][c1][o2 + 1][c2][o3][c3][max(d, cur_depth + 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                    if (c2 + 1 <= L2) dp[o1 % 2][c1][o2][c2 + 1][o3][c3][max(d, cur_depth - 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                }
                                if (p3) {
                                    if (o3 + 1 <= L3) dp[o1 % 2][c1][o2][c2][o3 + 1][c3][max(d, cur_depth + 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                    if (c3 + 1 <= L3) dp[o1 % 2][c1][o2][c2][o3][c3 + 1][max(d, cur_depth - 1)] += dp[o1 % 2][c1][o2][c2][o3][c3][d];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << dp[L1 % 2][L1][L2][L2][L3][L3][D].n;
}
