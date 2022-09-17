#include <bits/stdc++.h>
using namespace std;
vector<int> adder (int n) {
    vector<int> s;
    int x = 1;
    while (n) {
        s.push_back(min(x, n));
        n -= s.back();
        x *= 2;
    }
    return s;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    int A[N], B[N];
    map<int,int> oc;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        sum += A[i];
        oc[B[i] - A[i]]++;
    }
    vector<int> prev(M + 1), cur(M + 1);
    for (int i = 0; i <= M; i++) {
        cur[i] = prev[i] = 1e6;
    }
    prev[sum] = cur[sum] = 0;
    for (auto& p: oc) {
        cur = prev;
        for (auto & q: adder(p.second)) {
            for (int x = 0; x <= M; x++) {
                if (x - q * p.first >= 0 && x - q * p.first <= M) {
                    cur[x] = min(min(cur[x], prev[x]), prev[x - q * p.first] + q);
                }
            }
            prev = cur;
        }
    }
    for (int i = 0; i <= M; i++) {
        if (cur[i] == 1e6) {
            cur[i] = -1;
        }
        cout << cur[i] << '\n';
    }
}
