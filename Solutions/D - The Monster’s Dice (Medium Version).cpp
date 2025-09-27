/*
 * Author     : Apu Das Orgho
 * Problem    : The Monster's Dice (Medium Version)
 * Created on : 27-09-2025
 */
#include<bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define ll int
using namespace std;
const int N = 5e6 + 5;
const ll mod = 998244353;
string s, ss;
ll d, x, y, z, cnt, t, tt, cnt2, sum, ans, res, q, n, m, k, i, j;
vector<pair<ll,ll> > graph[N];
vector<ll> cst(N);
ll dijk(int sz, int src) {
    priority_queue<pair<ll,ll> > pq;
    pq.push({0, src});
    vector<bool> vis(sz + 2, 0);
    while (!pq.empty()) {
        auto [cost,node] = pq.top();
        pq.pop();
        cost *= -1;
        if (vis[node])continue;
        cst[node] = cost;
        vis[node] = true;
        for (auto [child,wt]: graph[node]) {
            pq.push({-cost - wt, child});
        }
    }
    return -1;
}

int main() {
    iamspeed
    ///freopen("input.txt","r",stdin);
    ///freopen("output.txt","w",stdout);
    cin >> n >> m >> q;
    set<ll> st;
    int id = 1;
    map<ll,ll> mp, mp2;
    map<ll, bool> block;
    vector<pair<ll,ll> > pr;
    st.insert(1);
    st.insert(n);
    while (m--) {
        cin >> x >> y >> z;
        st.insert(x);
        st.insert(y);
        pr.push_back({x, y});
    }
    vector<ll> queries(q);
    for (i = 0; i < q; i++) {
        cin >> queries[i];
        st.insert(queries[i]);
    }
    vector<ll> v2;
    copy(st.begin(), st.end(), back_inserter(v2));
    st.clear();
    vector<pair<ll,ll> > v;
    for (ll x: v2) {
        for (i = 0; i <= 6; i++) {
            if (!st.count(x + i) && x + i <= n) {
                st.insert(x + i);
                mp[x + i] = id++;
            }
        }
    }
    ll sz = id;
    sort(v.begin(), v.end());
    cst.assign(id + 5, -1);
    for (i = 0; i <= id + 5; i++) {
        graph[i].clear();
    }
    for (auto [xx,yy]: pr) {
        xx = mp[xx], yy = mp[yy];
        block[xx] = true;
        ///graph[xx].push_back({yy, 0});
    }
    for (auto [val,id]: mp) {
        v.push_back({val, id});
    }
    for (i = 0; i < v.size(); i++) {
        auto [ai,id] = v[i];
        if (block.count(id))continue;
        int ct = 0;
        for (j = i + 1; j < v.size(); j++) {
            auto [aj,nid] = v[j];
            ll dist = (aj - ai) / 6 + ((aj - ai) % 6 != 0);
            graph[nid].push_back({id, dist});
            if (aj == v[j - 1].first + 1)ct++;
            else ct = 1;
            if (ct >= 6)break;
        }
    }
    for (auto [xx,yy]: pr) {
        xx = mp[xx], yy = mp[yy];
        graph[yy].push_back({xx, 0});
    }
    dijk(sz, mp[n]);
    for (int id = 0; id < queries.size(); id++) {
        cout << cst[mp[queries[id]]] << endl;
    }

    return 0;
}
