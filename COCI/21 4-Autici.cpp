#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int64_t sum = 0, myMin = INT_MAX;
    for (int i = 0; i < n; i++) {
        int64_t x; cin >> x;
        sum += x, myMin = min(myMin, x);
    }
    cout << sum + myMin * (n - 2) << '\n';
}
