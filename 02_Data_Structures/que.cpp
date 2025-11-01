#include<bits/stdc++.h>
using namespace std;

// ============ 模板1: 基础BFS（网格/图最短路） ============
// 时间复杂度: O(V + E)，空间复杂度: O(V)
void bfs_grid() {
    int n, m; // 网格大小
    cin >> n >> m;
    
    vector<string> grid(n);
    for(int i = 0; i < n; i++) cin >> grid[i];
    
    // 方向数组：上下左右
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    // 8方向（国际象棋马）：马走日
    int knight_dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int knight_dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    queue<pair<int,int>> q;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    
    int sx, sy; // 起点
    cin >> sx >> sy;
    
    q.push({sx, sy});
    dist[sx][sy] = 0;
    
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        
        // 遍历4个方向（或8个方向）
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // 边界检查 + 障碍检查 + 未访问检查
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(grid[nx][ny] == '#') continue; // '#'表示障碍
            if(dist[nx][ny] != -1) continue;  // 已访问
            
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    
    // 输出到目标点(tx, ty)的最短距离
    int tx, ty;
    cin >> tx >> ty;
    cout << dist[tx][ty] << endl; // -1表示不可达
}


// ============ 模板2: 状态空间BFS（如倒水问题） ============
void bfs_state() {
    int m, n, k; // 三个容器容量
    cin >> m >> n >> k;
    
    struct State {
        int a, b, c, steps;
    };
    
    queue<State> q;
    map<tuple<int,int,int>, bool> visited; // 或用数组 bool[201][201][201]
    
    q.push({m, 0, 0, 0});
    visited[{m, 0, 0}] = true;
    
    while(!q.empty()) {
        State cur = q.front(); q.pop();
        
        // 检查目标状态
        if(cur.a == m/2 && cur.b == m/2) {
            cout << cur.steps << endl;
            return;
        }
        
        // 枚举所有可能的操作（倒水）
        int cap[3] = {m, n, k};
        int amount[3] = {cur.a, cur.b, cur.c};
        
        for(int from = 0; from < 3; from++) {
            for(int to = 0; to < 3; to++) {
                if(from == to) continue;
                if(amount[from] == 0 || amount[to] == cap[to]) continue;
                
                int pour = min(amount[from], cap[to] - amount[to]);
                int next[3] = {amount[0], amount[1], amount[2]};
                next[from] -= pour;
                next[to] += pour;
                
                auto state = make_tuple(next[0], next[1], next[2]);
                if(!visited[state]) {
                    visited[state] = true;
                    q.push({next[0], next[1], next[2], cur.steps + 1});
                }
            }
        }
    }
    
    cout << -1 << endl; // 无解
}


// ============ 主函数：选择运行哪个模板 ============
int main() {
    // bfs_grid();          // 网格最短路
    // bfs_state();         // 状态空间搜索
    return 0;
}
