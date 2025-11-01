#include <bits/stdc++.h>
using namespace std;

// 斐波那契：F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
// 提供两种DP写法：Top-Down(记忆化) 与 Bottom-Up(空间优化)
// 注意：long long 最多安全到 F(92)

// Top-Down 记忆化：O(n) 时间，O(n) 空间
long long fib_topdown(int n, vector<long long>& memo) {
    if(n <= 1) return n;
    if(memo[n] != -1) return memo[n];//直接返回已计算结果
    return memo[n] = fib_topdown(n-1, memo) + fib_topdown(n-2, memo);
}

// Bottom-Up 空间优化：O(n) 时间，O(1) 额外空间
long long fib_bottomup_space_opt(int n) {
    if(n <= 1) return n;
    long long a = 0, b = 1; // F(0), F(1)
    for(int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;

    // 使用 Bottom-Up（推荐）
    cout << fib_bottomup_space_opt(n) << "\n";

    // 如需使用 Top-Down：
    // vector<long long> memo(n+1, -1);
    // cout << fib_topdown(n, memo) << "\n";

    return 0;
}