#include <bits/stdc++.h>
using namespace std;
 
struct BIT{
    vector<int> bit; //1-indexed
    int pref(int ind){
        int ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    int sum(int l, int r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(int ind, int val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void construct (int n) {
        bit.resize(n + 1);
        for(int i = 0; i <= n; i++){
            bit[i] = 0;
        }
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dum; cin >> dum; int N; cin >> N;
    BIT dummy;
    dummy.construct(N + 1);
    vector<BIT> vec;
    vec.assign(N, dummy);
    while (true) {
        int t;
        cin >> t;
        if (t == 3) {
            break;
        }
        if (t == 1) {
            int x, y; int64_t a;
            cin >> x >> y >> a;
            vec[x].update(y, a);
        } else if (t == 2) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int ans = 0;
            for (int i = x1; i <= x2; i++) {
                ans += vec[i].sum(y1, y2);
            }
            cout << ans << '\n';
        }
    }

}
