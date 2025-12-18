#include <bits/stdc++.h>

using namespace std;

int const maxn = 200;
bool vis[maxn][maxn];
int n, m;

array<pair<int,int>, 8> vecinos(int x, int y) {
    return {{
        {x+1, y+2}, {x+1, y-2}, {x-1, y+2}, {x-1, y-2},
        {x+2, y+1}, {x+2, y-1}, {x-2, y+1}, {x-2, y-1},
    }};
}

int libres(int x, int y) {
    int ans = 0;
    for (auto [nx, ny] : vecinos(x, y)) {
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) ans++;
    }
    return ans;
}

bool go(int x, int y, int steps) {
    if (steps == 0) return true;
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    if (vis[x][y]) return false;
    vis[x][y] = true;
    auto vs = vecinos(x, y);
    sort(begin(vs), end(vs), [&](auto a, auto b) {
        return libres(a.first, a.second) < libres(b.first, b.second);
    });
    for (auto [nx, ny] : vs) if (go(nx, ny, steps-1)) return true;
    vis[x][y] = false;
    return false;
}

int main() {
    cin >> n >> m;
    if (go(0, 0, n*m)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}