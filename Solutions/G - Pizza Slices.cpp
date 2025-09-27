/*
 * Author     : Apu Das Orgho
 * Problem    : Pizza Slices
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define int long long int
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
const int p1 = 137, mod1 = 127657753, p2 = 277, mod2 = 987654319;

int power(long long n, long long k, int mod) {
    int ans = 1 % mod;
    n %= mod;
    if (n < 0) n += mod;
    while (k) {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}

int ip1, ip2;
pair<int, int> pw[N], ipw[N];

void prec() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i].first = (1LL * pw[i - 1].first * p1) % mod1;
        pw[i].second = (1LL * pw[i - 1].second * p2) % mod2;
    }
    ip1 = power(p1, mod1 - 2, mod1);
    ip2 = power(p2, mod2 - 2, mod2);
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        ipw[i].first = (1LL * ipw[i - 1].first * ip1) % mod1;
        ipw[i].second = (1LL * ipw[i - 1].second * ip2) % mod2;
    }
}


vector<pair<int, int> > build(string &s) {
    int n = s.size();
    vector<pair<int, int> > pref(n + 1);
    for (int i = 0; i < n; i++) {
        pref[i].first = 1LL * (s[i] - 'a' + 1) * pw[i].first % mod1;
        if (i) pref[i].first = (pref[i].first + pref[i - 1].first) % mod1;
        pref[i].second = 1LL * (s[i] - 'a' + 1) * pw[i].second % mod2;
        if (i) pref[i].second = (pref[i].second + pref[i - 1].second) % mod2;
    }
    return pref;
}

pair<int, int> get_hash(int i, int j, vector<pair<int, int> > &pref) {
    pair<int, int> hs({0, 0});
    hs.first = pref[j].first;
    if (i) hs.first = (hs.first - pref[i - 1].first + mod1) % mod1;
    hs.first = 1LL * hs.first * ipw[i].first % mod1;
    hs.second = pref[j].second;
    if (i) hs.second = (hs.second - pref[i - 1].second + mod2) % mod2;
    hs.second = 1LL * hs.second * ipw[i].second % mod2;
    return hs;
}

pair<int, int> create_pair(auto &pr, auto &pr2, auto &val) {
    return pair<int, int>((pr.first + pr2.first * val.first) % mod1, (pr.second + pr2.second * val.second) % mod2);
}

pair<int, int> mergeHash(int l1, int r1, int l2, int r2, auto &pref) {
    pair<int, int> pr = get_hash(l1, r1, pref);
    pair<int, int> pr2 = get_hash(l2, r2, pref);
    return create_pair(pr, pr2, pw[r1 - l1 + 1]);
}

void perform_hash(string &s,int &n, int &k, auto &st) {
    vector<pair<int, int> > hsh = build(s);
    for (int i = 0; i < n; i++) {
        int len = n - i;
        int baki = k - len;
        if (baki > 0) {
            pair<int,int> pr = mergeHash(i, n - 1, 0, baki - 1, hsh);
            st.insert(pr);
        } else {
            pair<int,int> pr = get_hash(i, i + k - 1, hsh);
            st.insert(pr);
        }
    }
    return;
}

int32_t main() {
    iamspeed
    prec();
    string s;
    int n, k;
    cin >> n >> k >> s;
    set<pair<int,int> > st;
    perform_hash(s, n, k, st);
    reverse(s.begin(), s.end());
    perform_hash(s, n, k, st);
    cout << st.size() << endl;


    return 0;
}
