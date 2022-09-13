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
struct Hasher {
    vector<int64_t> a, pref, powr;
    int64_t base = 33000857ll;
    int64_t mod = 1000000223ll;
    int64_t res (int x, int y) {
        return (pref[y + 1] - (pref[x] * powr[y - x + 1]) % mod + mod) % mod;
    }
    Hasher (vector<int64_t> a) {
        powr.push_back(1);
        while (powr.size() != a.size() + 1) {
            powr.push_back(powr.back() * base), powr.back() %= mod;
        }
        this->a = a;
        pref.push_back(0);
        for (int i = 0; i < a.size(); i++) {
            pref.push_back(pref.back() * base), pref.back() %= mod;
            pref.back() += a[i], pref.back() %= mod;
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = read_int();
    for (int t = 0; t < T; t++) {
        int n = read_int(), k = read_int();
        vector<int64_t> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = read_int();
        }
        for (int i = 0; i < n; i++) {
            b[i] = read_int();
        }
        Hasher hsa(a), hsb(b);
        bool okay;
        if (k == 0) {
            okay = (a == b);
        } else if (n == 1) {
            okay = true;
        } else if (n == 2) {
            if (a == b && a[0] == a[1]) {
                okay = true;
            } else {
                if (a == b) {
                    okay = (k % 2 == 0);
                } else {
                    okay = (k % 2 == 1);
                }
            }
        } else {
            if (k != 1 && a == b) {
                okay = true;
            } else {
                okay = false;
                for (int i = 0; i < n - 1; i++) {
                    //[0...i] [i + 1...n - 1]
                    //[0....n - i - 2] [n - i - 1 ... n - 1]
                    if (hsa.res(0, i) == hsb.res(n - i - 1, n - 1)
                    && hsa.res(i + 1, n - 1) == hsb.res(0, n - i - 2)) {
                        vector<int> a1, a2, b1, b2;
                        for (int j = 0; j <= i; j++) a1.push_back(a[j]);
                        for (int j = i + 1; j < n; j++) a2.push_back(a[j]);
                        for (int j = 0; j <= n - i - 2; j++) b1.push_back(b[j]);
                        for (int j = n - i - 1; j < n; j++) b2.push_back(b[j]);
                        if (a1 != b2 || b1 != a2) {
                            continue;
                        }
                        okay = true;
                    }
                }
            }
        }
        cout << "Case #" << t + 1 << ": " << (okay ? "YES" : "NO") << '\n';
    }
}
