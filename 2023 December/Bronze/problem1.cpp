/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1347
 * @brief https://www.youtube.com/watch?v=ANGOY_W7pBM
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