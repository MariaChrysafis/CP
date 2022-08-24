#include <bits/stdc++.h>
using namespace std;
struct Order {
	long long price; //price we gain
	long long clockspeed; //clockspeed
	long long cores; //cores we gain
};
bool comp (Order o1, Order o2) {
	if (o1.clockspeed != o2.clockspeed) {
		return (o1.clockspeed > o2.clockspeed);
	}
	return (o1.price < o2.price);
}
void print(Order a) {
	cout << "PRICE: " << a.price << endl;
	cout << "CLOCKSPEED: " << a.clockspeed << endl;
	cout << "CORES " << a.cores << endl;
	cout << "------\n";
}
int main() {
	int n;
	cin >> n;
	vector<Order> v;
	for (int i = 0; i < n; i++) {
		Order a;
		cin >> a.cores >> a.clockspeed >> a.price;
		a.price = -a.price;
		v.push_back(a);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		Order a;
		cin >> a.cores >> a.clockspeed >> a.price;
		a.cores = -a.cores;
		v.push_back(a);
	}
	sort(v.begin(), v.end(), comp);
	vector<long long> dp ((int)1e5 + 10);
	for (int i = 0; i < dp.size(); i++) {
		dp[i] = -LLONG_MAX/3;
	}
	dp[0] = 0;
	long long myMax = 0;
	for (auto p: v) {
		if (p.cores > 0 ) {
			//buy a computer
			for (int i = dp.size() - 1; i >= 0; i--) {
				if (i - abs(p.cores) < 0) continue;
				dp[i] = max(dp[i], dp[i - abs(p.cores)] - abs(p.price));
			}
		} else {
			//customer
			for (int i = 0; i < dp.size(); i++) {
				if (i + abs(p.cores) >= dp.size()) continue;
				dp[i] = max(dp[i], dp[i + abs(p.cores)] + abs(p.price));
			}
		}
	}
	for (int i = 0; i < dp.size(); i++) {
		myMax = max(myMax, dp[i]);
	}
	cout << myMax << endl;
}
