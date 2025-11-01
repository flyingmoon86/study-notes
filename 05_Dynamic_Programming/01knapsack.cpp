#include <bits/stdc++.h>
using namespace std;

/*
0-1 背包（每件物品最多取一次）
- 输入：
  n W
  w1 v1
  w2 v2
  ...
- 定义：
  dp[cap] 表示容量为 cap 时能取得的最大价值（只用到一维滚动数组）
- 初始化：
  dp[0] = 0，其余为 0（表示不拿任何物品时的价值）
- 转移（关键）：
  对每个物品 i，容量 cap 从大到小遍历：
    如果 cap >= w[i]：
      dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i])
  “倒序遍历容量”的原因：防止同一件物品在同一轮被重复使用（保证是 0-1）
- 复杂度：
  时间 O(n * W)，空间 O(W)
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    if(!(cin >> n >> W)) return 0;

    vector<int> w(n), v(n);
    for (int i = 0; i < n; ++i) cin >> w[i] >> v[i];

    // dp[cap]：容量为 cap 的最大价值
    vector<long long> dp(W + 1, 0);

    // 物品外层；容量内层“从大到小”，确保每件物品只用一次
    for (int i = 0; i < n; ++i) {
        for (int cap = W; cap >= w[i]; --cap) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }

    cout << dp[W] << "\n"; // 输出容量恰为 W 时的最大价值
    return 0;
}