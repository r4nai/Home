#define _CRT_SECURE_NO_WARNINGS
#define forn(i, n) for(int i = 0; i < (n); ++i)
#define TEST "rvq"
#define push_back pb
#define make_pair mp
#define first ff
#define second ss

#include <bits\stdc++.h>

using namespace std;


typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

struct tree {
	int s, l, r, d;
};

vi a;
vector<tree> t;

void build(int i, int l, int r) {

}

void solve() {
	int n, k;
	cin >> n >> k;
	a.resize(n + 1, 0);
	int foo = (1 << (int)ceil(log(n) / log(2)));
	t.resize(foo);
	build(1, 1, n + 1);
	forn(i, k) {
		char c;
		cin >> c;
		if (c == 'A') {
			int l, r, x;

		}
}

int main() {
	ios_base::sync_with_stdio(false);
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#elif ONLINE_JUDGE
	freopen(TEST".in", "r", stdin);
	freopen(TEST".out", "w", stdout);
#endif
	solve();
	return 0;
}