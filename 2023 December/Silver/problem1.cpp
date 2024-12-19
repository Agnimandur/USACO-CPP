/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1350
 * @brief https://www.youtube.com/watch?v=K-Ajj2FT1TY
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int N; cin >> N;
    ll M,K; cin >> M >> K;
    vector<pair<ll,ll>> cows; //(w,a) pairs
    for (int i = 0; i < N; i++) {
        long long w,a; cin >> w >> a;
        cows.push_back({w,a});
    }
    sort(cows.begin(),cows.end()); //sort by weight
    map<ll,ll> towers; //tower base weight ->  num towers
    long long ans = 0;

    int index = N-1;
    //greedily assign the M largest cows to form the "base" of M separate towers
    while (index >= 0 && M > 0) {
        ll use = min(cows[index].second, M);
        towers[cows[index].first] = use;
        ans += use;

        cows[index].second -= use; M -= use;
        if (cows[index].second == 0) index--;
    }

    while (index >= 0) {
        ll wi = cows[index].first;
        ll ai = cows[index].second;
        auto it = towers.lower_bound(wi + K);
        if (ai == 0 || it == towers.end()) {
            index--;
        } else {
            ll wopt = it->first;
            ll aopt = it->second;
            ll z = min(ai,aopt);
            if (aopt == z) towers.erase(wopt);
            else towers[wopt] -= z;

            towers[wi] += z;
            cows[index].second -= z;
            ans += z;
        }
    }

    cout << ans;
}
