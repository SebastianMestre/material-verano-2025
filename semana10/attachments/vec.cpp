
using ll = long long;

struct vec { int x, y; };

vec operator+(vec a, vec b) { return {a.x+b.x, a.y+b.y}; }
vec operator-(vec a, vec b) { return {a.x-b.x, a.y-b.y}; }

ll dot(vec a, vec b) { return ll(a.x)*b.x + ll(a.y)*b.y; }
vec R(vec a) { return { -a.y, a.x }; }
ll det(vec a, vec b) { return dot(R(a), b); }

bool colineal(vec a, vec b, vec c) { return det(c-a, b-a) == 0; }
bool ccw(vec o, vec b, vec c) { return det(c-o, b-o) > 0; }
bool cw(vec o, vec b, vec c) { return det(c-o, b-o) < 0; }

bool pip(vector<vec> const& a, vec p) {
	int const n = a.size();
	if (cw(a[0], a[1], p)) return false;
	if (ccw(a[0], a[n-1], p)) return false;
	int l = 1, r = n-1;
	while (r - l > 1) {
		int m = (l+r) / 2;
		if (ccw(a[0], a[m], p)) {
			l = m;
		} else {
			r = m;
		}
	}
	if (cw(a[l], a[r], p)) return false;
	return true;
}

