#include <bits/stdc++.h>
using namespace std;
__int128 read() {
    __int128 x = 0;
    char ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
void print(__int128 x) {
    if (x/10) print(x / 10);
    putchar(x % 10 + '0');
}
__int128 arithmetic (__int128 a, __int128 n, __int128 m) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        return (a * arithmetic(a, n - 1, m) + 1) % m;
    }
    return ((a + 1) * arithmetic((a * a) % m, n/2, m)) % m;
}
__int128 binPow (__int128 x, __int128 y, __int128 m) {
    __int128 res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= m;
        }
        res *= res, res %= m, y /= 2;
    }
    return ans;
}
int main() {
    __int128 m = read(), a = read(), c = read(), x0 = read(), n = read(), g = read();
    __int128 ans = ((arithmetic(a, n - 1, m) * c + binPow(a, n, m) * x0) % m) % g;
    int64_t res = ans;
    cout << res << '\n';
}
