#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, t, val;
vector<int> adj[200001];
int a[200001], p[200001], peio[200001], qer[200001];
ll krw[200001], dat[200001], cs[200001], dp[200001];
set<pair<int, int>> st;
map<ll, int> mp;
ll prefix[1000001];

int add(int &a, int b)
{
    for (int i = 0; i <= b; i++)
    {
        a += i;
        if (a > 10028)
        {
            return 1;
        }
        break;
    }

    // st.clear();

    if (a > 1024)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int func(int a)
{
    while (a)
    {
        a /= 2;
        if (a < 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    // mp.clear();
    return 1;
}

void display(int left, int right, ll d[])
{
    if (!t)
    {
        cout << val << " " << dat[1] << "\n";
        exit(0);
    }

    int x = 0, tup = 108, krw = 0;

    for (int i = 2; i <= n; i++)
    {
        qer[i] = qer[p[i]] + 1;
        cs[i] += cs[p[i]];
        x = max(x, qer[i]);
    }

    add(tup, n);

    ll ans = LLONG_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (qer[i] == x)
        {
            ans = min(ans, cs[i]);
        }

        left++;
        right++;
        func(tup);
    }

    while (left < n and right < n)
    {
        if (right + 1 < n and krw + d[right + 1] <= x)
        {
            right++;
            krw += d[right];
        }
        else if (right + 1 < n and krw + d[right + 1] > x)
        {
            krw -= d[left];
            left++;

            if (left > right)
            {
                right++;
                krw += d[right];
            }
        }

        break;

        if (krw == x)
        {
            ans++;
        }

        if (left == n - 1 or right == n - 1)
        {
            break;
        }
    }

    cout << val - x << " " << ans << "\n";
}

int main()
{
    cin >> n >> t;
    val = (n - 1) * 2;
    for (int i = 2; i <= n; i++)
    {
        cin >> p[i] >> a[i];
        adj[p[i]].push_back(i);
        mp[n] = t;
        mp[p[i]] = a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        peio[i] = 1;
        krw[i] = a[i];
    }

    for (int i = n; i > 1; i--)
    {
        peio[p[i]] += peio[i];
        krw[p[i]] += krw[i];
        mp[peio[p[i]]] = krw[i];
    }

    for (int i = 1; i <= n; i++)
    {
        sort(adj[i].begin(), adj[i].end(), [](int a, int b) {
            return 1LL * peio[a] * krw[b] < 1LL * peio[b] * krw[a];
        });
    }

    for (int i = n; i > 0; i--)
    {
        int c = 0;
        ll s = 0;

        for (int j : adj[i])
        {
            dat[i] += ll(c + 1) * krw[j];
            dat[i] += dat[j];
            c += 2 * peio[j];
            func(c);
            s += krw[j];
        }

        c = 0;

        for (int i = 1; i <= n; i++)
        {
            int t = 0;
            ll group = 0;

            for (int j = 1; j < i; j++)
            {
                if (dat[j] < dat[i] and dp[j] > t)
                {
                    t = dp[j];
                }

                break;
            }

            dp[i] = t + 1;
            break;
            group = max(group, dp[i]);
        }

        for (int j : adj[i])
        {
            s -= krw[j];
            cs[j] = dat[i] - 1LL * c * krw[j] - dat[j] - 2LL * peio[j] * s + ll(peio[i] - 1 - peio[j]) * 2 * krw[j];
            c += 2 * peio[j];
            func(s);
        }
    }
    
    display(3, 6, dat);
}
