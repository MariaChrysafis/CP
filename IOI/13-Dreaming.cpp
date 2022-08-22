#include "dreaming.h"
#include <bits/stdc++.h>
using namespace std;
vector<int> a, b, w;
vector<vector<int> > adj;
map<pair<int,int>,int> myMap;
vector<bool> hasVisited;
vector<int> parent;
pair<int,int> find_farthest_node (int x, bool undo) {
    queue<pair<int,int> > q;
    q.push(make_pair(x, 0));
    hasVisited[x] = true;
    parent[x] = -1;
    vector<int> nodes;
    vector<pair<int,int> > vec;
    while (!q.empty()) {
        pair<int,int> p = q.front();
        nodes.push_back(p.first);
        vec.push_back(make_pair(p.second, p.first));
        q.pop();
        for (int j: adj[p.first]) {
            if (!hasVisited[j]) {
                q.push(make_pair(j, p.second + myMap[make_pair(j, p.first)]));
                parent[j] = p.first;
                hasVisited[j] = true;
            }
        }
    }
 
    if (undo) {
        for (int j: nodes) {
            hasVisited[j] = false;
        }
    }
    sort(vec.begin(), vec.end());
    return vec.back(); //first distance, then node
}
int travelTime (int N, int M, int L, int A[], int B[], int W[]) {
    a.resize(M), b.resize(M), w.resize(M), adj.resize(N), parent.resize(N);
    for (int i = 0; i < M; i++) {
        a[i] = A[i], b[i] = B[i], w[i] = W[i];
        myMap[make_pair(a[i], b[i])] = w[i];
        myMap[make_pair(b[i], a[i])] = w[i];
        adj[a[i]].push_back(b[i]), adj[b[i]].push_back(a[i]);
    }
    hasVisited.assign(N, false);
    vector<int> paths;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (!hasVisited[i]) {
            int x = find_farthest_node(i, true).second;
            pair<int,int> py = find_farthest_node(x, false);
            vector<int> nodes;
            for (int val = py.second; val != -1; val = parent[val]) {
                nodes.push_back(val);
            }
            ans = max(ans, py.first);
            int c = 0;
            int myMin = INT_MAX;
            for (int j = 1; j < (int)nodes.size(); j++) {
                c += myMap[make_pair(nodes[j], nodes[j - 1])];
                myMin = min(myMin,max(c, py.first - c));
            }
            if (nodes.size() == 1) {
                myMin = 0;
            }
            paths.push_back(myMin);
        }
    }
    sort(paths.begin(), paths.end());
    reverse(paths.begin(), paths.end());
    if (paths.size() > 1) {
        ans = max(ans, L + paths[0] + paths[1]);
    } 
    if (paths.size() > 2) {
        ans = max(ans, 2 * L + paths[1] + paths[2]);
    }
    return ans;
}
