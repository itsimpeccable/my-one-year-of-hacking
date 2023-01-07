#include <bits/stdc++.h>
using namespace std;

class DSU {
    private:
        vector<int> parent;
        vector<int> size;
    public:
        DSU(int size) : parent(size), size(size, 1) {
            for (int i = 0; i < size; i++) {
                parent[i] = i;
            }
        }

        int get_top(int n) {
            return parent[n] == n ? n : (parent[n] = get_top(parent[n]));
        }

        bool link(int n1, int n2) {
            n1 = get_top(n1);
            n2 = get_top(n2);
            if (n1 == n2) {
                return false;
            }
            if (size[n2] > size[n1]) {
                return link(n2, n1);
            }
            parent[n2] = n1;
            size[n1] += size[n2];
            return true;
        }
};

struct Wormhole {
    int c1, c2;
    int width;
};

bool operator<(const Wormhole& w1, const Wormhole& w2) {
    return w1.width < w2.width;
}

int main() {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    int cow_num, wormhole_num;
    cin >> cow_num >> wormhole_num;

    vector<int> cows(cow_num);
    for (int& c : cows) {
        cin >> c;
        c--;
    }

    int max_width = 0;
    vector<Wormhole> wormholes(wormhole_num);
    for (Wormhole& w : wormholes) {
        cin >> w.c1 >> w.c2 >> w.width;
        w.c1--;
        w.c2--;
        max_width = max(max_width, w.width);
    }

    sort(wormholes.begin(), wormholes.end());

    int wormhole_at = wormhole_num;
    DSU dsu(cow_num);
    for (int i = 0; i < cow_num; i++) {
        while (dsu.get_top(i) != dsu.get_top(cows[i])) {
            wormhole_at--;
            dsu.link(wormholes[wormhole_at].c1, wormholes[wormhole_at].c2);
        }
    }

    cout << (wormhole_at == wormhole_num ? -1 : wormholes[wormhole_at].width) << "\n";
}