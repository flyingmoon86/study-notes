# 最长递增子序列（LIS: Longest Increasing Subsequence）

## 问题定义
- 给定长度为 n 的序列 a[0..n-1]，求其最长「严格递增」子序列的长度；可选地输出任意一条序列。
- 变体：
  - 最长不下降子序列（允许相等）。
  - 最长递减子序列（可对数值取反或逆序处理）。

## O(n²) 动态规划（易实现，支持恢复）
- 状态：`dp[i]` 为以 a[i] 结尾的 LIS 长度。
- 转移（严格递增）：`dp[i] = 1 + max{ dp[j] | j<i 且 a[j] < a[i] }`；若不存在则 `dp[i]=1`。
- 答案：`max_i dp[i]`。
- 路径恢复：记录 `prev[i]` 为来源 j，最终从最大位置回溯。
- 复杂度：时间 O(n²)，空间 O(n)。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if(!(cin >> n)) return 0;
    vector<long long> a(n);
    for(int i=0;i<n;++i) cin >> a[i];

    vector<int> dp(n,1), pre(n,-1);
    int best=0, pos=-1;
    for(int i=0;i<n;++i){
        for(int j=0;j<i;++j){
            if(a[j] < a[i] && dp[j]+1 > dp[i]){
                dp[i]=dp[j]+1; pre[i]=j;
            }
        }
        if(dp[i]>best){ best=dp[i]; pos=i; }
    }

    cout << best << "\n";
    vector<long long> seq; for(int cur=pos; cur!=-1; cur=pre[cur]) seq.push_back(a[cur]);
    reverse(seq.begin(), seq.end());
    for(size_t i=0;i<seq.size();++i) cout<<seq[i]<<(i+1==seq.size()? '\n':' ');
    return 0;
}
```

> 非严格（不下降）时，将条件改为 `a[j] <= a[i]`。

## O(n log n) 二分（耐心排序思想）
- 维护 `tails[k]`：长度为 k+1 的所有递增子序列中，最小可能末尾值。
- 对每个 `x=a[i]`：
  - 严格递增：在 `tails` 上 `lower_bound(x)`（第一个 >=x 的位置）并替换；
  - 不下降：改用 `upper_bound(x)`（第一个 >x 的位置）。
- `tails.size()` 即为 LIS 长度。长度最优，恢复需额外数组。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if(!(cin >> n)) return 0;
    vector<long long> a(n); for(int i=0;i<n;++i) cin>>a[i];

    vector<long long> tails;
    for(long long x: a){
        auto it = lower_bound(tails.begin(), tails.end(), x); // 严格递增
        if(it==tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << (int)tails.size() << "\n";
    return 0;
}
```

### 路径恢复（思路）
- 维护：`pos[len]` 为长度为 len 的子序列最后位置索引；`pre[i]` 为前驱。
- 每次放置到长度 `L` 处：`pre[i] = (L>0 ? pos[L-1] : -1)`，并更新 `pos[L]=i`。
- 最后从 `pos[best_len-1]` 回溯得到一条 LIS。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if(!(cin >> n)) return 0;
    vector<long long> a(n); for(int i=0;i<n;++i) cin>>a[i];

    vector<long long> tails; // 值
    vector<int> pos;         // tails 对应的原数组索引
    vector<int> pre(n,-1);

    for(int i=0;i<n;++i){
        auto it = lower_bound(tails.begin(), tails.end(), a[i]);
        int L = (int)(it - tails.begin());
        if(it==tails.end()) { tails.push_back(a[i]); pos.push_back(i); }
        else { *it = a[i]; pos[L] = i; }
        if(L>0) pre[i]=pos[L-1];
    }

    int len = (int)tails.size();
    cout << len << "\n";
    vector<long long> seq; int cur = pos[len-1];
    while(cur!=-1){ seq.push_back(a[cur]); cur = pre[cur]; }
    reverse(seq.begin(), seq.end());
    for(size_t i=0;i<seq.size();++i) cout<<seq[i]<<(i+1==seq.size()? '\n':' ');
    return 0;
}
```

## 易错点与小贴士
- 严格递增 vs 不下降：严格用 `lower_bound`，不下降用 `upper_bound`。
- 输出序列不唯一，若需字典序最小等需额外约束与记录。
- 只要长度：用 O(n log n)；要路径且 n 不大：O(n²) 更直观。
- 索引 0/1 基注意一致性；大值用 `long long`。