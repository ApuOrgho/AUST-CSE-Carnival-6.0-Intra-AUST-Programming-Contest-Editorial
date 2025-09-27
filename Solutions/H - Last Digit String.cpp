/*
* Author     : Apu Das Orgho
 * Problem    : Last Digit String
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;

int main() {
    iamspeed

    int t;
    cin >> t;
    while (t--) {
        int x, y, z, k;
        cin >> x >> y >> z >> k;

        x %= 10;
        y %= 10;

        vector<int> digits;
        vector<int> seen(10, -1);

        int cur = (x * y) % 10;
        while (seen[cur] == -1) {
            seen[cur] = digits.size();
            digits.push_back(cur);
            cur = (cur * y) % 10;
        }

        int start = seen[cur];
        int cycle = digits.size() - start;

        vector<int> ans;
        ans.reserve(k);

        int begin = z - k;
        for (int i = begin; i < z; i++) {
            if (i < start) ans.push_back(digits[i]);
            else {
                int idx = start + (i - start) % cycle;
                ans.push_back(digits[idx]);
            }
        }

        for (int d: ans) cout << d;
        cout << "\n";
    }
}
