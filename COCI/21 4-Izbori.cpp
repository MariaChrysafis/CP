#include <bits/stdc++.h>
 
using namespace std;

struct BinaryIndexTree {
    vector<int64_t> bit; 
    int64_t pref(int ind){
        int64_t ans = 0;
        ind++;
        while(ind > 0){
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    int64_t sum (int l, int r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update (int ind, int64_t val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    BinaryIndexTree (int n){
        bit.resize(n + 1);
        for(int i = 0; i <= n; i++){
            bit[i] = 0;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int arr[n];
    map<int, int> m;
    vector<int> oc[n + 1];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (!m.count(x)) {
            m[x] = m.size();
        }
        arr[i] = m[x];
        oc[arr[i]].push_back(i);
    }
    int64_t c = 0;
    for (int val = 0; val <= n; val++) {
        if (oc[val].empty()) continue;
        pair<int,vector<int> > p;
        p = make_pair(val, oc[val]);
        if (p.second.size() >= 450) {
            int64_t pref[n + 1];
            pref[0] = 0;
            for (int i = 1; i <= n; i++) {
                pref[i] = pref[i - 1] + (arr[i - 1] == p.first);
            }
            BinaryIndexTree br (n + 1 + 2 * pref[n]);
            for (int j = 0; j < n; j++) {
                br.update(2 * pref[j] - j + 2 + n, 1);
                c += br.sum(0, 2 * pref[j  + 1] - j + n);
            }
        } else {
            vector<int> v = p.second;
            for (int i = 0; i < v.size(); i++) {
                for (int j = i; j < v.size(); j++) {
                    int64_t left = ((i == 0) ? v[i] : v[i] - v[i - 1] - 1);
                    int64_t right = ((j == v.size() - 1) ? right = n - v[j] : v[j + 1] - v[j]);
                    int64_t x = 2 * (j - i) - v[j] + v[i] + 1;
                    c += max(min(left, x) - max(x - right, (int64_t)0) + 1, (int64_t) 0) * x;
                    int64_t l1 = max(x - right, (int64_t) 0);
                    int64_t r1 = min(left, x);
                    if (l1 <= r1) {
                        c -= r1 * (r1 + 1)/2 - l1 * (l1 - 1)/2;
                    }
                    c += right * max(min(left, x - right - 1) + 1, (int64_t) 0);
                }
            }
        }

    }
    cout << c; 
}
