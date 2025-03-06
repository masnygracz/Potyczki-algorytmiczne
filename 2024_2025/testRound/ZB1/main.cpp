#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>

using namespace std;

struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_N = 50000;
    bitset<MAX_N> sets[450000];
    unordered_map<pair<int, int>, int, pair_hash> cache;
    unordered_map<int, int> negation_cache;

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sets[i - 1][j - 1] = 1;
        }
    }

    int extra_set = n;

    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {  // Suma zbiorów
            int x, y;
            cin >> x >> y;
            x--; y--;

            if (cache.count({x, y})) {
                extra_set = cache[{x, y}];
            } else {
                sets[extra_set] = sets[x] | sets[y];
                cache[{x, y}] = extra_set;
            }
        }
        else if (type == 2) {  // Przecięcie zbiorów
            int x, y;
            cin >> x >> y;
            x--; y--;

            if (cache.count({x, y})) {
                extra_set = cache[{x, y}];
            } else {
                sets[extra_set] = sets[x] & sets[y];
                cache[{x, y}] = extra_set;
            }
        }
        else if (type == 3) {  // Negacja zbioru
            int x;
            cin >> x;
            x--;

            if (negation_cache.count(x)) {
                extra_set = negation_cache[x];
            } else {
                sets[extra_set] = ~sets[x];
                sets[extra_set] &= bitset<MAX_N>().set();
                negation_cache[x] = extra_set;
            }
        }

        extra_set++;
    }

    // Obsługa zapytań
    while (q--) {
        int x, v;
        cin >> x >> v;
        x--; v--;

        cout << (sets[x][v] ? "TAK\n" : "NIE\n");
    }

    return 0;
}
