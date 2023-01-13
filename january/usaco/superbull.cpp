#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000;

int parent[MAXN], comp[MAXN];

struct DSU
{
    void init(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            comp[i] = 1;
        }
    }

    int find(int a)
    {
        if (a == parent[a])
        {
            return a;
        }
        return parent[a] = find(parent[a]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return false;
        }
        
        if (comp[a] > comp[b])
        {
            swap(a, b);
        }

        parent[a] = b;
        comp[b] += comp[a];
        return true;
    }
};

int main()
{
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);

    int n;
    cin >> n;

    int ids[MAXN];
    for (int i = 0; i < n; i++)
    {
        cin >> ids[i];
    }

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            edges.push_back({ids[i] ^ ids[j], {i, j}});
        }
    }

    DSU dsu;
    dsu.init(n);

    sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());

    int eliminated = 0;
    long long ans = 0;
    for (auto e : edges)
    {
        if (dsu.unite(e.second.first, e.second.second))
        {
            eliminated++;
            ans += e.first;
            if (eliminated == n - 1)
            {
                cout << ans << "\n";
                return 0;
            }
        }
    }
}