#include <bits/stdc++.h>

using namespace std;
bool isPrime (int64_t x) {
    if (x == 1 || x == 0) {
        return false;
    }
    for (int64_t i = 2; i <= sqrt(x) + 1; i ++) {
        if (x % i == 0 && x != i) {
            return false;
        }
    }
    return true;
}
vector<int64_t> solve (int64_t a, int64_t b) {
    if (isPrime(abs(a - b))) {
        return {a, b};
    }
    if (isPrime(a + b)) {
        return {a, a + b, b};
    }
    if (a > b) {
        vector<int64_t> v = solve(b, a);
        reverse(v.begin(), v.end());
        return v;
    }
    if (isPrime(a - 2)) {
        vector<int64_t> v = solve(2, b);
        if (!v.empty()) {
            reverse(v.begin(), v.end());
            v.push_back(a);
            reverse(v.begin(), v.end());
            return v;
        }
    }
    if (isPrime(b - 2)) {
        vector<int64_t> v = solve(a, 2);
        if (!v.empty()) {
            v.push_back(b);
            return v;
        }
    }
    if (isPrime(a + 2)) {
        vector<int64_t> v = solve(a + 2, b);
        if (!v.empty()) {
            reverse(v.begin(), v.end());
            v.push_back(a);
            reverse(v.begin(), v.end());
        }
        return v;
    }
    if (isPrime(b - 2)) {
        vector<int64_t> v = solve(a, b - 2);
        if (!v.empty()) {
            v.push_back(b);
        }
        return v;
    }
    if (b - 2 >= 2 && isPrime(b - 2)) {
        vector<int64_t> v = solve(a, b - 2);
        if (v.empty() && isPrime(b + 2)) {
            v = solve(a, b + 2);
        }
        v.push_back(b);
        return v;
    }
    return {};
    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t a, b;
    cin >> a >> b;
    vector<int64_t> v = solve(a, b);
    if (v.empty()) {
        cout << -1;
        return 0;
    }
    cout << v.size() << '\n';
    for (int64_t i: v) {
        cout << i << ' ';
    }
}
