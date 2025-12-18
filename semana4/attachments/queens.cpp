#include <bits/stdc++.h>

using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)

int const maxn = 500;

bool c[maxn];
bool d1[2*maxn];
bool d2[2*maxn];

int n;
int col[maxn];

bool go(int i) {
    if (i == n) return true;
    int idx[n];
    forn(j, n) idx[j] = j;
    random_shuffle(idx, idx+n);
    for (int j : idx) {
        if (c[j] || d1[i+j] || d2[i-j+n]) continue;
        c[j] = d1[i+j] = d2[i-j+n] = true;
        col[i] = j;
        if (go(i+1)) return true;
        c[j] = d1[i+j] = d2[i-j+n] = false;
    }
    return false;
}

int main() {
    srand(123123);
    cin >> n;
    if (go(0)) {
        cout << "YES" << endl;
        forn(i, n) {
            forn(j, n) {
                if (col[i] == j) cout << "Q";
                else cout << ".";
            }
            cout << "\n";
        }
    } else {
        cout << "NO" << endl;
    }
}