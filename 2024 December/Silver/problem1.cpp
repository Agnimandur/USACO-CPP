/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1350
 * @brief https://www.youtube.com/watch?v=K-Ajj2FT1TY
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

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