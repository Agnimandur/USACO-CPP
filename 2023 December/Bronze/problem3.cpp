/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1349
 * @brief https://www.youtube.com/watch?v=cl41SXh0Evg
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int tests; cin >> tests;
    while (tests--) {
        int N; cin >> N;
        vector<long long> H(N);
        for (int i = 0; i < N; i++) cin >> H[i];
        vector<long long> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];

        vector<int> T(N);
        for (int i = 0; i < N; i++) cin >> T[i];
        vector<int> order(N);
        for (int i = 0; i < N; i++) order[N-1-T[i]] = i;

        long long Dlower = 0;
        long long Dupper = 1e9;
        for (int i = 0; i < N-1; i++) {
            int x = order[i];
            int y = order[i+1];
            //valid d are all those satisfying: H[x] + d*A[x] < H[y] + d*A[y]
            if (A[x] > A[y]) {
                //d < (H[y] - H[x])/(A[x]-A[y])
                long long d = (H[y] - H[x] - 1)/(A[x] - A[y]);
                if (H[y] - H[x] < 0) d = -1;
                Dupper = min(Dupper,d);
            } else if (A[x] < A[y]) {
                //d > (H[x]-H[y])/(A[y]-A[x])
                long long d = (H[x] - H[y])/(A[y] - A[x]) + 1;
                if (H[x] - H[y] < 0) d = 0;
                Dlower = max(Dlower,d);
            } else if (H[x] >= H[y]) {
                Dlower = 1; Dupper = 0;
                break;
            }
        }
        if (Dlower <= Dupper) {
            cout << Dlower << '\n';
        } else {
            cout << "-1\n";
        }
    }
}