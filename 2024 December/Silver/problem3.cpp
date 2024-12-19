/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1352
 * @brief https://www.youtube.com/watch?v=AlbsVnYgMNg
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

int N,Q;
int conv(int r, int c) {
    return r * N + c;
}

vector<vector<int>> belts;
vector<vector<bool>> usable;
vector<pii> dirs = {{0,1}, {0,-1}, {1, 0}, {-1,0}}; //RLDU

bool OOB(int i, int j) {
    if (belts[i][j] >= 0) {
        int r = i + dirs[belts[i][j]].first;
        int c = j + dirs[belts[i][j]].second;
        return r < 0 || r >= N || c < 0 || c >= N;
    } else {
        return i == 0 || i == N-1 || j == 0 || j == N-1;
    }
}

pii move(int i, int j, int dir) {
    return {i + dirs[dir].first, j + dirs[dir].second};
}

// Count the number of cells that become usable (that connect back to the cells in bfs).
int BFS(queue<pii> bfs) {
    int ans = 0;
    while (!bfs.empty()) {
        pii cell = bfs.front(); bfs.pop();
        ans++;
        for (pii dir: dirs) {
            int newI = cell.first + dir.first;
            int newJ = cell.second + dir.second;
            if (newI >= 0 && newI < N && newJ >= 0 && newJ < N && !usable[newI][newJ]) {
                if (belts[newI][newJ] == -1 || move(newI, newJ, belts[newI][newJ]) == cell) {
                    usable[newI][newJ] = true;
                    bfs.push({newI,newJ});
                }
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    vector<vector<int>> ops;
    belts.assign(N,vector<int>(N,-1));
    usable.assign(N,vector<bool>(N,false));
    for (int q = 0; q < Q; q++) {
        int L,R; cin >> L >> R;
        string dir; cin >> dir;
        int c;
        if (dir == "R") c = 0;
        else if (dir == "L") c = 1;
        else if (dir == "D") c = 2;
        else c = 3;
        ops.push_back({L-1,R-1,c});
        belts[L-1][R-1] = c;
    }

    //the base case usable cells are those on the edge that go out of bounds
    queue<pii> bfs;
    for (int x = 0; x < N; x++) {
        if (OOB(x, 0)) {
            usable[x][0] = true;
            bfs.push({x,0});
        }
        if (OOB(x, N-1)) {
            usable[x][N-1] = true;
            bfs.push({x,N-1});
        }
        if (x > 0 && x < N-1 && OOB(0, x)) {
            usable[0][x] = true;
            bfs.push({0, x});
        }
        if (x > 0 && x < N-1 && OOB(N-1, x)) {
            usable[N-1][x] = true;
            bfs.push({N-1,x});
        }
    }

    // Multisource BFS for all usable cells at the end
    int ans = BFS(bfs);

    vector<int> allAns = {ans};
    for (int q = Q-1; q > 0; q--) {
        //undo operation q
        int i = ops[q][0];
        int j = ops[q][1];
        belts[i][j] = -1;

        if (usable[i][j]) {
            allAns.push_back(ans);
            continue; // Cell is already usable so nothing changes
        }

        //The current cell is usable if it connects to a free cell.
        for (int dir = 0; dir < 4; dir++) {
            pii newCell = move(i, j, dir);
            if (OOB(i, j) || usable[newCell.first][newCell.second]) {
                usable[i][j] = true;
            }
        }

        //Cell (i,j) went from unusable to usable, so we want to update all incoming cells.
        if (usable[i][j]) {
            queue<pii> bfs;
            bfs.push({i,j});
            ans += BFS(bfs);
        }
        allAns.push_back(ans);
    }

    reverse(allAns.begin(), allAns.end());
    for (int a: allAns) cout << N*N - a << '\n';
}