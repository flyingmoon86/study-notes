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