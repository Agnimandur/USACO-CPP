/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1351
 * @brief https://www.youtube.com/watch?v=Z7yHg1y5fgY
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

struct BinaryIndexedTree {
    vector<int> arr;
    int N;

    BinaryIndexedTree (int N) {
        this->N=N;
        arr.assign(N+1,0);
    }

    void add(int i, int val) {
        for (int node = i+1; node <= N; node += (node & (-node)))
            arr[node] += val;
    }

    int sum(int s_i, int e_i) {
        return sum(e_i+1) - sum(s_i);
    }

    int sum(int i) {
        int total = 0;
        for (int node = i; node > 0; node -= (node & (-node)))
            total += arr[node];
        return total;
    }

    int search(int v) {
        int sum = 0;
        int pos = 0;
        for(int i=19; i>=0; i--) {
            if (pos + (1 << i) <= N && sum + arr[pos + (1 << i)] < v) {
                sum += arr[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int Q; cin >> Q;
    while (Q--) {
        int N, K; cin >> N >> K;
        vector<int> tree(N);
        set<int> coords;
        for (int i = 0; i < N; i++) {
            cin >> tree[i];
            coords.insert(tree[i]);
        }

        vector<vector<int>> restrictions(K, vector<int>(3));
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> restrictions[i][j];
                if (j < 2) coords.insert(restrictions[i][j]);
            }
        }

        map<int,int> compression;
        int index = 0;
        for (int x: coords) {
            compression[x] = index;
            index++;
        }
        int C = coords.size();
        BinaryIndexedTree available(C);
        multiset<int> availableSet;
        BinaryIndexedTree used(C);
        for (int i = 0; i < N; i++) {
            available.add(compression[tree[i]], 1);
            availableSet.insert(compression[tree[i]]);
        }
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < 2; j++) restrictions[i][j] = compression[restrictions[i][j]];
        }

        sort(restrictions.begin(), restrictions.end(), [](auto &left, auto &right) {
            return left[1] < right[1];
        }); //in increasing order of R.

        for (vector<int> restriction: restrictions) {
            int L = restriction[0];
            int R = restriction[1];
            int T = restriction[2];
            // the number of trees in use from L to R inclusive.
            int cover = used.sum(L, R);
            while (cover < T) {
                int x = *(--availableSet.upper_bound(R));
                used.add(x, 1);
                availableSet.erase(availableSet.find(x));
                cover++;
            }
        }
        cout << availableSet.size() << '\n';
    }
}
