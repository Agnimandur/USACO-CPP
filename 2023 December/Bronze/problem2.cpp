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


int main() {
    int N; cin >> N;
    string cows; cin >> cows;
    vector<pair<int,int>> intervals;
    int sz = 0;
    for (int i = 0; i <= N; i++) {
        if (i < N && cows[i]=='1') {
            sz++;
        } else if (sz > 0) {
            intervals.push_back({i-sz,i-1});
            sz = 0;
        }
    }

    if (intervals.empty()) {
        cout << 0;
        return 0;
    }

    int D = 1e9; //day FJ reports on the sickness
    for (pair<int,int> p: intervals) {
        int x = p.second - p.first + 1; //interval size
        if (p.first == 0 || p.second == N-1) {
            D = min(D,x);
        } else {
            D = min(D,(x+1)/2);
        }
    }

    int ans = 0;
    for (pair<int,int> p: intervals) {
        int x = p.second - p.first + 1; //interval size
        int c = (x + 2*D-2)/(2*D-1);
        ans += c;
    }
    cout << ans;
}