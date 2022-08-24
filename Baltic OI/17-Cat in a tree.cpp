#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<pair<int,int>> vec;
vector<int> parent;
vector<bool> isValid;
vector<int> marked;
vector<int> qr;
bool comp (pair<int,int> p1, pair<int,int> p2) {
    return (p1.second > p2.second);
}
void go_down (int curNode, int d) {
    if (d == 0) return;
    if (marked[curNode] >= d) return;
    marked[curNode] = d;
    isValid[curNode] = false;
    for (int i: adj[curNode]) go_down(i, d - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, D;
    cin >> N >> D;
    adj.resize(N), vec.assign(N, {-1, -1}), isValid.assign(N, true), parent.resize(N), marked.assign(N, -1);
    for (int i = 1; i < N; i++) {
        int x; cin >> x;
        adj[x].push_back(i), adj[i].push_back(x);
    }
    queue<pair<int,int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        pair<int,int> pr = q.front();
        q.pop();
        if (vec[pr.first].first != -1) {
            continue;
        }
        vec[pr.first] = pr;
        for (int i: adj[pr.first]) {
            q.push({i, pr.second + 1});
        }
    }
    sort(vec.begin(), vec.end(), comp);
    int ans = 0;
    for (auto& p: vec) {
        if (!isValid[p.first]) {
            continue;
        }
        ans++;
        go_down(p.first, D);
    }
    cout << ans;
 
}
