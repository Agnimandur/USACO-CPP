/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1355
 * @brief https://www.youtube.com/watch?v=pWdwUu_l6q4
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

int main() {
    int N; cin >> N;
    vector<ll> X(N+1);
    for (int i = 1; i <= N; i++) cin >> X[i];
    sort(X.begin(),X.end());

    vector<ll> prefix(N+2);
    for (int i = 1; i <= N; i++) prefix[i] = prefix[i-1] + X[i];
    vector<ll> suffix(N+2);
    for (int i = N; i >= 1; i--) suffix[i] = suffix[i+1] + X[i];

    int Q; cin >> Q;
    while (Q--) {
        ll a,b; cin >> a >> b;

        ll fmin = b * suffix[1];
        
        int i = (int)((N*b+a+b-1)/(a+b));
        ll fxi = (a*i+b*i-b*N)*X[i] + (b*suffix[i+1] - a*prefix[i]);


        ll fmax = 1000000*a*N - a*prefix[N];
        cout << min(min(fmin,fmax),fxi) << '\n';
    }
}
