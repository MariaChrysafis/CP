#include <bits/stdc++.h>
using namespace std;
set<int> s;
void rec (int x) {
    if (s.count(x)) {
        return;
    }
    s.insert(x);
    rec(x/2);
}
vector<int> kLargest (vector<int> arr, int k) {
    deque<pair<int,int> > d;
    vector<int> ans;
    for (int i = 0; i < arr.size(); i++) {
        while (!d.empty() && d.front().first < arr[i]) {
            d.pop_front();
        }
        if (!d.empty() && d.back().second == i - k) {
            d.pop_back();
        }
        d.push_front(make_pair(arr[i], i));
        if (i >= k - 1) {
            ans.push_back(d.back().first);
        }
    }
    return ans;
}
int alpha[3000][3000];
void solve (vector<vector< int > > &arr, int k) {
    for (int i = 0; i < arr.size(); i++) {
        vector<int> v;
        for (int j = 0; j < arr.size(); j++) {
            v.push_back(arr[j][i]);
        }
        v = kLargest(v, k);
        for (int j = 0; j < v.size(); j++) {
            alpha[j][i] = v[j];
        }
    }
    for (int i = 0; i < arr.size() - k + 1; i++) {
        vector<int> v(arr.size() - k + 1);
        for (int j = 0; j < v.size(); j++) {
            v[j] = alpha[i][j];
        }
        v = kLargest(v, k);
        for (int j = 0; j < v.size(); j++) {
            alpha[i][j] = v[j];
        }
    }
}
long long sum_subtriangles (int N, int K, vector<vector<int> > arr) {
    int n = N; 
    int k = K;
    rec(k);
    s.erase(0);
    int up[n][n][2];
    for (int i = 0; i < n; i++) {
        while (arr[i].size() != n) {
            arr[i].push_back(0);
        }
    }
    int ind[k + 1];
    for (int i = 0; i <= k; i++) {
        ind[i] = -1;
    }
    int c = 0;
    for (int x: s) {
        ind[x] = c++;
        ind[x] %= 2;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            up[i][j][0] = arr[i][j];
        }        
    }
    s.erase(1);
    for (int x: s) {
        int a = ind[x];
        solve(arr, (x + 1)/2);
        for (int i = x - 1; i < n; i++) {
            for (int j = 0; j + x - 1 <= i; j++) {
                if (x % 2 == 0) {
                    up[i][j][a] = max(max(up[i - x/2][j][!a], up[i][j + x/2][!a]), alpha[i - x/2 + 1][j]);
                } else {
                    up[i][j][a] = max(max(up[i][j + x/2 + 1][!a], up[i - (x/2 + 1)][j][!a]), alpha[i - x/2][j]);
                }
            }
        }
    }
    long long ans = 0;
    for (int i = k - 1; i < n; i++) {
        for (int j = 0; j + k - 1 <= i; j++) {
            ans += up[i][j][ind[k]];
        }
    }
    return ans;
}
