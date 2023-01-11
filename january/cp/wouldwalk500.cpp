#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 2019201997LL, X_FACTOR = 2019201913LL, Y_FACTOR = 2019201949LL;

ll calc(ll a, ll b)
{
    a++, b++;
    return (a * X_FACTOR + b * Y_FACTOR) % MOD;
}

vector<ll> prim(int n)
{
    vector<ll> dist(n, MOD);
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        int min_dist_node = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && (min_dist_node < 0 || dist[j] < dist[min_dist_node]))
            {
                min_dist_node = j;
            }
        }

        visited[min_dist_node] = true;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                dist[j] = min(
                    dist[j],
                    calc(min(min_dist_node, j), max(min_dist_node, j)));
            }
        }
    }

    return dist;
}

int main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    // Just did Kruskal's algorithm by hand via math
    /*
        2019201913x + 2019201949y ≡ −84x−48y [mod 2019201997]

        Note that since x and y are both bounded by N≤7500, this will always return a negative result.
        So, we can clean up for the residue:

        (2019201913x + 2019201949y) [mod 2019201997] = 2019201997 - 84x - 48y

        This will just become an optimization problem, and we can adapt a greedy strategy to put x and y in different groups.
    */

    // cout << MOD - 48LL * n - 84LL * (k - 1LL) << "\n";

    /*
        Of course, we can init a DSU via Kruksal's algorithm, but it's not necessary.
        Here's an implementation with Prim's:
    */

    vector<ll> mst = prim(n);
    sort(mst.begin(), mst.end());

    cout << mst[n - k] << "\n";
}