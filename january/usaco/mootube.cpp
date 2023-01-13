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
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    DSU dsu(n);

    vector<pair<int, pair<int, int>>> edges(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges[i] = make_pair(w, make_pair(u, v));
    }

    vector<pair<int, pair<int, int>>> queries(q);
    for (int i = 0; i < q; i++)
    {
        int v, k;
        cin >> k >> v;
        v--;
        queries[i] = make_pair(i, make_pair(v, k));
    }

    sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());
    sort(queries.begin(), queries.end(), [](const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
        return a.second.second > b.second.second;
    });

    vector<int> ans(q);
    int idx = 0;
    for (auto query : queries)
    {
        int v = query.second.first;
        int curK = query.second.second;
        while (idx < (int)edges.size() && edges[idx].first >= curK)
        {
            dsu.unite(edges[idx].second.first, edges[idx].second.second);
            idx++;
        }
        ans[query.first] = dsu.size(v) - 1;
    }

    for (auto x : ans)
    {
        cout << x << '\n';
    }
}