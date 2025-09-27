/*
* Author    : Apu Das Orgho
 * Problem   : Making Equal
 * Created on: 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;

int main() {
    iamspeed

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<int> a(n);
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++) {
            mp[a[i]]++;
            mp[b[i]]--;
        }
        bool f = true;
        for (auto [val,freq]: mp) {
            if (freq % 2 != 0) {
                f = false;
                break;
            }
        }
        if (!f) {
            cout << -1 << endl;
            continue;
        }
        deque<int> d, d2;
        int mn = min(a[0], b[0]);
        for (int i = 0; i < n; i++) {
            auto &ache = mp[a[i]];
            if (ache > 0) {
                d2.push_back(a[i]);
                ache -= 2;
            }
            auto &ache2 = mp[b[i]];
            if (ache2 < 0) {
                d.push_back(b[i]);
                ache2 += 2;
            }
        }
        long long int ans = 0;
        while (!d.empty()) {
            int df = d.front();
            int d2f = d2.front();
            if (df < d2f) {
                d2.pop_back();
                d.pop_front();
                ans += min(2 * mn, df);
            } else {
                d.pop_back();
                d2.pop_front();
                ans += min(2 * mn, d2f);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
