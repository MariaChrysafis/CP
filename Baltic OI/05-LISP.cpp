#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    string s;
    while (s.length() != N) {
        string str;
        cin >> str;
        s += str;
    }
    int cnt = 0;
    int balance = 0;
    vector<int> b;
    b.push_back(balance);
    for (char c: s) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        b.push_back(balance);
    }
    vector<int> v;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        if (s[i] == ']') {
            M--;
            if (M == 0) {
                v.push_back(b.back()+cnt);
            } else {
                v.push_back(1);
            }
            if (v.back() <= 0) {
                cout << 0;
                exit(0);
            }
            cnt -= v.back();
        } 
    }
    cnt = 0;
    int c = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') cnt++;
        else if (s[i] == ')') cnt--;
        else cnt -= v[c++];
        if (cnt < 0) {
            cout << 0;
            exit(0);
        }
    }
    cout << 1 << '\n';
    for (int i: v) {
        cout << i << '\n';
    }
}
