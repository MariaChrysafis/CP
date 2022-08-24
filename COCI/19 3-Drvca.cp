#include <bits/stdc++.h>

using namespace std;

struct Arithmetic {
    multiset<int64_t> ms;
    multiset<int64_t> differences;
    set<int64_t> dif;
    bool arithmetic () {
        return (dif.size() <= 1);
    }
    void remove (int64_t x) {
        auto it = ms.find(x);
        int64_t prev = -1, nxt = -1;
        it++;
        if (it != ms.end()) {
            nxt = *it;
        }
        it--;
        if (it != ms.begin()) {
            it--;
            prev = *it;
            it++;
        }
        if (nxt != -1) {
            differences.erase(differences.find(abs(nxt - x)));
            if (differences.find(abs(nxt - x)) == differences.end()) {
                dif.erase(abs(nxt - x));
            }
        }
        if (prev != -1) {
            differences.erase(differences.find(abs(prev - x)));
            if (differences.find(abs(prev - x)) == differences.end()) {
                dif.erase(abs(prev - x));
            }
        }
        if (nxt != -1 && prev != -1) {
            differences.insert(abs(prev - nxt));
            dif.insert(abs(prev - nxt));
        }
        ms.erase(ms.find(x));
    }
    Arithmetic (vector<int64_t> v) {
        for (int i: v) {
            ms.insert(i);
        }
        int64_t prev = -1;
        for (int i: ms) {
            if (prev == -1) {
                prev = i; continue;
            }
            dif.insert(abs(i - prev));
            differences.insert(abs(i - prev));
            prev = i;
        }
    }
};

map<int64_t,int64_t> convert (vector<int64_t> v) {
    map<int64_t,int64_t> s;
    for (int i: v) {
        s[i]++;
    }
    return s;
}

void check1 (vector<int64_t> v, int i1, int i2) {
    Arithmetic arm(v);
    map<int64_t,int64_t> s = convert(v);
    vector<int64_t> new_v;
    new_v.push_back(v[i1]), arm.remove(v[i1]);
    new_v.push_back(v[i2]), arm.remove(v[i2]);
    s[v[i1]]--, s[v[i2]]--;
    while (true) {
        if (arm.arithmetic()) {
            cout << new_v.size() << '\n';
            for (int i: new_v) {
                cout << i << ' ';
            }
            cout << '\n';
            vector<int> a;
            for (auto& p: s) {
                while (p.second--) {
                    a.push_back(p.first);
                }
            }
            cout << a.size() << '\n';
            for (int i: a) {
                cout << i << ' ';
            }
            cout << '\n';
            exit(0);
        }
        int x = 2 * new_v.back() - new_v[new_v.size() - 2];
        if (s[x] == 0) {
            break;
        }
        s[x]--;
        arm.remove(x);
        new_v.push_back(x);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int64_t> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    if (v.size() == 2) {
        cout << 1 << '\n' << v[0] << '\n' <<  1 << '\n' << v[1] << '\n';
        return 0;
    }
    check1(v, 0, 1);
    check1(v, 1, 2);
    check1(v, 0, 2);
    cout << -1;
}
