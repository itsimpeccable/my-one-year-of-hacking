#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[2500];

int cycle(int start)
{
    int items = INT32_MAX;

    vector<int> dist(n, -1);
    queue<int> graph;

    dist[start] = 0;
    graph.push(start);

    while (!graph.empty())
    {
        int node = graph.front();
        graph.pop();

        for (int adj_node : adj[node])
        {
            if (dist[adj_node] == -1)
            {
                dist[adj_node] = dist[node] + 1;
                graph.push(adj_node);
            }
            else if (dist[adj_node] >= dist[node])
            {
                items = min(items, 1 + dist[adj_node] + dist[node]);
            }
        }
    }

    return items;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
        ans = min(ans, cycle(i));
    }

    if (ans == INT32_MAX)
    {
        cout << -1 << "\n";
        return 0;
    }

    cout << ans << "\n";
}