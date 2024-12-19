/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1349
 * @brief https://www.youtube.com/watch?v=cl41SXh0Evg
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>

int freq[26][26];
int maxfreq[26][26];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, F; cin >> N >> F;
    string input; cin >> input;
    vector<int> s(N);
    for (int i = 0; i < N; i++) s[i] = input[i]-'a';

    for (int i = 0; i < N-2; i++) {
        if (s[i+1] == s[i+2]) {
            freq[s[i]][s[i+1]]++;
            maxfreq[s[i]][s[i+1]]++;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int c = 0; c < 26; c++) {
            for (int j = i-1; j <= i+1; j++) {
                if (j-1 >= 0 && j+1 < N && s[j] == s[j+1]) freq[s[j-1]][s[j]]--;
            }


            int oldC = s[i];
            s[i] = c;
            for (int j = i-1; j <= i+1; j++) {
                if (j-1 >= 0 && j+1 < N && s[j] == s[j+1]) {
                    freq[s[j-1]][s[j]]++;
                    maxfreq[s[j-1]][s[j]] = max(maxfreq[s[j-1]][s[j]], freq[s[j-1]][s[j]]);
                }
            }
            for (int j = i-1; j <= i+1; j++) {
                if (j-1 >= 0 && j+1 < N && s[j] == s[j+1]) freq[s[j-1]][s[j]]--;
            }
            s[i] = oldC;

            for (int j = i-1; j <= i+1; j++) {
                if (j-1 >= 0 && j+1 < N && s[j] == s[j+1]) freq[s[j-1]][s[j]]++;
            }
        }
    }

    vector<string> ans;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int a = 0; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            if (a != b && maxfreq[a][b] >= F) {
                string moo = string(1, alphabet[a]) + string(2, alphabet[b]);
                ans.push_back(moo);
            }
        }
    }
    cout << ans.size() << '\n';
    for (string moo: ans) cout << moo << '\n';
}