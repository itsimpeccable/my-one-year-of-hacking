#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char directions[4] = {'R', 'D', 'L', 'U'};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    char grid[n + 1][m + 1];
    vector<pair<int, int>> monsters;

    pair<int, int> A = make_pair(0, 0), destination = make_pair(0, 0);
    int dist[n + 1][m + 1], par[n + 1][m + 1];
    bool vis[n + 1][m + 1], possible[n + 1][m + 1];
    queue<pair<int, int>> q;
    string path = "";

    memset(par, 0, sizeof par);
    memset(vis, 0, sizeof vis);
    memset(possible, 0, sizeof possible);
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            dist[i][j] = 1e9 + 7;
        }
    }
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'A')
                A = make_pair(i, j);
            if (grid[i][j] == 'M')
                monsters.emplace_back(i, j);
        }
    }
    
    for (pair<int, int> &p : monsters)
    {
        q.push(p);
        par[p.first][p.second] = -1;
        dist[p.first][p.second] = 0;
    }
    
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            pair<int, int> res = make_pair(cur.first + dx[i], cur.second + dy[i]);
            if (res.first >= 1 && res.first <= n && res.second >= 1 && res.second <= m && grid[res.first][res.second] == '.' && !vis[res.first][res.second])
            {
                vis[res.first][res.second] = 1;
                dist[res.first][res.second] = dist[cur.first][cur.second] + 1;
                par[res.first][res.second] = i;
                q.push(res);
            }
        }
    }
    
    q.push(A);

    par[A.first][A.second] = -1;
    dist[A.first][A.second] = 0;
    possible[A.first][A.second] = 1;
    
    memset(vis, 0, sizeof vis);
    
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            pair<int, int> res = make_pair(cur.first + dx[i], cur.second + dy[i]);
            if (res.first >= 1 && res.first <= n && res.second >= 1 && res.second <= m && grid[res.first][res.second] == '.' && !vis[res.first][res.second])
            {
                vis[res.first][res.second] = 1;
                int d = dist[cur.first][cur.second] + 1;
                if (d < dist[res.first][res.second])
                {
                    possible[res.first][res.second] = 1;
                    dist[res.first][res.second] = d;
                }
                par[res.first][res.second] = i;
                q.push(res);
            }
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (i == 1 || j == 1 || i == n || j == m)
            {
                if (possible[i][j])
                {
                    destination = make_pair(i, j);
                    break;
                }
            }
        }
    }

    if (destination.first == 0 && destination.second == 0)
    {
        cout << "NO";
        return 0;
    }

    while (par[destination.first][destination.second] != -1)
    {
        int x = par[destination.first][destination.second];
        path += directions[x];
        destination.first -= dx[x];
        destination.second -= dy[x];
    }

    reverse(path.begin(), path.end());

    cout << "YES\n"
         << path.size() << '\n'
         << path << '\n';
}
