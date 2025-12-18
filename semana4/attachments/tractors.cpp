#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)

int const maxn = 9;
int n, m;
int tablero[maxn][maxn];

pair<int, int> tractores[4][5] = {
    {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {2, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {2, 0}, {1, 2}},
    {{0, 1}, {1, 1}, {2, 1}, {2, 0}, {2, 2}},
    {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 2}},
};

bool ok(int i, int j, int r) {
    forn(k, 5) {
        auto [di, dj] = tractores[r][k];
        int x = i + di, y = j + dj;
        if (x < 0 || x >= n || y < 0 || y >= m) return false;
        if (tablero[x][y]) return false;
    }
    return true;
}


void poner(int i, int j, int r, int idx) {
    forn(k, 5) {
        auto [di, dj] = tractores[r][k];
        int x = i + di, y = j + dj;
        tablero[x][y] = idx;
    }
}

void sacar(int i, int j, int r) {
    forn(k, 5) {
        auto [di, dj] = tractores[r][k];
        int x = i + di, y = j + dj;
        tablero[x][y] = 0;
    }
}

int cnt = 0;
int best = 0;
int best_tablero[maxn][maxn];

int go(int p) {
    if (p == n*m) return cnt;

    int rem = 0;
    forr(q, p, n*m) rem += (tablero[q/m][q%m] == 0);
    int opt = cnt + rem / 5;
    if (opt <= best) return opt;

    int const i = p / m, j = p % m;
    
    int ans = cnt;
    forn(r, 4) {
        if (!ok(i, j, r)) continue;
        poner(i, j, r, cnt+1); cnt++;
        ans = max(ans, go(p+1));
        sacar(i, j, r); cnt--;
    }
    ans = max(ans, go(p+1));
    
    if (ans > best) {
        best = ans;
        memcpy(best_tablero, tablero, sizeof(tablero));
    }

    return ans;
}

int main() {
    cin >> n >> m;
    cout << go(0) << endl;
    forn(i, n) {
        forn(j, m) {
            int x = best_tablero[i][j];
            cout << (x == 0 ? '.' : char(x-1+'A'));
        }
        cout << "\n";
    }
}