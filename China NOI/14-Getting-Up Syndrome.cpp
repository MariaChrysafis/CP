#include <bits/stdc++.h>
using namespace std;
int calculate (vector<pair<string,int> > & vec, int x) {
    int val = x;
    for (auto& p: vec) {
        if (p.first == "AND") {
            val = val & p.second;
        } else if (p.first == "OR") {
            val = val | p.second;
        } else {
            val = val ^ p.second;
        }
    }
    return val;
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<string,int> > vec;
    for (int i = 0; i < n; i++) {
        string s; int x;
        cin >> s >> x;
        vec.push_back(make_pair(s, x));
    }
    int ans = 0;
    for (int i = 31; i >= 0; i--) {
        if ((1 << i) + ans > m) {
            continue;
        }
        int a0 = calculate(vec, ans);
        int a1 = calculate(vec, ans + (1 << i));
        ans += (1 << i) * (a1 > a0);
    }
    cout << calculate(vec, ans);
}
