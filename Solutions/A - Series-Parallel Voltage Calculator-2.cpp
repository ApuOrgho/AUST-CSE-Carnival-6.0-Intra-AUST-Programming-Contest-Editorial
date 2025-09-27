/*
 * Author    : Swapnil Sharma
 * Problem   : Series-Parallel Voltage Calculator
 * Created on: 27-09-2025
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

struct ParallelState {
    long long nextParallel;
    double resistance;

    ParallelState(long long nextParallel, double resistance)
        : nextParallel(nextParallel), resistance(resistance) {
    }
};

vector<bool> visited;
map<long long, map<long long, double> > wireMap;
map<long long, double> resistanceMap;

bool isParallel(long long x, long long n) {
    auto &connections = wireMap[x];
    if (connections.size() > 2) {
        return true;
    }

    if (connections.size() == 2) {
        return x == 0LL || x == n - 1;
    }

    return false;
}

ParallelState calculateParallelResistance(long long x, long long n);

double findTotalResistance(long long x, long long n) {
    if (visited[x]) {
        return -1.0; // Return -1 to indicate that this node has already been visited
    }
    visited[x] = true;
    double totalResistance = 0.0;

    long long nextParallel = x;

    auto &connections = wireMap[x];

    if (isParallel(x, n)) {
        // parallel connection
        ParallelState state(-1LL, 0.0);

        for (auto &entry: connections) {
            long long neighbor = entry.first;
            double resistance = entry.second;

            if (visited[neighbor]) {
                continue;
            }

            state = calculateParallelResistance(neighbor, n);

            state.resistance = resistance + state.resistance;
            totalResistance += 1 / state.resistance;

            if (nextParallel == x) {
                nextParallel = state.nextParallel;
            }
        }

        if (state.nextParallel == n - 1) {
            resistanceMap[x] = 1 / totalResistance;
            // we reached the end
            return 1 / totalResistance;
        }

        connections = wireMap[nextParallel];
        totalResistance = 1 / totalResistance;
        resistanceMap[x] = totalResistance;
        visited[nextParallel] = true;
        x = nextParallel; // Update x to the next parallel node
    }

    for (auto &entry: connections) {
        long long neighbor = entry.first;
        double resistance = entry.second;

        if (visited[neighbor]) {
            continue;
        }

        double futureResistance = findTotalResistance(neighbor, n);
        totalResistance += resistance + futureResistance;
    }

    resistanceMap[x] = totalResistance;
    return totalResistance;
}

ParallelState calculateParallelResistance(long long x, long long n) {
    if (visited[x]) {
        return ParallelState(-1LL, 0.0);
    }

    if (isParallel(x, n)) {
        return ParallelState(x, 0.0);
    }

    visited[x] = true;

    auto &connections = wireMap[x];

    ParallelState state(-1LL, 0.0);

    for (auto &entry: connections) {
        long long neighbor = entry.first;
        double resistance = entry.second;
        if (visited[neighbor]) {
            continue;
        }
        state = calculateParallelResistance(neighbor, n);
        state.resistance += resistance;
    }
    return state;
}

void solve() {
    long long n, m, V;
    cin >> n >> m >> V;

    visited.clear();
    visited.resize(n, false);
    wireMap.clear();
    resistanceMap.clear();

    for (int i = 0; i < m; i++) {
        long long a, b;
        double c;
        cin >> a >> b >> c;

        wireMap[a][b] = c;
        wireMap[b][a] = c;
    }

    long long q;
    cin >> q;

    double totalResistance = findTotalResistance(0LL, n);

    double I = V / totalResistance;

    double res = V - (totalResistance - resistanceMap[q]) * I;

    cout << fixed << setprecision(10) << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}

