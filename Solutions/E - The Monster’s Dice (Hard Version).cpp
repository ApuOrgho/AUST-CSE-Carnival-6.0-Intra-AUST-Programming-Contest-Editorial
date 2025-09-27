/*
 * Author     : Sohom Munasib Sahaun
 * Problem    : The Monster's Dice (Hard Version)
 * Created on : 27-09-2025
 */
#include <bits/stdc++.h>
using namespace std;

#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);
using ll = long long;

const int MX = 7'000'005;
vector<pair<int, int> > g[MX];

void add_edge(int u, int v, int w) {
    assert(u < MX);
    assert(v < MX);
    g[u].emplace_back(w, v);
}

void seg_build(int offset, int ti, int l, int r) {
    if (l == r) {
        add_edge(l, offset + ti, 0);
        return;
    }

    int tl, tr, tm;
    tl = ti * 2 + 1;
    tr = ti * 2 + 2;
    tm = (l + r) / 2;

    add_edge(offset + tl, offset + ti, 0);
    add_edge(offset + tr, offset + ti, 0);

    seg_build(offset, tl, l, tm);
    seg_build(offset, tr, tm + 1, r);
}

void seg_add_edge(int offset, int ti, int l, int r, int L, int R, int v, int w) {
    if ((l > R) || (r < L)) return;
    if ((L <= l) && (r <= R)) {
        add_edge(offset + ti, v, w);
        return;
    }

    int tl, tr, tm;
    tl = ti * 2 + 1;
    tr = ti * 2 + 2;
    tm = (l + r) / 2;

    seg_add_edge(offset, tl, l, tm, L, R, v, w);
    seg_add_edge(offset, tr, tm + 1, r, L, R, v, w);
}

map<int, int> get_normalized_mapping(vector<int> &a) {
    map<int, int> ret;
    for (int i = 0; i < (int) a.size(); ++i) {
        ret[a[i]] = i;
    }
    return ret;
}

int main() {
    FAST;

    // ----- input
    int n, m, q;
    cin >> n >> m >> q;
    assert(clamp(n, 3, 1'000'000'000) == n);
    // assert(clamp(m, 1, min(n-1, 10000)) == m);
    assert(clamp(q, 1, 10000) == q);

    vector<tuple<int, int, int> > edges(m);

    for (int i = 0; i < m; ++i) {
        // int u, l, r; cin >> u >> l >> r;
        int u, l, r;
        cin >> u >> l >> r;
        assert(clamp(u, 1, n-1) == u);
        assert(clamp(l, 1, n-1) == l);
        assert(clamp(r, 1, n-1) == r);
        assert(l <= r);
        --u;
        --l;
        --r;
        edges[i] = {u, l, r};
    }

    vector<int> queries(q);
    for (int i = 0; i < q; ++i) {
        int u;
        cin >> u;
        assert(clamp(u, 1, n-1) == u);
        --u;
        queries[i] = u;
    }

    // ----- find the interesting nodes
    set<int> banned;
    vector<int> in_pts = queries;
    for (int i = 0; i <= min(n - 1, 6); ++i) in_pts.push_back(i);
    for (int i = max(0, n - 7); i <= n - 1; ++i) in_pts.push_back(i);
    for (int i = 0; i < m; ++i) {
        auto [u, l, r] = edges[i];
        banned.insert(u);
        in_pts.push_back(u);
        for (int v = max(0, u - 6); v <= min(n - 1, u + 6); ++v) {
            in_pts.push_back(v);
        }
        for (int v = max(0, l - 6); v <= min(r, l + 6); ++v) {
            in_pts.push_back(v);
        }
        for (int v = max(l, r - 6); v <= min(n - 1, r + 6); ++v) {
            in_pts.push_back(v);
        }
    }
    sort(in_pts.begin(), in_pts.end());
    in_pts.erase(unique(in_pts.begin(), in_pts.end()), in_pts.end());
    int k = (int) in_pts.size();

    // ----- determine the edges of the graph
    vector<int> groups[6];
    for (int i = 0; i < k; ++i) {
        int u = in_pts[i];
        groups[u % 6].push_back(u);
    }

    vector<tuple<int, int, int> > single_edges; // (from, to, cost)
    for (int i = 0; i < k; ++i) {
        int u = in_pts[i];
        for (int g = 0; g < 6; ++g) {
            vector<int> &group = groups[g];
            auto it = lower_bound(group.begin(), group.end(), u);
            if (it == group.begin()) continue;
            --it;
            int v = *it;
            if ((u > v) && (banned.find(v) == banned.end())) {
                single_edges.emplace_back(u, v, (u - v + 5) / 6);
            }
        }
    }
    int prev = -1;
    for (int x: banned) {
        if (prev == -1) {
            prev = x;
            continue;
        }
        for (int u = x; u >= max(0, x - 6); --u) {
            for (int v = prev + 1; v <= min(u - 1, prev + 6); ++v) {
                single_edges.emplace_back(u, v, (u - v + 5) / 6);
            }
        }
        prev = x;
    }

    vector<tuple<int, int, int, int> > range_edges; // (from_L, from_R, to, cost)
    for (int i = 0; i < m; ++i) {
        auto [u, l, r] = edges[i];
        range_edges.emplace_back(l, r, u, 0);
    }

    // ----- get compressed graph node ids
    map<int, int> id = get_normalized_mapping(in_pts);

    // ----- add single edges
    for (auto [u, v, w]: single_edges) {
        add_edge(id.at(u), id.at(v), w);
    }

    // ----- add range edges
    seg_build(k, 0, 0, k - 1);
    for (auto [l, r, v, w]: range_edges) {
        int li = (int) (lower_bound(in_pts.begin(), in_pts.end(), l) - in_pts.begin());
        int ri = (int) (lower_bound(in_pts.begin(), in_pts.end(), r) - in_pts.begin());
        assert(in_pts[li] == l);
        assert(in_pts[ri] == r);
        seg_add_edge(k, 0, 0, k - 1, li, ri, id.at(v), w);
    }

    // ----- find distances
    vector<int> dis(MX, INT_MAX);
    dis[id.at(n - 1)] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.emplace(dis[id.at(n - 1)], id.at(n - 1));
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (dis[u] != w) continue;
        for (auto [w_to, to]: g[u]) {
            if (dis[u] + w_to < dis[to]) {
                dis[to] = dis[u] + w_to;
                pq.emplace(dis[to], to);
            }
        }
    }

    // ----- output
    for (int i = 0; i < q; ++i) {
        int d = dis[id.at(queries[i])];
        if (d == INT_MAX) d = -1;
        cout << d << "\n";
    }

    return 0;
}
