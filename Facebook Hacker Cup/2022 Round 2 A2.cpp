#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int BUF_SZ = 1 << 15;

inline namespace Input {
char buf[BUF_SZ];
int pos;
int len;
char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) {
			return EOF;
		}
	}
	return buf[pos++];
}

int read_int() {
	int x;
	char ch;
	int sgn = 1;
	while (!isdigit(ch = next_char())) {
		if (ch == '-') {
			sgn *= -1;
		}
	}
	x = ch - '0';
	while (isdigit(ch = next_char())) {
		x = x * 10 + (ch - '0');
	}
	return x * sgn;
}
} // namespace Input
inline namespace Output {
char buf[BUF_SZ];
int pos;

void flush_out() {
	fwrite(buf, 1, pos, stdout);
	pos = 0;
}

void write_char(char c) {
	if (pos == BUF_SZ) {
		flush_out();
	}
	buf[pos++] = c;
}

void write_int(int x) {
	static char num_buf[100];
	if (x < 0) {
		write_char('-');
		x *= -1;
	}
	int len = 0;
	for (; x >= 10; x /= 10) {
		num_buf[len++] = (char)('0' + (x % 10));
	}
	write_char((char)('0' + x));
	while (len) {
		write_char(num_buf[--len]);
	}
	write_char('\n');
}

// auto-flush output when program exits
void init_output() { assert(atexit(flush_out) == 0); }
} // namespace Output
int a[(int)1e6 + 10];
int orig[(int)1e6 + 10];
bool f[(int)1e6 + 10];
pair<int,pair<int,int> > queries[(int)1e6 + 10];
map<int64_t,int64_t> id;
set<int64_t> tot;
struct BIT{
    vector<long long> bit; //1-indexed
    void update_point(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void update_range(int l, int r, long long x){
        update_point(l, x);
        update_point(r + 1, -x);
    }
    long long query(int b){
        b++;
        long long sum = 0;
        for(; b ; b -= b & (-b)) sum += bit[b];
        return sum;
    }
    void construct(int n){
        vector<long long> v;
        v.assign(n, 0);
        bit.resize(v.size() + 1);
        for(int i = 0; i <= v.size(); i++){
            bit[i] = 0;
        }
        for(int i = 0; i < v.size(); i++) {
            update_point(i, v[i]);
        }
    }
};
BIT b;
void solver (int N, int Q) {
    id.clear();
    tot.clear();
    for (int i = 0; i < N; i++) {
        a[i] = orig[i];
        if (!id.count(a[i])) {
            id[a[i]] = rand() % (int)1e9;
            tot.insert(id[a[i]]);
        }
    }
    for (int i = 0; i <= N + 3; i++) {
        b.bit[i] = 0;
    }
    for (int i = 0; i < N; i++)  {
        b.update_range(i + 1, N, id[a[i]]);
    }
    for (int q = 0; q < Q; q++) {
        int t = queries[q].first;
        if (t == 1) {
            int x = queries[q].second.first, y = queries[q].second.second;
            x--;
            if (!id.count(y)) {
                id[y] = rand() % (int)1e9;
                tot.insert(id[y]);
            }
            b.update_range(x + 1, N + 1, id[y] - id[a[x]]);
            a[x] = y;
        } else {
            int l = queries[q].second.first, r = queries[q].second.second;
            l--, r--;
            int m = (l + r)/2;
            long long left = b.query(m + 1) - b.query(l);
            long long right = b.query(r + 1) - b.query(m + 1);
            if (tot.count(abs(right - left))) {
                continue;
            }
            m = (l + r)/2 - 1;
            left = b.query(m + 1) - b.query(l);
            right = b.query(r + 1) - b.query(m + 1);
            if (tot.count(abs(right - left))) {
                continue;
            }
            f[q] = false;
        }
    }
}
void solve () {
    int N = read_int();
    for (int i = 0; i < N; i++) {
        orig[i] = read_int();
    }
    int Q = read_int();
    for (int i = 0; i < Q; i++) {
        queries[i].first = read_int(), queries[i].second.first = read_int(), queries[i].second.second = read_int();
        f[i] = true;
    }
    solver(N, Q);
    solver(N, Q);
    int ans = 0;
    for (int i = 0; i < Q; i++) {
        if(queries[i].first == 2) {
            ans += f[i];
        } 
    }
    cout << ans << '\n';
}
int main() {
    freopen("perfectly_balanced_chapter_2_input.txt", "r", stdin);
    freopen("cbarn.out", "w", stdout);
    b.construct((int)1e6 + 10);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = read_int();
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }   
}
