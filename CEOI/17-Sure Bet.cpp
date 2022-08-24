#include <bits/stdc++.h>
 
using namespace std;
int main () {
    int N; cin >> N;
    vector<double> a(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i];
    }
    sort(a.begin(), a.end()), reverse(a.begin(), a.end());
    sort(b.begin(), b.end()), reverse(b.begin(), b.end());
    vector<double> pref_a(N + 1), pref_b(N + 1), min_b(N + 1);
    pref_a[0] = pref_b[0] = min_b[0] = 0;
    for (int i = 1; i <= N; i++) {
        pref_a[i] = pref_a[i - 1] + a[i - 1];
        pref_b[i] = pref_b[i - 1] + b[i - 1];
        min_b[i] = max(pref_b[i] - i, min_b[i - 1]);
    }
    double ansr = 0;
    for (int i = 0; i <= N; i++) {
        int l = 0;
        int r = N;
        while (l != r) {
            int m = (l + r)/2;
            if (pref_a[i] - i - m <= pref_b[m] - i - m) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        ansr = max(ansr, min(pref_a[i] - i - l, pref_b[l] - i - l));
        if (l != 0) {
            ansr = max(ansr, min_b[l - 1] - i);
        }
    }
    printf("%.4lf",(double)ansr);
}
