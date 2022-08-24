#include <bits/stdc++.h>
using namespace std;
int f (vector<int> v) {
    int n = v.size();
    multiset<int> s;
    s.insert(v[0]);
    for (int i = 1; i < n; i++) {
        auto it = s.lower_bound(v[i]);
        if (it == s.begin()) {
            s.insert(v[i]);
        } else {
            it--;
            s.erase(it);
            s.insert(v[i]);
        }
    }
    return s.size();
}
int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec.begin(), vec.end());
    vector<int> v;
    for (int i = 0; i < vec.size(); i++) {
        v.push_back(vec[i].second);
    }
    cout << f(v);
}
