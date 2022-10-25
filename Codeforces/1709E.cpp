#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>
using namespace std;
vector<int> arr;
vector<vector<int>> adj;

void merger (set<int> s1, set<int> &s2, int x) {
    if (s1.size() > s2.size()) {
        swap(s1, s2);
    }
    for (int i: s1) {
        if (s2.count(i ^ x)) {
            s2 = {};
            return;
        }
    }
    for (int i: s1) {
        s2.insert(i);
    }
}

int c = 0;

set<int> small_large_merge (int curNode, int prevNode) {
    if (prevNode != -1) {
        arr[curNode] ^= arr[prevNode];
    }
    set<int> s = {arr[curNode]};
    bool fine = false;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            if (!fine) {
                merger(small_large_merge(i, curNode), s, (prevNode == -1 ? arr[curNode] : arr[curNode] ^ arr[prevNode]));
            } else {
                small_large_merge(i, curNode);
            }
            fine |= s.empty();
        }
    }
    c += fine;
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    arr.resize(n), adj.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    small_large_merge(0, -1);
    cout << c;
}
