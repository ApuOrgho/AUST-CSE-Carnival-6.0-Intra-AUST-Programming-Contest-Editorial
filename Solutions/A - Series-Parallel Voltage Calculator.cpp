/*
 * Author    : Apu Das Orgho
 * Problem   : Series-Parallel Voltage Calculator
 * Created on: 27-09-2025
 */
#include <bits/stdc++.h>
#define iamspeed ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define endl '\n'
using namespace std;
using ll = long long;
using ld = long double;

struct Edge {
    int from, to;
    ll resistance;
};

int main() {
    iamspeed

    int n, m;
    ll V;
    cin >> n >> m >> V;

    vector<Edge> edges(m);
    vector<vector<pair<int, int> > > adj(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll r;
        cin >> a >> b >> r;
        edges[i] = {a, b, r};
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    int query;
    cin >> query;

    if (query == 0) {
        cout << fixed << setprecision(10) << (ld) V << endl;
        return 0;
    }
    if (query == n - 1) {
        cout << fixed << setprecision(10) << 0.0L << endl;
        return 0;
    }

    vector<int> degree(n);
    for (int i = 0; i < n; i++) degree[i] = adj[i].size();

    vector<char> isJunction(n, 0);
    for (int i = 0; i < n; i++) if (i == 0 || i == n - 1 || degree[i] != 2) isJunction[i] = 1;

    vector<char> usedEdge(m, 0);
    map<unsigned long long, ld> invParallel;
    bool queryIsJunction = isJunction[query];
    int qs = -1, qt = -1;
    ld qDist = 0.0L, qLen = 0.0L;

    for (int u = 0; u < n; u++)
        if (isJunction[u]) {
            for (auto [v, eid]: adj[u]) {
                if (usedEdge[eid]) continue;
                int cur = v, prevEdge = eid;
                ld pathLen = edges[eid].resistance;
                usedEdge[eid] = 1;

                if (!queryIsJunction && cur == query && qs == -1) {
                    qs = u;
                    qDist = pathLen;
                }

                while (!isJunction[cur]) {
                    int nextEdge = -1, nextNode = -1;
                    for (auto [nb, id]: adj[cur])
                        if (id != prevEdge) {
                            nextEdge = id;
                            nextNode = nb;
                            break;
                        }
                    if (nextEdge == -1) break;
                    pathLen += edges[nextEdge].resistance;
                    usedEdge[nextEdge] = 1;

                    if (!queryIsJunction && nextNode == query && qs == -1) {
                        qs = u;
                        qDist = pathLen;
                    }
                    prevEdge = nextEdge;
                    cur = nextNode;
                }

                int a = u, b = cur;
                if (a > b) swap(a, b);
                unsigned long long key = ((unsigned long long) a << 32) | (unsigned int) b;
                invParallel[key] += 1.0L / pathLen;

                if (qs == u && qt == -1) {
                    qt = cur;
                    qLen = pathLen;
                }
            }
        }

    vector<vector<pair<int, ld> > > graph(n);
    for (auto &[key, invSum]: invParallel) {
        int a = key >> 32, b = key & 0xffffffffu;
        ld Req = 1.0L / invSum;
        graph[a].push_back({b, Req});
        graph[b].push_back({a, Req});
    }

    vector<int> nodes = {0};
    vector<ld> resistances;
    int prev = -1, cur = 0;
    while (cur != n - 1) {
        auto &nbr = graph[cur];
        int nextNode = -1;
        ld R = 0;
        for (auto [x, r]: nbr)
            if (x != prev) {
                nextNode = x;
                R = r;
                break;
            }
        if (nextNode == -1) {
            nextNode = nbr[0].first;
            R = nbr[0].second;
        }
        resistances.push_back(R);
        nodes.push_back(nextNode);
        prev = cur;
        cur = nextNode;
    }

    int k = nodes.size();
    vector<ld> prefix(k, 0.0L);
    for (int i = 1; i < k; i++) prefix[i] = prefix[i - 1] + resistances[i - 1];
    ld totalR = prefix.back();

    ld RtoQuery = 0.0L;
    if (isJunction[query]) {
        for (int i = 0; i < k; i++)
            if (nodes[i] == query) {
                RtoQuery = prefix[i];
                break;
            }
    } else {
        int is = -1, it = -1;
        for (int i = 0; i < k; i++) {
            if (nodes[i] == qs) is = i;
            if (nodes[i] == qt) it = i;
        }
        RtoQuery = (is < it) ? prefix[is] + qDist : prefix[it] + (qLen - qDist);
    }

    ld current = (ld) V / totalR;
    ld voltageAtQuery = (ld) V - current * RtoQuery;
    cout << fixed << setprecision(10) << (double) voltageAtQuery << endl;
    return 0;
}
