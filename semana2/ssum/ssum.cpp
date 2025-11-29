#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
int main() {
	int n; cin >> n;
	int x; cin >> x;
	vector<int> a(n);
	forn(i, n) cin >> a[i];

	set<int> sumas;
	sumas.insert(0);
	for (int x : a) {
		set<int> nuevo;
		for (int y : sumas) {
			nuevo.insert(y);
			nuevo.insert(y + x);
		}
		sumas = nuevo;
	}

	if (sumas.count(x)) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}
