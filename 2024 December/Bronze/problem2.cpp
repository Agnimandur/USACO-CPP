/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1348
 * @brief https://www.youtube.com/watch?v=AOj4MWNqGUc
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

int X[1000][1000];
int Y[1000][1000];
int Z[1000][1000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N,Q; cin >> N >> Q;
    int ans = 0;
    while (Q--) {
        int x,y,z; cin >> x >> y >> z;
        X[y][z]++;
        Y[x][z]++;
        Z[x][y]++;
        if (X[y][z] == N) ans++;
        if (Y[x][z] == N) ans++;
        if (Z[x][y] == N) ans++;
        cout << ans << '\n';
    }
}