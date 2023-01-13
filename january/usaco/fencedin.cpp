#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }

    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y)
    {
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

int main()
{
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    int horizontal_dist, vertical_dist, n, m;
    cin >> horizontal_dist >> vertical_dist >> n >> m;

    vector<int> x(n + 1), y(m + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> y[i];
    }

    x.push_back(horizontal_dist);
    y.push_back(vertical_dist);

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    n += 2;
    m += 2;

    vector<pair<int, pair<int, int>>> edges;

    int curr_sect = 0, row = 1;
    while (row < m)
    {
        for (int i = 0; i < n - 2; i++)
        {
            edges.push_back({y[row] - y[row - 1], {curr_sect, curr_sect + 1}});
            curr_sect++;
        }

        curr_sect++;
        row++;
    }

    curr_sect = n - 1;
    int col = 1;
    while (col < n)
    {
        int init = curr_sect;
        for (int i = 0; i < m - 2; i++)
        {
            edges.push_back({x[col] - x[col - 1], {curr_sect - (n - 1), curr_sect}});
            curr_sect += (n - 1);
        }
        curr_sect = init + 1;
        col++;
    }

    DSU dsu((n + 2) * (m + 2));

    sort(edges.begin(), edges.end());

    long long ans = 0;
    for (auto &i : edges)
    {
        if (dsu.unite(i.second.first, i.second.second))
        {
            ans += i.first;
        }
    }

    cout << ans << "\n";
}