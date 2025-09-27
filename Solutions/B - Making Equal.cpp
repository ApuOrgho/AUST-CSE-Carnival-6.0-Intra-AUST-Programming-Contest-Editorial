/*
 * Author    : Apu Das Orgho
 * Problem   : Making Equal
 * Created on: 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;


void counFrequency(auto &a, auto &b, auto &d, auto &d2, int &id1, int &id2, int &n, bool &f) {
    int ct = 0, ct2 = 0;
    int x = min((id1 < n ? a[id1] : INT_MAX), (id2 < n ? b[id2] : INT_MAX));
    for (int i = id1; i < n; i++) {
        if (a[i] == x)ct++, id1++;
        else break;
    }
    for (int i = id2; i < n; i++) {
        if (b[i] == x)ct2++, id2++;
        else break;
    }
    int tot = ct + ct2;
    if (tot % 2) {
        f = false;
        return;
    }
    while (ct > ct2) {
        d2.push_back(x);
        ct -= 2;
    }
    while (ct2 > ct) {
        d.push_back(x);
        ct2 -= 2;
    }
}

int main() {
    iamspeed

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        deque<int> d, d2;
        int mn = min(a[0], b[0]) * 2, id1 = 0, id2 = 0;
        bool f = true;
        while (id1 < n || id2 < n) {
            counFrequency(a, b, d, d2, id1, id2, n, f);
        }
        if (!f) {
            cout << -1 << endl;
            continue;
        }
        long long int ans = 0;
        while (!d.empty()) {
            int df = d.front();
            int d2f = d2.front();
            if (df < d2f) {
                d2.pop_back();
                d.pop_front();
                ans += min(mn, df);
            } else {
                d.pop_back();
                d2.pop_front();
                ans += min(mn, d2f);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
