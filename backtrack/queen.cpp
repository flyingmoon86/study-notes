#include<bits/stdc++.h>
using namespace std;
int sum=0;
int n;
int queens[15]; // queens[i] = j 表示第 i 行的皇后放在第 j 列
bool PlaceQueen(int k) {
    for(int j = 1; j < k; ++j) {
        if (queens[j] == queens[k] || abs(queens[k] - queens[j]) == abs(k - j)) {
            return false; //same diagonal
        }
    }
    return true;
}

void SolveNQueens(int t) {
    if(t>n){
        //output first 3 solutions
        if(sum<3){
            for(int i=1;i<=n;i++){  
                cout<<queens[i]<<" ";
            }
            cout<<endl;
        }
        sum++;
        return;
    }
    for(int i=t;i<=n;i++){
        swap(queens[t], queens[i]);
        if(PlaceQueen(t)) {
            SolveNQueens(t+1);
        }
        swap(queens[t], queens[i]);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)queens[i]=i;//initialize

    SolveNQueens(1);//start from row 1

    cout<<sum<<endl;
    return 0;
}