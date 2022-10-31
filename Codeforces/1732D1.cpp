#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    vector<pair<int64_t,char> > vec(t);
    set<int64_t> factors, pos;
    for (int i = 0; i < t; i++) {
        cin >> vec[i].second >> vec[i].first;
        if (vec[i].second == '?') {
            factors.insert(vec[i].first);
        } else {
            pos.insert(vec[i].first);
        }
    }
    map<int64_t, int64_t> m;
    map<int64_t, vector<int64_t> > oc;
    for (int64_t i: factors) {
        for (int64_t j = i; j <= (int64_t)2e18; j += i) {
            if (!pos.count(j)) {
                m[i] = j;
                break;
            } 
            oc[j].push_back(i);
        }
    }
    reverse(vec.begin(), vec.end());
    vector<int64_t> ans;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].second == '?') {
            ans.push_back(m[vec[i].first]);
        } else {
            for (int64_t x: oc[vec[i].first]) {
                m[x] = min(m[x], vec[i].first);
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for (int64_t i: ans) {
        cout << i << '\n';
    }
}
