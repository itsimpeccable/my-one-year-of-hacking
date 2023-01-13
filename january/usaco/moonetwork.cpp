#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_Y = 10;

struct DSU {
    vector<int> top;
    vector<int> sizes;
    DSU(int n) {
        top.resize(n);
        sizes.resize(n, 1);
        for (int i = 0; i < n; i++) {
            top[i] = i;
        }
    }

    int parent(int a) {
        if (top[a] == a) {
            return a;
        }
        return top[a] = parent(top[a]);
    }

    bool merge(int a, int b) {
        a = parent(a);
        b = parent(b);
        if (a == b) {
            return false;
        }
        if (sizes[b] > sizes[a]) {
            swap(a, b);
        }
        top[b] = a;
        sizes[a] += sizes[b];
        return true;
    }
};

int main() {
    int n;
    cin >> n;

    vector<array<ll, 3>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
        points[i][2] = i;
    }

    sort(points.begin(), points.end());

    vector<array<ll, 3>> buffer(11, {-1, -1, -1});
    vector<array<ll, 3>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            if (buffer[j][2] != -1) {
                ll dist = pow(points[i][0] - buffer[j][0], 2) +
                          pow(points[i][1] - buffer[j][1], 2);
                edges.push_back({dist, points[i][2], buffer[j][2]});
            }
        }
        buffer[points[i][1]] = points[i];
    }

    sort(edges.begin(), edges.end());

    ll ans = 0;
    DSU dsu(n);
    for (int i = 0; i < edges.size(); i++) {
        if (dsu.merge(edges[i][1], edges[i][2])) {
            ans += edges[i][0];
        }
    }

    cout << ans << "\n";
}