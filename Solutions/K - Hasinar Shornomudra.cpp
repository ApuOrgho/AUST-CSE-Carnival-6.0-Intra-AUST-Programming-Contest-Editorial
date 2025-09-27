/*
* Author     : Apu Das Orgho
 * Problem    : Hasinar Shornomudra
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define ll long long int
using namespace std;

int main() {
    iamspeed
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        bool f = false;
        for (int i = 2; i * i < n; i++) {
            if (n % i != 0)continue;
            if ((n / i) % i != 0) {
                f = true;
                break;
            }
        }
        cout << (f ? "YES" : "!YES") << endl;
    }


    return 0;
}
