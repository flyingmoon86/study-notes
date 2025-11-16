#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1 << 10) + 10;
int board[MAXN][MAXN];
int tiles=1;
void chessboard(int tr,int tc,int dr,int dc,int size){
    if(size==1){
        return;
    }
    int t=tiles++;
    int s=size/2;
    //top-left
    if(dr<tr+s && dc<tc+s){
        chessboard(tr,tc,dr,dc,s);
    }
    else{
        board[tr+s-1][tc+s-1]=t;
        chessboard(tr,tc,tr+s-1,tc+s-1,s);//特殊的方格变成了填的方格
    }
    //top-right
    if(dr<tr+s && dc>=tc+s){
        chessboard(tr,tc+s,dr,dc,s);
    }
    else{
        board[tr+s-1][tc+s]=t;
        chessboard(tr,tc+s,tr+s-1,tc+s,s);
    }
    //bottom-left
    if(dr>=tr+s && dc<tc+s){
        chessboard(tr+s,tc,dr,dc,s);
    }
    else{
        board[tr+s][tc+s-1]=t;
        chessboard(tr+s,tc,tr+s,tc+s-1,s);
    }
    //bottom-right
    if(dr>=tr+s && dc>=tc+s){
        chessboard(tr+s,tc+s,dr,dc,s);
    }
    else{
        board[tr+s][tc+s]=t;
        chessboard(tr+s,tc+s,tr+s,tc+s,s);//特殊的方格变成了填的方格
    }
}
int main(){
    int k,x,y;
    cin>>k;
    cin>>x>>y;
    int size=1<<k; //2^k
    chessboard(0,0,x-1,y-1,size);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}