/*
* Author     : Apu Das Orgho
 * Problem    : UCL Final
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define ll long long int
using namespace std;


bool canPartition(const vector<int> &a, int k, ll maxSum) {
    int cnt = 1;
    ll curr = 0;
    for (int x: a) {
        if (x > maxSum) return false;
        if (curr + x <= maxSum) {
            curr += x;
        } else {
            cnt++;
            curr = x;
            if (cnt > k) return false;
        }
    }
    return true;
}

int main() {
    iamspeed

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, (ll) a[i]);
    }

    if (k > n) {
        cout << -1 << "\n";
        return 0;
    }

    ll low = mx, high = sum;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (canPartition(a, k, mid)) high = mid;
        else low = mid + 1;
    }

    cout << low << "\n";
    return 0;
}
