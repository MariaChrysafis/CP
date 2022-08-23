#include <bits/stdc++.h>
 
using namespace std;

void rec (vector<pair<int,int> > v1, vector<pair<int,int> > v2) {
    for (int len = 1; len <= v1.size(); len++) {
        bool fine = true;
        vector<pair<int,int> > res;
        for (int i = 0; i < len; i++) {
            int x1 = v1[v1.size() - len + i].first;
            int x2 = v2[i].first;
            res.push_back(make_pair(x1, x2));
            if ((x1 & x2) != x1) {
                fine = false;
                break;
            }
        }
        if (fine) {
            for (auto& p: res) {
                cout << p.first << " " << p.second << '\n';
            }
            int l = len;
            reverse(v2.begin(), v2.end());
            while (l--) {
                v1.pop_back();
                v2.pop_back();
            }
            reverse(v2.begin(), v2.end());
            rec(v1, v2);
            return;
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<pair<int,int> > v1, v2;
    v1.resize(N), v2.resize(N);
    for (int i = 0; i < N; i++) {
        v1[i].first = v1[i].second = i, v2[i].first = v2[i].second = i + M;
    }
    rec(v1, v2);
}
