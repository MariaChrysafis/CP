#include <bits/stdc++.h>
using namespace std;
int calculate (vector<pair<string,int> > & vec, int x) {
    for (auto& p: vec) {
        if (p.first == "AND") {
            x = x & p.second;
        } else if (p.first == "OR") {
            x = x | p.second;
        } else {
            x = x ^ p.second;
        }
    }
    return x;
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
        if ((1 << i) + ans <= m && calculate(vec, 0) < calculate(vec, (1 << i))) {
            ans += (1 << i);
        }
    }
    cout << calculate(vec, ans);
}
