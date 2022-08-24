#include <bits/stdc++.h>
 
using namespace std;
const int MOD = 1e9;
class Matrix {
public:
    vector<vector<int64_t>> v;
    void print () {
        for (int i = 0; i < v.size(); i++) {
            for (int j: v[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    }
    Matrix operator* (Matrix m1) const {
        Matrix ans(v);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ans.v[i][j] = 0;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    ans.v[i][j] += (v[i][k] * m1.v[k][j]) % MOD;
                    ans.v[i][j] %= MOD;
                }
            }
        }
        return ans;
    }
    Matrix identity (int64_t n) {
        vector<vector<int64_t>> v(n);
        for (int i = 0; i < n; i++) {
            v[i].resize(n);
            for (int j = 0; j < n; j++) {
                v[i][j] = (i == j);
            }
        }
        return Matrix(v);
    }
    Matrix operator^ (int64_t x) {
        Matrix ans = identity(v.size());
        Matrix res = *this;
        while (x > 0) {
            if (x & 1) {
                ans = ans * res;
            }
            res = res * res;
            x /= 2;
        }
        return ans;
    }
    Matrix (vector<vector<int64_t>> v) {
        this->v = v;
    }
};
int64_t binPow (int64_t x, int y) {
    int64_t ans = 1;
    int64_t res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res; res %= MOD;
        y >>= 1;
    }
    return ans;
}
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Matrix fib = Matrix({{0, 0, 1}, {0, 0, 2}, {2, 1, 4}});
    int64_t n;
    cin >> n;
    fib = fib^(n - 2);
    vector<int64_t> v;
    v.resize(3);
    for (int i = 0; i < 3; i++) {
        v[i] = 2 * fib.v[0][i] + fib.v[2][i];
    }
    cout << (2 * v[1] + v[2]) % MOD;
 
 
}
