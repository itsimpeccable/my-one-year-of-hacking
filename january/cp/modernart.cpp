#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);

    int n, ans = 0;
    cin >> n;

    vector<int> start(n + 1, INT_MAX), end(n + 1, INT_MIN), color(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    for (int i = 1; i <= n; i++) {
        start[color[i]] = min(start[color[i]], i);
        end[color[i]] = max(end[color[i]], i);
    }

    start[0] = 0;
    end[0] = n + 1;

    stack<int> stk;
    for (int idx = 0; idx <= n; idx++) {
        int curr = color[idx];

        if (idx == start[curr]) {
            stk.push(curr);
            ans = max(ans, (int)stk.size());
        }

        if (stk.top() != curr) {
            cout << -1 << "\n";
            return 0;
        }

        if (idx == end[curr]) {
            stk.pop();
        }
    }

    cout << ans - 1 << "\n";
}