#define _CRT_SECURE_NO_WARNINGS
#define first ff
#define second ss
#define make_pair mp
#define push_back pb
#define File "task"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <stack>
#include <queue>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

ll gcd(ll a, ll b)
{
	for(;b != 0;)
	{
		ll t = b;
		b = a % b;
		a = t;
	}
	return a;
}

pii solve() {
	/*int n; cin >> n;
	vi ws(n), bs(n);
	for (int i = 0; i < n; ++i) {
		int w; cin >> w;
		ws[i] = w;
		bs[i] = w >= 0 ? 1 : -1;
	}
	double a = ws[0] / bs[0];
	double err = 1e18;
	do {
		double f = 0, deriv = 0;
		for (int i = 0; i < n; ++i) {
			f += (ws[i] - a * bs[i]) * (ws[i] - a * bs[i]);
			deriv += -2 * (ws[i] - a * bs[i]) * bs[i];
		}
		err = f / deriv;
		a -= err;
	} while (abs(err) > 1e-2);*/
	pii ans = mp(0, 1);
	ll n, sum = 0;
	cin >> n;
	vector<pii> a(n, mp(1, 1));
	for (int i = 0; i < n; ++i) {
		cin >> a[i].ff;
		a[i].ff = abs(a[i].ff);
		sum += a[i].ff;
	}
	ll t = gcd(sum, n);
	pii s = mp(sum / t, n / t);
	for (int i = 0; i < n; ++i)
	{
		ll ch = abs(a[i].ff * s.ss - a[i].ss * s.ff), zn = a[i].ss * s.ss;
		t = gcd(ch, zn);
		a[i] = mp(ch / t, zn / t);
		a[i] = mp(a[i].ff * a[i].ff, a[i].ss * a[i].ss);
		ans = mp(ans.ff * a[i].ss + ans.ss * a[i].ff, ans.ss * a[i].ss);
		t = gcd(ans.ff, ans.ss);
		ans = mp(ans.ff / t, ans.ss / t);
	}
	t = gcd(ans.ff, ans.ss);
	ans = mp(ans.ff / t, ans.ss / t);
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#else
	//freopen(File".in", "r", stdin);
	//freopen(File".out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) {
		pii ans = solve();
		cout << ans.ff << '/' << ans.ss << endl;
	}
	/*int t = 400;
	cout << t << endl;
	srand(time(NULL));
	for (int i = 0; i < t; ++i) {
		int n = rand() % 100000 + 1;
		cout << n << endl;
		for (int i = 0; i < n; ++i)
			cout << rand() % 20001 - 10001 << ' ';
		cout << endl;
	}*/
	return 0; 
}