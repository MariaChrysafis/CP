#include <bits/stdc++.h>

using namespace std;

void triangulation (vector<pair<int,int> > vec, int n) {
    vector<int> adj[n];
    set<int> s[n];
    for (auto& p: vec) {
        adj[p.first].push_back(p.second), s[p.first].insert(p.second);
        adj[p.second].push_back(p.first), s[p.second].insert(p.first);
    }
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            if (adj[j].size() < adj[i].size()) {
                for (int x: adj[j]) {
                    if (s[i].count(x)) {
                        cout << "neispravno bojenje";
                        exit(0);
                    }
                }
            } else {
                for (int x: adj[i]) {
                    if (s[j].count(x)) {
                        cout << "neispravno bojenje";
                        exit(0);
                    }
                }
            }
        }
    }
}

vector<pair<int,int> > merge (vector<pair<int,int> > v1, vector<pair<int,int> > v2) {
    for (auto& p: v2) {
        v1.push_back(p);
    }
    return v1;
}

int main () {
    int t, n;
    cin >> t >> n;
    string str;
    cin >> str;
    vector<pair<int,int> > color[3];
    for (int i = 0; i < str.size(); i++) {
        color[str[i] - '1'].push_back(make_pair(i, (i + 1) % n));
    }
    vector<pair<pair<int,int>,int> > vec(n - 3);
    set<int> st[n];
    for (int i = 0; i < n - 3; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        c--;
        x--, y--;
        if (x > y) {
            swap(x, y);
        }
        color[c].push_back(make_pair(x, y));
        vec.push_back(make_pair(make_pair(x, y), c));
        st[x].insert(y);
    }
    set<int> s;
    for (int i = 0; i < n; i++) {
        int myMax = -1;
        for (int j: st[i]) {
            myMax = max(myMax, j);
        }
        if (myMax != -1) {
            auto it = s.upper_bound(i);
            if (it != s.end() && *it < myMax) {
                cout << "neispravna triangulacija\n";
                exit(0);
            }
        }
        for (int j: st[i]) {
            s.insert(j);
        }
    }
    triangulation(merge(color[0], color[1]), n);
    triangulation(merge(color[2], color[1]), n);
    triangulation(merge(color[0], color[2]), n);
    cout << "tocno\n";
}
