#include <bits/stdc++.h>
using namespace std;

int n, m;
queue<int> col[1005];
char grid[1005][1005];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < m; j++)
        {
            grid[j][i] = str[j];
            if (grid[j][i] == '*')
            {
                col[j].push(i);
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        col[j].push(n);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (col[j].front() < i)
                col[j].pop();
        }

        stack<pair<int, int>> stk;

        for (int j = 0; j < m; j++)
        {
            int start = j;
            while (!stk.empty() && col[j].front() - i < stk.top().second)
            {
                pair<int, int> cur = stk.top();
                stk.pop();
                start = cur.first;
                ans = max(ans, (j - cur.first) * cur.second);
            }
            stk.push(make_pair(start, col[j].front() - i));
        }

        while (!stk.empty())
        {
            pair<int, int> cur = stk.top();
            stk.pop();
            ans = max(ans, (m - cur.first) * cur.second);
        }
    }

    cout << ans << "\n";
}
