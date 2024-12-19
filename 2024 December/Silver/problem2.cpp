#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using order_statistic_tree = tree<
    T,                             // Key type
    null_type,                     // Mapped type (for sets, use null_type)
    std::less<T>,                  // Comparator
    rb_tree_tag,                   // Specifies the underlying tree structure
    tree_order_statistics_node_update // Enables order-statistics functionality
>;
using namespace std;
#define pii pair<int,int>

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int Q; cin >> Q;
    while (Q--) {
        int N, K; cin >> N >> K;
        multiset<int> available;
        for (int i = 0; i < N; i++) {
            int tree; cin >> tree;
            available.insert(tree);
        }
        order_statistic_tree<pii> used;

        vector<array<int,3>> restrictions;
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < 3; j++) cin >> restrictions[i][j];
        }

        sort(restrictions.begin(), restrictions.end(), [](auto &left, auto &right) {
            return left[1] < right[1];
        }); //in increasing order of R.

        int time = 0;
        for (const auto& [L, R, T]: restrictions) {
            // the number of trees in use from L to R inclusive.
            int cover = used.order_of_key({R+1,0}) - used.order_of_key({L,0});
            while (cover < T) {
                int x = *(--available.upper_bound(R));
                used.insert({x, time}); time++;
                available.erase(available.find(x));
                cover++;
            }
        }
        cout << available.size() << '\n';
    }
}