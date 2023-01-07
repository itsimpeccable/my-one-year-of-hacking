#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }

    // get representive component (uses path compression)
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y)
    { // union by size
        x = get(x), y = get(y);

        if (x == y)
        {
            return false;
        }

        if (e[x] > e[y])
        {
            swap(x, y);
        }

        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

// Kruskal's algorithm
int kruskal(vector<pair<int, pair<int, int>>> &edges, int N)
{
    sort(edges.begin(), edges.end());
    DSU dsu(N);
    int cost = 0;

    for (auto &e : edges)
    {
        if (dsu.unite(e.second.first, e.second.second))
        {
            cost += e.first;
        }
    }

    return cost;
}

// Driver code
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(c, make_pair(a, b));
    }

    cout << kruskal(edges, n) << "\n";
}