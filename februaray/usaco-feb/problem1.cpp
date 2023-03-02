#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct position
{
    int idx, idy;
    ll val, tmp, sum;

    position(int arr, int b, ll c, ll d, ll e)
    {
        idx = arr, idy = b;
        val = c, tmp = d, sum = e;
    }

    position()
    {
        // do nothing
    }
};

ll arr[502], pre[502], ans[502][502], prefix = 0, cnt = 0;
position dv[600001];
int num = 0;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= n; i++)
    {
        pre[i] = arr[i];
    }

    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i] + pre[i - 1];
    }

    vector<ll> v;
    while (prefix)
    {
        cnt++;
        prefix /= 10;
        v.push_back(prefix % 10);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            dv[num++] = position(i, j, pre[j] - pre[i - 1], 1, 1);
        }
    }

    sort(dv, dv + num, [](position arr, position b)
         { return arr.val < b.val; });

    set<ll> s;
    for (int i = 0; i < num / 1000; i++)
    {
        s.insert(dv[i].val);
    }

    s.size() < n *(n + 1) / 2 ? ans[0][0] = n : ans[0][0] = 1;

    for (int x = 1; x <= n; x++)
    {
        ll r = LLONG_MAX;
        auto itr = s.lower_bound(r);

        for (int y = 1; y < num; y++)
        {
            bool ina = false;
            bool inb = false;

            if (dv[y - 1].idx <= x and x <= dv[y - 1].idy)
            {
                ina = true;
            }
            else if (prefix > x or prefix > y)
            {
                inb = false;
            }
            else
            {
                ina = false;
            }

            if (dv[y].idx <= x and x <= dv[y].idy)
            {
                inb = true;
            }
            else if (prefix > x or prefix > y)
            {
                inb = false;
            }
            else
            {
                inb = false;
            }

            if (ina != inb and dv[y].val - dv[y - 1].val <= r)
            {
                r = dv[y].val - dv[y - 1].val;
            }
        }

        cout << r << "\n";
        memset(ans, 0x3f, sizeof(ans));
    }
}