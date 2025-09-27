/*
* Author     : Apu Das Orgho
 * Problem    : Help them!
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
using namespace std;
vector<bool> found(1005, 0);

int main() {
    iamspeed
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        int mn = 1005, mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            found[v[i]] = true;
            mn = min(mn, v[i]);
            mx = max(mx, v[i]);
        }
        for (int i = mn; i <= mx; i++) {
            if (found[i]) {
                found[i] = false;
                continue;
            }
            cout << i << endl;
        }
    }
    return 0;
}
