#include <bits/stdc++.h>
 
#define ll long long
 
using namespace std;
vector<string> vec;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int R, C, M;
    cin >> R >> C >> M;
    vec.resize(R);
    for (int i = 0; i < R; i++) {
        cin >> vec[i];
        assert(vec[i].size() == C);
    }
    string s;
    cin >> s;
    vector<bitset<1000>> orig(R);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (vec[i][j] == '.') {
                orig[i].set(j + 500);
            }
        }
    }
    vector<bitset<1000>> pos = orig;
    map<char, pair<int, int>> myMap;
    myMap['W'] = {0, -1};
    myMap['E'] = {0, 1};
    myMap['S'] = {1, 0};
    myMap['N'] = {-1, 0};
    for (int i = 0; i < s.length(); i++) {
        vector<bitset<1000>> dum(R);
        if (s[i] == '?' || s[i] == 'W') {
            for (int j = 0; j < R; j++) {
                dum[j] |= (pos[j] >> 1);
            }
        }
        if (s[i] == '?' || s[i] == 'E') {
            for (int j = 0; j < R; j++) {
                dum[j] |= (pos[j] << 1);
            }
        }
        if (s[i] == '?' || s[i] == 'N') {
            for (int j = 0; j < R - 1; j++) {
                dum[j] |= pos[j + 1];
            }
        }
        if (s[i] == '?' || s[i] == 'S') {
            for (int j = 1; j < R; j++) {
                dum[j] |= pos[j - 1];
            }
        }
        for (int j = 0; j < R; j++) {
            pos[j] = dum[j] & orig[j];
        }
    }
    int ans = 0;
    for (int i = 0; i < R; i++) {
        ans += pos[i].count();
    }
    cout << ans;
}
