# 矩阵路径和（Matrix Path Sum）

- 目标：在 n×m 的非负权网格中，从 (0,0) 走到 (n-1,m-1)，每步只能向右或向下，求经过格子权值之和的最小值（或最大值）。
- 状态：dp[i][j] = 到达 (i,j) 的最优路径和。
- 转移：dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])（最大值则改为 max）。
- 边界：
  - dp[0][0] = grid[0][0]
  - 第一行只能从左来：dp[0][j] = grid[0][j] + dp[0][j-1]
  - 第一列只能从上来：dp[i][0] = grid[i][0] + dp[i-1][0]
- 复杂度：时间 O(n·m)，空间 O(n·m)；可用滚动数组降到 O(m)。
- 可选：记录父指针可还原一条最优路径。

## 常见变体
- 含障碍：将障碍视为不可达，初始化为 +INF；注意起点/终点不可达直接返回不可达。
- 允许向右/下以外的方向（如上/左）：可能引入环，DP 不再适用，需要图最短路（Dijkstra/Bellman-Ford）。
- 权值为负：若存在负环，最短路无定义；若仅非正需用最短路算法而非此 DP 模板。

## 边界与坑
- 空矩阵、n 或 m 为 0 的输入要提前返回。
- 数值可能溢出，使用 64 位整型（long long）。
- 重建路径时要保证父指针与转移一致。

## 参考代码（C++，含路径重建）

输入：
- 第一行：n m
- 接下来 n 行：每行 m 个整数，表示 grid

输出：
- 第一行：最小路径和
- 第二行：一条最优路径（按坐标 0-based 列出）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m; 
	if(!(cin >> n >> m)) return 0;
	if(n<=0 || m<=0){ cout << 0 << "\n"; return 0; }

	vector<vector<long long>> grid(n, vector<long long>(m));
	for(int i=0;i<n;++i) for(int j=0;j<m;++j) cin >> grid[i][j];

	const long long INF = (1LL<<62);
	vector<vector<long long>> dp(n, vector<long long>(m, INF));
	vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));//记录来时路

	dp[0][0] = grid[0][0];

	// 第一行
	for(int j=1;j<m;++j){
		if(dp[0][j-1] != INF){
			dp[0][j] = dp[0][j-1] + grid[0][j];
			parent[0][j] = {0, j-1};
		}
	}
	// 第一列
	for(int i=1;i<n;++i){
		if(dp[i-1][0] != INF){
			dp[i][0] = dp[i-1][0] + grid[i][0];
			parent[i][0] = {i-1, 0};
		}
	}
	// 其余
	for(int i=1;i<n;++i){
		for(int j=1;j<m;++j){
			long long from_up = dp[i-1][j];
			long long from_left = dp[i][j-1];
			if(from_up <= from_left){
				dp[i][j] = from_up + grid[i][j];
				parent[i][j] = {i-1, j};
			}else{
				dp[i][j] = from_left + grid[i][j];
				parent[i][j] = {i, j-1};
			}
		}
	}

	long long ans = dp[n-1][m-1];
	if(ans >= INF/2){ cout << "INF\n"; return 0; } // 不可达
	cout << ans << "\n";

	// 回溯一条最优路径（0-based 坐标）
	vector<pair<int,int>> path;
	int x=n-1, y=m-1;
	while(x!=-1 && y!=-1){
		path.push_back({x,y});
		auto p = parent[x][y];
		tie(x,y) = p;
	}
	reverse(path.begin(), path.end());

	for(size_t k=0;k<path.size();++k){
		cout << "(" << path[k].first << "," << path[k].second << ")";
		if(k+1<path.size()) cout << " ";
	}
	cout << "\n";

	return 0;
}
```

## 空间优化（思路）
- 使用两行滚动数组：`vector<vector<long long>> dp(2, vector<long long>(m, INF));`
- 转移时仅依赖“上一行同列”和“当前行上一列”。
- 若不需要路径重建，空间可降为 O(m)。

