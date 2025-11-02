#include <bits/stdc++.h>
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
int lcs_length_rolling(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(2, vector<int>(m + 1, 0));
    int cur = 0, nxt = 1;
    for (int i = 1; i <= n; ++i) {
        // 当前行的第 0 列保持为 0
        dp[nxt][0] = 0;
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) dp[nxt][j] = dp[cur][j - 1] + 1; // 左上 + 1
            else dp[nxt][j] = max(dp[cur][j], dp[nxt][j - 1]);        // 上 vs 左
        }
        swap(cur, nxt);
    }
    return dp[cur][m];
}

// 恢复一条 LCS 序列：需要完整 dp 表，空间 O(n*m)
string lcs_reconstruct(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    // 回溯构造一条 LCS
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res.push_back(a[i - 1]);
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入：两行或一行两个 token 的字符串
    // 推荐：每个字符串独占一行（更直观）。
    string a, b;
    if (!getline(cin, a)) return 0;
    if (!a.empty() && a.back() == '\r') a.pop_back();

    if (!getline(cin, b)) {
        // 兼容一行两个 token 的情况
        string s1, s2; stringstream ss(a);
        ss >> s1 >> s2;
        if (s2.empty()) return 0; // 读不到第二个字符串
        a = s1; b = s2;
    } else {
        if (!b.empty() && b.back() == '\r') b.pop_back();
    }

    int len = lcs_length_rolling(a, b);
    cout << len << "\n";               // 输出 LCS 长度

    string seq = lcs_reconstruct(a, b); // 可选：恢复一条 LCS
    cout << seq << "\n";               // 输出 LCS 序列（任一条）

    return 0;
}