#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q, a, b;

    char c[100020];
    int f[100020], g[100020];

    cin >> n >> q;
    cin >> c + 1;

    stack<char> s;
    for (int i = 1; i <= n; i++)
    {
        while (s.size() > 0 && s.top() > c[i])
        {
            s.pop();
        }
        f[i] = f[i - 1];
        if (s.size() == 0 || s.top() != c[i])
        {
            f[i]++;
            s.push(c[i]);
        }
    }

    while (s.size())
    {
        s.pop();
    }

    for (int i = n; i >= 1; i--)
    {
        while (s.size() > 0 && s.top() > c[i])
        {
            s.pop();
        }
        g[i] = g[i + 1];
        if (s.size() == 0 || s.top() != c[i])
        {
            g[i]++;
            s.push(c[i]);
        }
    }

    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        cout << f[a - 1] + g[b + 1] << "\n";
    }
}