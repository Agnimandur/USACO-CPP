/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1354
 * @brief https://www.youtube.com/watch?v=-dfO1ggJfuc
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

struct TopologicalSort {
    int n;
    vector<vector<pii>> graph;
    vector<bool> visited;
    vector<int> order;
    vector<int> post;

    TopologicalSort(int numNodes) {
        n = numNodes;
        graph.assign(n,vector<pii>{});
    }

    void addEdge(int u, int v, int label) {
        graph[u].push_back({v,label});
    }

    void dfs(int v) {
        visited[v] = true;
        for (pii p : graph[v]) {
            int u = p.first;
            if (!visited[u])
                dfs(u);
        }
        order.push_back(v);
    }

    vector<int> run() {
        visited.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i])
                dfs(i);
        }
        return order;
    }
};

int main() {
    int N,M; cin >> N >> M;

    TopologicalSort ts(N);
    for (int i = 0; i < M; i++) {
        int u,v,label; cin >> u >> v >> label;
        ts.addEdge(u-1,v-1,label);
    }

    vector<int> revorder = ts.run();
    vector<int> length(N);
    vector<vector<int>> nodesAtLength(N,vector<int>{});
    for (int u: revorder) {
        for (pii p: ts.graph[u]) {
            length[u] = max(length[u],1+length[p.first]);
        }
        nodesAtLength[length[u]].push_back(u);
    }

    vector<ll> labelSum(N);
    vector<int> path(N);
    for (int len = 0; len < N; len++) {
        vector<vector<int>> tuples;
        for (int x: nodesAtLength[len]) {
            int v1 = 2e9;
            int v2 = 2e9;
            int y = -1; //x -> y is the optimal edge in the longest path
            for (pii p: ts.graph[x]) {
                if (length[x] == length[p.first]+1) {
                    if (p.second < v1) {
                        v1 = p.second;
                        v2 = path[p.first];
                        y = p.first;
                    } else if (p.second == v1 && path[p.first] < v2) {
                        v2 = path[p.first];
                        y = p.first;
                    }
                }
            }

            if (y >= 0) labelSum[x] = v1+labelSum[y];
            tuples.push_back({v1,v2,x});
        }
        sort(tuples.begin(),tuples.end());
        for (int i = 0; i < (int)tuples.size(); i++) {
            path[tuples[i][2]] = i;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << length[i] << ' ' << labelSum[i] << '\n';
    }
}
