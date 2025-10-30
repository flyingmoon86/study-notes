
# 动态规划

- 定义：用有限状态描述重复子问题，通过转移复用计算结果。
- 两个核心：重叠子问题 + 最优子结构。
- 建模要点：明确目标 → 设计最小状态 → 写转移 → 确定边界。
- 时间复杂度估算：状态数 × 每状态转移成本；空间与状态表大小相关，可压缩。
- 当目标是“可达性/最短步数（单位步）”时，优先用状态空间搜索（BFS）；当要“最优值/计数/带权最短”时，用 DP/记忆化或 Dijkstra。

---

## 例：国际象棋——马的最少跳数（Knight shortest path）

题目要点（精简）：200×200 棋盘，给定起点 S(x1,y1) 与终点 T(x2,y2)，求马最少跳数。多组测试。

输入格式：第一行 N（测试数），接下来的 N 行每行 4 个整数 x1 y1 x2 y2（坐标从 1 开始）。

输出：每组输出最少跳数（单行）。

样例：

输入：

2

1 1 2 1

1 5 5 1

输出：
3
4

思路（一句话）：在 200×200 网格上把每个格子视为状态，马有 8 个可能移动方向，对每个测例做 BFS，返回到达目标的层数。

复杂度：每次 BFS 最多访问 200*200 状态，时间 O(200*200)（常数 8），总体 O(N * 200*200)。

参考 C++ 实现：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N; if(!(cin>>N)) return 0;
	const int MAXN = 200;
	int dx[8] = {1,2,2,1,-1,-2,-2,-1};
	int dy[8] = {2,1,-1,-2,-2,-1,1,2};

	while(N--){
		int sx,sy,tx,ty; 
        cin>>sx>>sy>>tx>>ty;
		if(sx==tx && sy==ty){ cout<<0<<"\n"; continue; }//出生在罗马，0步
        //否则，bfs跳的地方
		vector<vector<int>> dist(MAXN+1, vector<int>(MAXN+1, -1));
        //到此地的步数
		queue<pair<int,int>> q;//q为位置
		dist[sx][sy]=0; //初始地为0步
        q.push({sx,sy});
		while(!q.empty()){
		    auto [x,y]=q.front(); 
            q.pop();
            //pop出来挪8个位置，分别检查边界（之前跳过了，没棋盘了都不行
            // dp精髓的剪枝，新的地方距离加1）
			for(int d=0; d<8; ++d){
				int nx=x+dx[d], ny=y+dy[d];
				if(nx<1||nx>MAXN||ny<1||ny>MAXN) continue;
				if(dist[nx][ny]!=-1) continue;
				dist[nx][ny]=dist[x][y]+1;
				if(nx==tx && ny==ty){
					while(!q.empty()) q.pop(); break;//找到目标跳出循环
				}
				q.push({nx,ny});//新的地方入队等待被探索
			}
		}
		cout<<dist[tx][ty]<<"\n";
	}
	return 0;
}
```

注：若棋盘更大或存在障碍，可考虑 A* 或启发式剪枝；若步权不同则用 Dijkstra。

---

备注：你给出的三壶倒水题是状态空间+BFS 的典型例子，与上面马跳问题建模方法相同（都可用 visited/dist 三维/二维表记录状态）。


