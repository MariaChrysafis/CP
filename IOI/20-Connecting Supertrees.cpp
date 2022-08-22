#include <bits/stdc++.h>
#include "supertrees.h"
 
using namespace std;
 
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }
 
public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }
 
    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }
 
    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }
 
    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
 
int construct (vector<vector<int>> grid) {
    vector<vector<int>> ans(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        ans[i].assign(grid[0].size(), 0);
    }
    set<int> s;
    map<int,int> cnt;
    DisjointSetUnion disjointSetUnion(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 3) {
                return false;
            }
            s.insert(grid[i][j]);
            cnt[grid[i][j]]++;
            if (grid[i][j] != 0) {
                disjointSetUnion.join(i, j);
            }
        }
    }
    map<int,vector<int>> myMap;
    for (int i = 0; i < grid.size(); i++) {
        myMap[disjointSetUnion.find_head(i)].push_back(i);
    }
    if (cnt[0] >= 0 && cnt[1] >= 0 && cnt[2] >= 0 && cnt[3] == 0) {
        for (auto& p: myMap) {
            DisjointSetUnion dsu(grid.size());
            map<int,vector<int>> m;
            for (int x: p.second) {
                for (int y: p.second) {
                    if (grid[x][y] == 1) {
                        dsu.join(x, y);
                    }
                }
            }
            for (int i: p.second) {
                m[dsu.find_head(i)].push_back(i);
            }
            vector<int> vec;
            for (auto& q: m) {
                vec.push_back(q.first);
            }
            if (vec.size() != 1) {
                if (vec.size() == 2) {
                    return false;
                }
                for (int i = 0; i < vec.size(); i++) {
                    ans[vec[i]][vec[(i + 1) % (int) vec.size()]] = ans[vec[(i + 1) % (int) vec.size()]][vec[i]] = 1;
                }
            }
            for (int x: vec) {
                for (int y: vec) {
                    if (grid[x][y] == 0) {
                        return false;
                    }
                }
            }
            for (auto& q: m) {
                vector<int> v = q.second;
                for (int i: v) {
                    for (int j: v) {
                        if (grid[i][j] == 0) {
                            return false;
                        }
                    }
                }
                for (int i = 1; i < (int)v.size(); i++) {
                    ans[v[i]][v[0]] = 1;
                    ans[v[0]][v[i]] = 1;
                }
                for (int x: v) {
                    for (int y: v) {
                        if (grid[x][y] != 1) {
                            return 0;
                        }
                    }
                }
            }
 
        }
        build(ans);
        return 1;
    }
}
