#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    int static_table[n + m][n] = {};
    vector<vector<int>> dynamic_table(n + m);
    unordered_map<string, int> cache;

    // Adding numbers to static and dynamic table
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            dynamic_table[i - 1].push_back(j);
            static_table[i - 1][j - 1] = 1;
        }
    }

    int extra_set = n;
    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {  // Sum of sets
            int x, y;
            cin >> x >> y;
            x--; y--;

            string key = "U_" + to_string(x) + "_" + to_string(y);
            if (cache.count(key)) {
                extra_set = cache[key];
            } else {
                for (int num : dynamic_table[x]) {
                    if (!static_table[extra_set][num - 1]) {
                        static_table[extra_set][num - 1] = 1;
                        dynamic_table[extra_set].push_back(num);
                    }
                }
                for (int num : dynamic_table[y]) {
                    if (!static_table[extra_set][num - 1]) {
                        static_table[extra_set][num - 1] = 1;
                        dynamic_table[extra_set].push_back(num);
                    }
                }
                cache[key] = extra_set;
            }

        }
        else if (type == 2) {  // Common part
            int x, y;
            cin >> x >> y;
            x--; y--;

            string key = "I_" + to_string(x) + "_" + to_string(y);
            if (cache.count(key)) {
                extra_set = cache[key];
            } else {
                for (int num : dynamic_table[x]) {
                    if (static_table[y][num - 1]) {
                        static_table[extra_set][num - 1] = 1;
                        dynamic_table[extra_set].push_back(num);
                    }
                }
                cache[key] = extra_set;
            }

        }
        else if (type == 3) {  // Complement of a set
            int x;
            cin >> x;
            x--;

            string key = "N_" + to_string(x);
            if (cache.count(key)) {
                extra_set = cache[key];
            } else {
                for (int i = 1; i <= n; i++) {
                    if (!static_table[x][i - 1]) {
                        static_table[extra_set][i - 1] = 1;
                        dynamic_table[extra_set].push_back(i);
                    }
                }
                cache[key] = extra_set;
            }
        }
        extra_set++;
    }

    while (q--) {
        int x, v;
        cin >> x >> v;
        x--; v--;

        if (static_table[x][v]) cout << "TAK\n";
        else cout << "NIE\n";
    }
    return 0;
}