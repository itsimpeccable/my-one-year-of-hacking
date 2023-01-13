#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    
    ll n, k;
    cin >> n >> k;
    k--;

    vector<vector<ll>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;
        --a, --b;
        adj[a].push_back(b), adj[b].push_back(a);
    }

    vector<ll> dist1(n, 1e9), dist2(n, 1e9);
    dist2[k] = 0;

    queue<ll> q;
    q.push(k);

    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        for (ll u : adj[cur])
        {
            if (dist2[cur] + 1 < dist2[u])
            {
                dist2[u] = dist2[cur] + 1;
                q.push(u);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (adj[i].size() == 1)
        {
            q.push(i);
            dist1[i] = 0;
        }
    }

    
    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        for (ll u : adj[cur])
        {
            if (dist1[cur] + 1 < dist1[u])
            {
                dist1[u] = dist1[cur] + 1;
                q.push(u);
            }
        }
    }

    ll ans = 0;
    q.push(k);

    vector<bool> visited(n);
    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        if (dist1[cur] <= dist2[cur])
        {
            ans++;
            continue;
        }
        if (visited[cur])
        {
            continue;
        }
        visited[cur] = true;
        for (ll u : adj[cur])
        {
            q.push(u);
        }
    }

    cout << ans << "\n";
}