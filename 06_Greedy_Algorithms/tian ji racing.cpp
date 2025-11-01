#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n, n) {
        vector<int> t(n), k(n);
        for (int i = 0; i < n; ++i) cin >> t[i];
        for (int i = 0; i < n; ++i) cin >> k[i];
        // 降序
        sort(t.begin(), t.end(), greater<int>());
        sort(k.begin(), k.end(), greater<int>());

        int lt = 0, rt = n - 1;   // 田忌最快、最慢指针
        int lk = 0, rk = n - 1;   // 齐王最快、最慢指针
        int win = 0;

        for (int cnt = 0; cnt < n; ++cnt) {
            if (t[lt] > k[lk]) {          // 用最快赢最快
                ++lt; ++lk; ++win;
            } else if (t[rt] > k[rk]) {   // 用最慢赢最慢
                --rt; --rk; ++win;
            } else {                      // 只能最慢对最快
                if (t[rt] < k[lk]) --win; // 送人头
                --rt; ++lk;
            }
        }
        cout << win << '\n';
    }
    return 0;
}