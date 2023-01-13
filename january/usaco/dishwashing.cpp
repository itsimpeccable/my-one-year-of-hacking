#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);

    int n, base[100005];
    vector<int> items[100005];

    cin >> n;

    int placed = 0, ans = n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;

        if (x < placed) {
            ans = i;
            break;
        }
        
        for (int j = x; j > 0 && !base[j]; j--) {
            base[j] = x;
        }

        while (!items[base[x]].empty() && items[base[x]].back() < x) {
            placed = items[base[x]].back();
            items[base[x]].pop_back();
        }

        items[base[x]].push_back(x);
    }

    cout << ans << "\n";
}