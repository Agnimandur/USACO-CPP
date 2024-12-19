/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1353
 * @brief https://www.youtube.com/watch?v=IdzVm5tUrrc
*/

#include <bits/stdc++.h>
using namespace std;

bool direct[750][750];
bool routes[750][750];

int main() {
    int N; cin >> N;
    for (int i = 0; i < N-1; i++) {
        string s; cin >> s;
        for (int j = i+1; j < N; j++) {
            if (s[j-i-1]=='1') routes[i][j] = true;
        }
    }

    int ans = 0;
    for (int diff = 1; diff < N; diff++) {
        for (int i = 0; i < N-diff; i++) {
            int j = i+diff;
            direct[i][j] = routes[i][j];
            for (int k = i+1; k <= j-1; k++) {
                direct[i][j] ^= (direct[i][k] & routes[k][j]);
            }
            if (direct[i][j]) ans++;
        }
    }

    cout << ans;
}
