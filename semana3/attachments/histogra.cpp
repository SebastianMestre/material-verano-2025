#include <vector>
#include <iostream>
using namespace std;
#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define fst first
#define snd second
#define sz(x) (int((x).size()))
using ll = long long;
int main() {
	int n;
	while (cin >> n, n != 0) {
		vector<int> a(n);
		forn(i, n) cin >> a[i];
		a.insert(begin(a), 0);
		a.insert(end(a), 0);
		n += 2;

		ll ans = 0;
		vector<pair<int, int>> s;
		forn(i, n) {
			while (sz(s) > 1 && s.back().second >= a[i]) {
				int x2 = i;
				int y  = s.back().snd;
				s.pop_back();
				int x1 = s.back().fst;
				ans = max(ans, ll(y) * (x2 - x1));
			}
			s.push_back({i+1, a[i]});
		}
		cout << ans << "\n";
	}
}
