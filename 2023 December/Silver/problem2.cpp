/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1351
 * @brief https://www.youtube.com/watch?v=Z7yHg1y5fgY
*/

#include <bits/stdc++.h>
using namespace std;

int N,K;
int solve(vector<int> A, vector<int> B) {
    vector<int> Apos(N,-1);
    for (int i = 0; i < K; i++) Apos[A[i]-1] = i;
    vector<int> Bpos(N,-1);
    for (int i = 0; i < K; i++) Bpos[B[i]-1] = i;

    map<int,int> freq; //required shift -> frequency
    int extra = 0;
    int maxFreq = 0;
    for (int i = 0; i < N; i++) {
        if (Apos[i] == -1 && Bpos[i] == -1) {
            //value "i" doesn't appear in either cycle, so it can be assigned to the same extra node
            extra++;
        } else if (Apos[i] >= 0 && Bpos[i] >= 0) {
            int shift = (Apos[i] - Bpos[i] + K) % K;
            freq[shift]++;
            maxFreq = max(maxFreq,freq[shift]);
        }
    }
    return maxFreq + extra;
}

int main() {
    cin >> N >> K;
    vector<int> A(K);
    for (int i = 0; i < K; i++) cin >> A[i];

    vector<int> B(K);
    for (int i = 0; i < K; i++) cin >> B[i];

    int ans1 = solve(A,B);
    reverse(B.begin(),B.end());
    int ans2 = solve(A,B);
    cout << max(ans1,ans2) << '\n';
}
