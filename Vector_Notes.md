# C++ `vector` 速查笔记

面向 DP / BFS 常见场景的一页纸总结：一维/多维数组写法、初始化、遍历、常用操作与常见坑。

## 为什么用 `vector` 而不是原生数组
- 动态长度：运行时决定大小，省心省力。
- 自动管理内存：避免手动 new/delete。
- 连续内存：支持随机访问，能与标准算法（sort/lower_bound 等）配合。

---

## 一维 `vector`（动态数组）

创建与初始化：
```cpp
vector<int> a;                 // 空
vector<int> b(5);              // 长度5，默认0
vector<int> c(5, 42);          // 长度5，元素=42
vector<int> d = {1,2,3};       // 列表初始化
vector<long long> dp(W+1, 0);  // 典型DP：容量0..W
```

基本操作（摊还 O(1)）：
```cpp
a.push_back(10);
a.emplace_back(10);            // 原地构造，少拷贝
a.pop_back();
a.size(); a.clear(); a.empty();
```

容量管理：
```cpp
a.reserve(100000);             // 预留容量，减少扩容
a.capacity();
a.shrink_to_fit();             // 尝试收缩（非强制）
```

访问与遍历：
```cpp
int x = a[i];                  // 不检查越界
int y = a.at(i);               // 检查越界，异常更安全

for (int v : a) { /* range-for */ }
for (size_t i = 0; i < a.size(); ++i) { /* 索引遍历 */ }
for (auto it = a.begin(); it != a.end(); ++it) { /* 迭代器 */ }
```

修改与构造：
```cpp
a.assign(5, -1);               // 变成长度5，每个=-1
a.resize(100, 0);              // 扩到100，补0
a.insert(a.begin()+k, 3);      // 中间插入（O(n)）
a.erase(a.begin()+l, a.begin()+r); // 删除区间 [l,r)
```

排序与查找：
```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end()); // 去重（需先排序）
auto it = lower_bound(a.begin(), a.end(), key); // 二分
```

小坑：
- `vector<bool>` 是特化类型（按位压缩），引用与取地址特殊；若需要布尔数组，建议 `vector<char>`/`vector<uint8_t>`。
- 频繁在中间插入/删除是 O(n)；该场景考虑 `deque`/`list`。

---

## 二维 `vector`（二维数组）在 DP / BFS 中

安全且常用的初始化：
```cpp
int n = 3, m = 4;
vector<vector<int>> dp(n, vector<int>(m, 0));      // n行m列，初值0
vector<vector<int>> dist(n, vector<int>(m, -1));   // BFS 距离表
```

网格输入（常见于迷宫类/BFS）：
```cpp
int n, m; cin >> n >> m;
vector<string> grid(n);
for (int i = 0; i < n; ++i) cin >> grid[i];
// grid[i][j]：'#'障碍、'.'可走、'S'起点、'T'终点等
```

遍历：
```cpp
for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    /* dp[i][j] / grid[i][j] */;
```

注意：上述初始化每行是“值拷贝”，不是同一行引用；改 `dp[i][j]` 不会影响其他行。

---

## 三维 `vector`（大状态空间慎用）

```cpp
int A=201,B=201,C=201;
vector<vector<vector<char>>> vis(
  A, vector<vector<char>>(B, vector<char>(C, 0))
);
```
- 三维内存开销巨大（A×B×C）。
- 三壶倒水等问题常按规模选：定长数组 `bool visited[201][201][201]`，或用 `unordered_set`/`unordered_map` 存可达状态。

---

## 来自 DP / BFS 代码的典型用法

0-1 背包（一维滚动，容量倒序，避免重复取）：
```cpp
vector<long long> dp(W + 1, 0);
for (int i = 0; i < n; ++i)
  for (int cap = W; cap >= w[i]; --cap)
    dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
```

完全背包（一维滚动，容量正序，允许多次取）：
```cpp
vector<long long> dp(W + 1, 0);
for (int i = 0; i < n; ++i)
  for (int cap = w[i]; cap <= W; ++cap)
    dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
```

LCS（两行滚动）：
```cpp
vector<vector<int>> dp(2, vector<int>(m+1, 0));
int cur = 0, nxt = 1;
for (int i = 1; i <= n; ++i) {
  fill(dp[nxt].begin(), dp[nxt].end(), 0);        // 当前行基础值
  for (int j = 1; j <= m; ++j) {//从左到右填（j从小到大）
    if (a[i-1] == b[j-1]) dp[nxt][j] = dp[cur][j-1] + 1;   // 左上来自上一行
    else dp[nxt][j] = max(dp[cur][j], dp[nxt][j-1]);       // 上 vs 左
  }
  swap(cur, nxt);
}
int ans = dp[cur][m];  // 最后一次 swap 后，答案在 cur 行

```

BFS 网格（`vector<string>` + 二维 `dist`）：
```cpp
vector<string> grid(n);
vector<vector<int>> dist(n, vector<int>(m, -1));
queue<pair<int,int>> q;
// 入队起点，dist=0，按方向扩展
```

邻接表建图（最常用图存储）：
```cpp
int n; // 节点数
vector<vector<pair<int,int>>> g(n); // g[u] = {v, w}
g[u].push_back({v, w});
```

---

## 性能与内存贴士
- 大量 push_back 前先 `reserve(k)`，显著减少扩容拷贝。
- 超大数组注意内存；需要时放全局/堆而非栈。
- 需要稳定指针/引用时避免继续 push_back（可能重分配使其失效）；可先 `reserve` 或改用 `list`/`deque`。
- 性能极致且大小固定的 DP 表，C 风格静态数组有时更快（失去灵活性）。

---

## 常见速查片段

一维 DP 初始化为“负无穷/不可达”：
```cpp
const long long NEG = LLONG_MIN/4;
vector<long long> dp(W+1, NEG);
dp[0] = 0;
```

二维 DP 滚动数组：
```cpp
vector<vector<int>> dp(2, vector<int>(m+1, 0));
int cur=0, nxt=1;
for (int i=1; i<=n; ++i) {
  fill(dp[nxt].begin(), dp[nxt].end(), 0);
  // 用 dp[cur] 转移到 dp[nxt]
  swap(cur, nxt);
}
```

访问表：
```cpp
vector<vector<char>> vis(n, vector<char>(m, 0));
```

排序去重 + 二分：
```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
auto it = lower_bound(a.begin(), a.end(), key);
```

---

如果需要，我可以再补：
- 可直接编译运行的小例子（网格输入/BFS、邻接表建图演示）；
- `vector<array<int,2>>` / `vector<pair<int,int>>` 的坐标写法速记；
- `unordered_map<vector<int>, int>` 等高维 key 的哈希技巧。