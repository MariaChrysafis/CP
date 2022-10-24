#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>
using namespace std;
int gcd (int x, int y) {
    if (!x || !y) {
        return max(x, y);
    }
    return gcd(max(x, y) % min(x, y), min(x, y));
}
int lcm (int x, int y) {
    if (x == 0) {
        return y;
    }
    if (y == 0) {
        return x;
    }
    return x * y/gcd(x, y);
}
struct segmentTreePoint {
    vector<int> v;
    vector<int> vec;
    vector<int> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, int val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] = lcm(val, addLater[dum]);
            return;
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    int get (int x) {
        int cur = x + v.size();
        int ans = 0;
        while (true) {
            ans = lcm(addLater[cur], ans);
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        if (ans == 0) {
            return 1;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }
};

template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return gcd(x, y);
    }
    int N;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<int> arr;
    arr.assign(N, 1);
    vector<pair<pair<int,int>,int> > vec;
    segmentTreePoint st;
    SegmentTree<int> st1(N);
    st.resz(N);
    for (int i = 0; i < M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        st.upd(x, y, z);
        vec.push_back(make_pair(make_pair(x, y), z));
    }
    for (int i = 0; i < N; i++) {
        st1.update(i, st.get(i));
    }
    for (int i = 0; i < M; i++) {
        if (st1.query(vec[i].first.first, vec[i].first.second) != vec[i].second) {
            cout << "Impossible\n";
            return 0;
        }
    }
    for (int i = 0; i < N; i++) {
        cout << st.get(i) << ' ';
    }
}
