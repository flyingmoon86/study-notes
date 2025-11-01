// Avoid <bits/stdc++.h> for better portability on some MinGW versions
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;

/*
Matrix Path Sum (min-sum path, only right/down)
- Input:
  n m
  grid[n][m]
- Output:
  min path sum and one optimal path (0-based coordinates)
- Complexity: O(n*m) time, O(n*m) space (can be reduced to O(m) if no path reconstruction)
*/

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
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

    dp[0][0] = grid[0][0];
    // first row
    for(int j=1;j<m;++j){
        if(dp[0][j-1] != INF){
            dp[0][j] = dp[0][j-1] + grid[0][j];
            parent[0][j] = {0, j-1};
        }
    }
    // first column
    for(int i=1;i<n;++i){
        if(dp[i-1][0] != INF){
            dp[i][0] = dp[i-1][0] + grid[i][0];
            parent[i][0] = {i-1, 0};
        }
    }
    // rest cells
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
    if(ans >= INF/2){ cout << "INF\n"; return 0; }
    cout << ans << "\n";

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
        if(k+1<path.size()) cout << ' ';
    }
    cout << "\n";

    return 0;
}
