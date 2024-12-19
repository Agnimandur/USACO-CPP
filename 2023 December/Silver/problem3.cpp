/***
 * @author Shiva Oswal (Recursive Dragon)
 * @details http://usaco.org/index.php?page=viewproblem2&cpid=1352
 * @brief https://www.youtube.com/watch?v=AlbsVnYgMNg
*/

#include <bits/stdc++.h>
using namespace std;

int shift(char a, char b) {
    if (a == 'L' && b == 'F') return 1;
    if (a == 'L' && b == 'R') return 2;
    if (a == 'F' && b == 'L') return -1;
    if (a == 'F' && b == 'R') return 1;
    if (a == 'R' && b == 'L') return -2;
    if (a == 'R' && b == 'F') return -1;

    return 0;
}

int main() {
    int T,C; cin >> T >> C;
    set<int> targets;
    for (int i = 0; i < T; i++) {
        int t; cin >> t;
        targets.insert(t);
    }
    string action; cin >> action;
    
    int finalPos = count(action.begin(),action.end(),'R') - count(action.begin(),action.end(),'L');
    vector<vector<int>> suffix(5,vector<int>(C+1,0));
    vector<map<int,int>> destroyedAt(5,map<int,int>{});

    for (int shift = -2; shift <= 2; shift++) {
        int p = finalPos+shift;
        set<int> targetsLeft;
        for (int t: targets) targetsLeft.insert(t);
        for (int i = C-1; i >= 0; i--) {
            int destroyed = 0;
            if (action[i] == 'F' && targetsLeft.count(p)) {
                destroyed = 1;
                targetsLeft.erase(p);

                //In the universe of "shift", target p is destroyed at index i.
                destroyedAt[2+shift][p] = i;
            }
            suffix[2+shift][i] = suffix[2+shift][i+1] + destroyed;
            
            //take a step backwards
            if (action[i] == 'L') p++; 
            if (action[i] == 'R') p--;
        }
    }

    int ans = 0;
    int pref = 0;
    int pos = 0;
    vector<int> overcount(5);
    vector<vector<int>> signal(5,vector<int>(C+1)); //undo overcount

    for (int i = 0; i < C; i++) {
        //total destroyed = pref + (1 if target destroyed due to change) + suffix[2+shift][i+1] - (overcount)
        //overcount = [# of targets destroyed in pref AND in suffix[2+shift] after i]
        //change overcount[2+shift] IF target "pos" is destroyed at index i AND destroyedAt[2+shift][pos] > i.

        for (int shift = -2; shift <= 2; shift++) overcount[2+shift] -= signal[2+shift][i];

        //change action[i] to 'L'
        int shiftL = shift(action[i],'L');
        int valL = pref + suffix[2+shiftL][i+1] - overcount[2+shiftL];
        ans = max(ans,valL);

        //change action[i] to 'R'
        int shiftR = shift(action[i],'R');
        int valR = pref + suffix[2+shiftR][i+1] - overcount[2+shiftR];
        ans = max(ans,valR);

        //change action[i] to 'F'
        int shiftF = shift(action[i],'F');
        int destroyed = 0;
        if (targets.count(pos)) destroyed = 1;
        int destroyedOvercount = 0;
        if (destroyed == 1 && destroyedAt[2+shiftF][pos] > i) destroyedOvercount = 1;
        int valF = pref + destroyed + suffix[2+shiftF][i+1] - overcount[2+shiftF] - destroyedOvercount;
        ans = max(ans,valF);


        //process action[i]
        if (action[i] == 'L') pos--;
        else if (action[i] == 'R') pos++;
        else if (targets.count(pos)) {
            targets.erase(pos);
            pref++;
            for (int shift = -2; shift <= 2; shift++) {
                if (destroyedAt[2+shift][pos] > i) {
                    overcount[2+shift]++;
                    signal[2+shift][destroyedAt[2+shift][pos]]++;
                }
            }
        }
    }
    ans = max(ans,pref);
    cout << ans;
}
