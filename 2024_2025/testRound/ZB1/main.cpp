#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    int static_table[n + m][n] = {};
    vector<vector<int>> dynamic_table(n + m);

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
        }
        else if (type == 2) {  // Common part
            int x, y;
            cin >> x >> y;
            x--; y--;

            for (int num : dynamic_table[x]) {
                if (static_table[y][num - 1]) {
                    static_table[extra_set][num - 1] = 1;
                    dynamic_table[extra_set].push_back(num);
                }
            }
        }
        else if (type == 3) {  // Complement of a set
            int x;
            cin >> x;
            x--;

            for (int i = 1; i <= n; i++) {
                if (!static_table[x][i - 1]) {
                    static_table[extra_set][i - 1] = 1;
                    dynamic_table[extra_set].push_back(i);
                }
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