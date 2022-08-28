#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 998244353;

int64_t binPow (int x, int y) {
    int64_t res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD, y /= 2;
    }
    return ans;
}

int inv (int x) {
    return binPow(x, MOD - 2);
} 

int mult (int x, int y) {
    return ((int64_t) x * (int64_t) y) % MOD;
}

int frac (int x, int y) {
    return mult(x, inv(y));
}

vector<int64_t> fact;

int64_t combo (int x, int y) {
    if (x < y) return 0;
    return frac(fact[x], mult(fact[y], fact[x - y]));
}

struct Matrix {
    int64_t arr[2][2];
};

Matrix mult (Matrix x, Matrix y) {
    Matrix res;
    res.arr[0][0] = res.arr[0][1] = res.arr[1][0] = res.arr[1][1] = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res.arr[i][j] += x.arr[i][k] * y.arr[k][j];
                res.arr[i][j] %= MOD;
            }
        }
    }
    return res;
}

Matrix exp (Matrix x, int64_t powr) {
    Matrix res = x;
    Matrix ans; ans.arr[0][0] = ans.arr[1][1] = 1, ans.arr[0][1] = ans.arr[1][0] = 0;        
    while (powr > 0) {
        if (powr & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res), powr /= 2;
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    const int MX = 2e4;
    for (int i = 0; i < MX; i++) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    int64_t N, D;
    cin >> N >> D;
    int64_t ans = 2;
    Matrix orig;
    orig.arr[0][0] = D - 1, orig.arr[0][1] = orig.arr[1][0] = 1, orig.arr[1][1] = 0;
    orig = exp(orig, N );
    ans += (orig.arr[0][0] + orig.arr[1][1]) % MOD, ans %= MOD;
    for (int W = 2; W <= D; W++) {
        Matrix dum;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                dum.arr[i][j] = combo(D - 1, W - i - j);
            }
        }
        dum = exp(dum, N);
        ans += (dum.arr[0][0] + dum.arr[1][1]) % MOD, ans %= MOD;
    }
    cout << ans;
}
