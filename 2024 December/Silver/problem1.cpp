/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1350
 * @brief https://www.youtube.com/watch?v=K-Ajj2FT1TY
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int Q; cin >> Q;
    while (Q--) {
        int N; cin >> N;
        vector<ll> nums(N);
        for (int i = 0; i < N; i++) cin >> nums[i];

        ll prefix = 0;
        int H = N/2 - 1; //Elsie can get some prefix and suffix with length summing to H.
        for (int i = 0; i < H; i++) prefix += nums[i];
        ll suffix = 0;
        ll elsie = prefix+suffix;
        for (int i = H - 1; i >= 0; i--) {
            prefix -= nums[i]; 
            suffix += nums[N/2 + 1 + i];
            elsie = max(elsie, prefix+suffix);
        }
        ll total = accumulate(nums.begin(), nums.end(), 0LL);
        ll bessie = total - elsie;
        cout << bessie << ' ' << elsie << '\n';
    }
}