#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
unsigned int gcd(unsigned int u, unsigned int v) {
    int shift;
    if (u == 0)
        return v;
    if (v == 0)
        return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        unsigned m;
        v >>= __builtin_ctz(v);
        v -= u;
        m = (int)v >> 31;
        u += v & m;
        v = (v + m) ^ m;
    } while (v != 0);
    return u << shift;
}
pair<ll,ll> frac (pair<ll,ll> p) {
    assert(p.first != 0 || p.second != 0);
    if (p.first == 0) return {0, 1};
    if (p.second == 0) return {1, 0};
    if (p.first < 0 && p.second < 0) p.first = -p.first, p.second = -p.second;
    ll g = gcd(abs(p.first), abs(p.second));
    return make_pair(p.first/g, p.second/g);
}
vector<pair<ll,ll>> points;
set<pair<ll,ll>> s;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    points.resize(n);
    for (int i = 0; i < points.size(); i++) {
        cin >> points[i].first >> points[i].second;
        s.insert(points[i]);
    }
    double myMax = 0;
    for (int i = 0; i < n; i++) {
        map<pair<ll,ll>,vector<pair<ll,ll>>> cnt;
        for (auto& p: points) {
            if (p == points[i]) {
                continue;
            }
            cnt[frac(make_pair(p.first - points[i].first, p.second - points[i].second))].push_back(p);
        }
        vector<pair<pair<ll,ll>,pair<ll,ll>>> tot;
        for (auto& p: cnt) {
            if (p.first.second >= 0) {
                tot.emplace_back(make_pair(p.first, make_pair(-p.first.second, p.first.first)));
            }
        }
        for (auto& p: tot) {
            for (auto& p1: cnt[p.second]) {
                for (auto& p2: cnt[p.first]) {
                    if (s.count(make_pair(p1.first + p2.first - points[i].first, p1.second + p2.second - points[i].second))) {
                        ll d1 = (p1.first - points[i].first) * (p1.first - points[i].first) + (p1.second - points[i].second) * (p1.second - points[i].second);
                        ll d2 = (p2.first - points[i].first) * (p2.first - points[i].first) + (p2.second - points[i].second) * (p2.second - points[i].second);
                        myMax = max(myMax, sqrt(d1) * sqrt(d2));
                    }
                }
            }
        }
    }
    cout << setprecision(30) << floor(myMax);
 
 
}
