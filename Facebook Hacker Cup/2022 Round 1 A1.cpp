#include <bits/stdc++.h>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; 
    cin >> T;
    for (int t = 0; t < T; t++) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        bool okay;
        if (k == 0) {
            okay = (a == b);
        } else if (n == 1) {
            okay = true;
        } else if (n == 2) {
            if (a == b) {
                okay = (k % 2 == 0);
            } else {
                okay = (k % 2 == 1);
            }
        } else {
            if (k == 1 && a == b) {
                okay = false;
            } else {
                vector<int> mb(b.size() + 1);
                for (int i = 0; i < b.size(); i++) {
                    mb[b[i]] = i;
                }
                vector<int> v;
                for (int i = 0; i < n; i++) {
                    v.push_back(i - mb[a[i]]);
                }
                int cntr = 0;
                for (int i = 1; i < v.size(); i++) {
                    if (v[i] != v[i - 1]) {
                        cntr++;
                    }
                }
                okay = (cntr <= 1);
            }
        }
        cout << "Case #" << t + 1 << ": ";
        if (okay) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
