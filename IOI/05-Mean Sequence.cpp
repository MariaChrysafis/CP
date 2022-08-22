#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int64_t myMin = LLONG_MAX, myMax = -LLONG_MIN, prev = 0, cur = 0;
    for (int i = 0; i < N; i++) {
        prev = cur;
        cin >> cur;
        cur = cur - prev;
        if (i % 2) {
            myMax = max(myMax, prev - cur);
        } else {
            myMin = min(myMin, cur - prev);
        }
    }
    cout << max(myMin - myMax + 1, (int64_t)0);
}
