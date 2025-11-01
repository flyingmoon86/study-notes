#include <bits/stdc++.h>
using namespace std;

/*
完全背包（同一物品可取多次）
- 输入：
  n W
  w1 v1
  w2 v2
  ...
- 定义：
  dp[cap] 表示容量为 cap 时能取得的最大价值
- 初始化：
  dp[0] = 0，其余为 0
- 转移（关键差异）：
  对每个物品 i，容量 cap 从小到大遍历：
    如果 cap >= w[i]：
      dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i])
  “正序遍历容量”的原因：允许在同一轮中重复使用当前物品（cap-w[i] 已包含当前物品 i 的贡献）
- 复杂度：
  时间 O(n * W)，空间 O(W)
- 备注（恰好装满变体）：
  若要求恰好装满，可将 dp 初始化为 -INF，dp[0]=0；最后输出 dp[W]（若仍为 -INF 表示不可达）
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

    // 物品外层；容量内层“从小到大”，允许同一物品多次使用
    for (int i = 0; i < n; ++i) {
        for (int cap = w[i]; cap <= W; ++cap) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }

    cout << dp[W] << "\n";
    return 0;
}