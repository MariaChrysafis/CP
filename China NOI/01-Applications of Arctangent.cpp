#include <bits/stdc++.h>
using namespace std;
bool pq (int64_t x) {
    return ((int64_t) sqrt(x) * (int64_t)sqrt(x) == x);
}
pair<int64_t,int64_t> quadratic (int64_t a, int64_t b, int64_t c) {
    int64_t disc = b * b - 4 * a * c;
    if (disc < 0 || !pq(disc)) return make_pair(INT_MAX, INT_MAX);
    int64_t res = -b + disc;
    if (res % 2 != 0) return make_pair(INT_MAX, INT_MAX);
    return make_pair((-b + disc)/2, (-b-disc)/2);
}
int main() {
    int64_t a;
    cin >> a;
    for (int64_t tot = 1; tot >= 0; tot++) {
        pair<int,int> p = quadratic(1, -1 * tot, a * tot + 1);
        if (p == make_pair(INT_MAX, INT_MAX)) continue;
        cout << tot;
        exit(0);
    }
}
