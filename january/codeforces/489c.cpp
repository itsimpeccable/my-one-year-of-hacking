#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    int m, s;
    cin >> m >> s;

    string min_possible, max_possible;

    // special cases
    if (s == 0)
    {
        if (m == 1)
        {
            cout << "0 0"
                 << "\n";
        }
        else
        {
            cout << "-1 -1"
                 << "\n";
        }
        return 0;
    }

    for (int i = 0; i < m; i++)
    {
        int d = min(9, s);
        // min possible
        min_possible += d + '0';
        s -= d;
    }

    // if s > 0, then the sum cannot be reached
    if (s > 0)
    {
        cout << "-1 -1"
             << "\n";
        return 0;
    }

    // max possible
    for (int i = m - 1; i >= 0; i--)
    {
        max_possible += min_possible[i];
    }

    // adjustments
    for (int i = 0; i < m; i++)
    {
        if (max_possible[i] != '0')
        {
            max_possible[i]--;
            max_possible[0]++;
            break;
        }
    }

    cout << max_possible << " " << min_possible << "\n";
}