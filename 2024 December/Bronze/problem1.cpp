/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1348
 * @brief https://www.youtube.com/watch?v=AOj4MWNqGUc
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

int intpow(int a, int b) {
    if (b == 0) return 1;
    return a * intpow(a,b-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        string N; cin >> N;
        int P = (int)N.size(); //the number of digits in N
        if (P == 1) {
            cout << "0\n";
            continue;
        }

        int ans = 0;
        //[4..4][5-9][xyz..]
        for (int i = 2; i < P; i++) {
            for (int four = 1; four < i; four++) {
                ans += 5 * intpow(10, i-four-1);
            }
        }

        for (int four = 1; four < P; four++) {
            for (int d = 5; d <= 9; d++) {
                string prefix(four, '4');
                prefix += to_string(d);
                if (prefix < N.substr(0, four + 1)) {
                    ans += intpow(10, P - (four+1));
                } else if (prefix == N.substr(0, four + 1)) {
                    if (four + 1 == P) ans++;
                    else ans += 1 + stoi(N.substr(four+1));
                }
            }
        }
        cout << ans << '\n';
    }
}