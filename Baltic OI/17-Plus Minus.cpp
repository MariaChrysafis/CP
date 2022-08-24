#include <bits/stdc++.h>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int MOD = 1e9 + 7;
int64_t binPow (int64_t x, int y) {
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t solve (int N, int M, vector<pair<pair<int,int>, bool>> points) {
    map<int,int> myMap;
    for (auto& p: points) {
        if (myMap.count(p.first.first) && myMap[p.first.first] != ((p.first.second % 2) ^ p.second)) {
            return 0;
        }
        myMap[p.first.first] = ((p.first.second % 2) ^ p.second);
    }
    return binPow(2, N - myMap.size());
}
int64_t overcount (vector<pair<pair<int,int>, bool>> points) {
    if (points.empty()) return 2;
    bool f[2];
    f[0] = f[1] = true;
    for (auto& p: points) {
        f[(p.first.first % 2) ^ (p.first.second % 2) ^ p.second] = false;
    }
    return f[0] + f[1];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K; cin >> N >> M >> K;
    vector<pair<pair<int,int>, bool>> points(K);
    for (int i = 0; i < K; i++) {
        char c; cin >> c;
        cin >> points[i].first.first >> points[i].first.second;
        points[i].second = (c == '+');
    }
    int64_t ans = 0;
    ans += solve(N, M, points);
    for (int i = 0; i < K; i++) {
        swap(points[i].first.first, points[i].first.second);
    }
    ans += solve(M, N, points);
    cout << (ans - overcount(points) + MOD) % MOD;
 
}
