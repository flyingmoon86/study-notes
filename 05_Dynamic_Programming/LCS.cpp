// Use explicit standard headers for better portability on MinGW
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
LCS (Longest Common Subsequence) 最长公共子序列
- 目标：给定字符串 a, b，求 LCS 的长度；可选：恢复一条 LCS 序列。
- 复杂度：时间 O(n*m)。
  - 长度：用两行滚动数组，空间 O(m)
  - 恢复序列：需要完整 n*m 表，空间 O(n*m)
- 滚动转移（长度）：
  if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1
  else dp[i][j] = max(dp[i-1][j], dp[i][j-1])
*/

// 仅计算 LCS 长度：两行滚动，空间 O(m)
// 返回 A 和 B 的 LCS 长度，空间 O(min(n,m))
int lcs_two_rows(const string& A, const string& B) {
    int n = A.size(), m = B.size();
    if (n < m) return lcs_two_rows(B, A);          // 保证 m 是较短串
    vector<int> pre(m + 1, 0), cur(m + 1, 0);      // pre = dp[i-1][*], cur = dp[i][*]
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1])
                cur[j] = pre[j - 1] + 1;
            else
                cur[j] = max(cur[j - 1], pre[j]);
        }
        swap(pre, cur);                            // 滚动：pre 接管 cur 的旧数据
        fill(cur.begin(), cur.end(), 0);           // 清空 cur 准备下一行
    }
    return pre[m];                                 // 答案在 pre[m]
}

/* ----- 以下为简单测试 ----- */
int main() {
    string a, b;
    while (cin >> a >> b) {
        cout << "LCS length = " << lcs_two_rows(a, b) << '\n';
    }
    return 0;
}