#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    while (!s.empty() && s.back() == 'A') {
        s.pop_back();
    }
    if (s.empty()) {
        cout << 0;
        return 0;
    }
    vector<int> v;
    char c = s[0];
    v.push_back(0);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            v.back()++;
        } else {
            if (c == 'A') c = 'B';
            else c = 'A';
            v.push_back(1);
        }
    }
    int ans = 0;
    while (!v.empty()) {
        int res = v.back();
        ans++, v.pop_back();
        if (res == 1 && !v.empty()) {
            v.pop_back();
        }
    }
    cout << ans << '\n';
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
