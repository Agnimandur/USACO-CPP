/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1348
 * @brief https://www.youtube.com/watch?v=AOj4MWNqGUc
*/

/********   All Required Header Files ********/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
const int INF = 2000000000;
const ll MOD = 998244353;

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