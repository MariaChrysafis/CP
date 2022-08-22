#include <bits/stdc++.h>
#include "cave.h"
using namespace std;
void exploreCave (int n) {
    vector<pair<int,bool>> vec;
    int c[n]; int arr[n];
    for (int i = 0; i < n; i++) {
        int a[n];
        for (int j = 0; j < n; j++) a[j] = true;
        for (auto& p: vec) a[p.first] = p.second;
        int x = tryCombination(a);
        bool b = (x >= i + 1 || x == -1);
        int l = 0;
        int r = n - 1;
        while (l != r) {
            int m = (l + r)/2;
            for (int j = 0; j < n; j++) a[j] = !b;
            for (int j = 0; j <= m; j++) a[j] = b;
            for (auto& p: vec) a[p.first] = p.second;
            x = tryCombination(a);
            if (x >= i + 1 || x == -1) r = m;
            else l = m + 1;
        }
        arr[l] = i;
        vec.emplace_back(l, b);
    }
    for (auto& p: vec) {
        c[p.first] = p.second;
    }
    answer(c, arr);
}
