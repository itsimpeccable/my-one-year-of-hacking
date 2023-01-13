#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

using ll = long long;

int main()
{
    int n;
    cin >> n;

    // input + find maximum
    int maximum = 0;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        maximum = max(maximum, arr[i]);
    }

    // dp[i] = maximum sum possible using numbers <= i
    vector<ll> freq(maximum + 1, 0), dp(maximum + 1, 0);
    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]++;
    }

    dp[1] = freq[1];

    for (int i = 2; i <= maximum; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + i * freq[i]);
    }

    cout << dp[maximum] << "\n";
}