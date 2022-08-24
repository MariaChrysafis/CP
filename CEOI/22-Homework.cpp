#include <bits/stdc++.h>
using namespace std;
vector<int> pref_q;
vector<int> pref_p;
map<int,set<int> > myMap;
string s;
pair<int,int> solve (int l, int r) {
    if (r == l) {
        return make_pair(1, 1);
    }
    pair<int,int> p;
    int i = *myMap[1 + pref_p[l]].upper_bound(l);
    i--;
    if (s[i] == ',' && pref_p[i + 1] == 1 + pref_p[l]) {
        auto p1 = solve(l + 4, i - 1);
        auto p2 = solve(i + 1, r - 1);
        if (s[l + 2] == 'n') {
            return make_pair(min(p1.first, p2.first), p1.second + p2.second - 1);
        } else {
            return make_pair( p1.first + p2.first, max(pref_q[i] - pref_q[l + 4] + p2.second, pref_q[r] - pref_q[i + 1] + p1.second));
        }
    }
    return p;
}
int main() {
    pref_q.push_back(0), pref_p.push_back(0);
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        pref_q.push_back(pref_q.back() + (s[i] == '?'));
        pref_p.push_back(pref_p.back());
        if (s[i] == '(') {
            pref_p.back()++;
        } else if (s[i] == ')') {
            pref_p.back()--;
        }
    }
    for (int i = 1; i < pref_p.size(); i++) {
        if (s[i - 1] == ',') {
            myMap[pref_p[i]].insert(i);
        }
    }
    auto p = solve(0, s.size() - 1);
    cout << p.second - p.first + 1 << '\n';
}
