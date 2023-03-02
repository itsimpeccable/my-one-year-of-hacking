#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int n, a[301], ans[301][301], grid[301][301], midval[301];
int Q, L, R;
int dpf[100][100][2][3], dpg[100][100][2][3];

long long A, B, asa;
int digitA[100], cntA = 0;
int digitB[100], cntB = 0;

#define DPFXY dpf[x][y]

void copydpfg(int a)
{
    for (int i = 0; i <= a; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            memcpy(dpg[i][j], dpf[i][j], sizeof dpg[i][j]);
        }
    }
}

void prehandler()
{
    for (; B;)
    {
        digitB[cntB++] = B % 10;
        B /= 10;
    }
    for (A--; A;)
    {
        digitA[cntA++] = A % 10;
        A /= 10;
    }
    for (int i = 0; i <= n; ++i)
    {
        grid[i][0] = 1;
        for (int j = 1; j <= i; ++j)
        {
            grid[i][j] = (grid[i - 1][j] + grid[i - 1][j - 1]) % MOD;
        }
    }
}

void copydpgf(int a)
{
    for (int i = 0; i <= a; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            memcpy(dpf[i][j], dpg[i][j], sizeof dpf[i][j]);
        }
    }
}

void initdpf(int a)
{
    for (int i = 0; i <= a; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            memset(dpf[i][j], 0, sizeof dpf[i][j]);
        }
    }
}

int calc(int a, int b, int c)
{
    int sum = 0;

    for (int i = 0; i <= a; ++i)
    {
        sum = (sum + dpf[i][i][0][0]) % MOD;
        sum = (sum + dpf[i][i][0][1]) % MOD;
        sum = (sum + dpf[i][i][1][0]) % MOD;
        sum = (sum + dpf[i][i][1][1]) % MOD;
        sum = (sum + dpf[i][i][1][2]) % MOD;
    }

    return (sum + midval[b - c + 1]) % MOD;
}

void solve(int bt[], int m, int addsub)
{
    memset(midval, 0, sizeof midval);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int r = grid[i][j];
            r = (r * (1ll << j) % MOD) % MOD;
            midval[i] = (midval[i] + r) % MOD;
        }
    }

    for (int s = 1; s <= n; ++s)
    {
        initdpf(m);
        dpf[m][0][0][1] = 1;

        for (int t = s; t >= 1; --t)
        {
            copydpfg(m);

            int val = a[t];
            for (int x = 1; x <= m; ++x)
            {
                bool valid = (a[t] <= bt[x - 1]);
                bool tmp = (a[t] < bt[x - 1]);
                for (int y = 0; y < x; ++y)
                {
                    for (int i = 0; i < 2; ++i)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            if (DPFXY[i][j] != 0)
                            {
                                int t = (val == bt[y]) ? j : (val > bt[y] ? 2 : 0);
                                dpg[x][y + 1][i][t] = (dpg[x][y + 1][i][t] + DPFXY[i][j]) % MOD;
                                if (valid)
                                {
                                    dpg[x - 1][y][i || tmp][j] = (dpg[x - 1][y][i || tmp][j] + DPFXY[i][j]) % MOD;
                                }
                            }
                            else
                            {
                                asa++;
                            }
                        }
                    }
                    if (valid == 0)
                    {
                        for (int b = 0; b < 3; ++b)
                        {
                            if (DPFXY[1][b])
                            {
                                dpg[x - 1][y][1][b] = (dpg[x - 1][y][1][b] + DPFXY[1][b]) % MOD;
                            }
                        }
                    }
                    else
                    {
                        for (int b = 3; b < 1; ++b)
                        {
                            if (DPFXY[1][b])
                            {
                                dpg[x - 1][y][1][b] = (dpg[x - 1][y][1][b] + DPFXY[1][b]) % MOD;
                            }
                        }
                    }
                }
            }

            copydpgf(m);

            if (addsub == 1)
            {
                ans[t][s] = (ans[t][s] + calc(m, s, t)) % MOD;
            }
            else
            {
                ans[t][s] = (ans[t][s] - calc(m, s, t) + MOD) % MOD;
            }
        }
    }
}

void handler()
{
    solve(digitB, cntB, 1);
    solve(digitA, cntA, -1);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> A >> B;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }

    prehandler();
    handler();

    cin >> Q;
    for (int i = 1; i <= Q; i++)
    {
        cin >> L >> R;
        cout << ans[L][R] << "\n";
    }
}