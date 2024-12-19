/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1347
 * @brief https://www.youtube.com/watch?v=ANGOY_W7pBM
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N,M; cin >> N >> M;
    vector<long long> cows(N);
    for (int i = 0; i < N; i++) cin >> cows[i];
    vector<long long> canes(M);
    for (int i = 0; i < M; i++) cin >> canes[i];

    for (long long H: canes) {
        long long floor = 0;
        for (int i = 0; i < N; i++) {
            if (cows[i] > floor) {
                long long eat = min(cows[i] - floor, H - floor);
                cows[i] += eat;
                floor += eat;
                if (floor == H) break;
            }
        }
    }

    for (long long C: cows) cout << C << '\n';
}