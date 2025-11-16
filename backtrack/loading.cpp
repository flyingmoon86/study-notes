#include<bits/stdc++.h>
using namespace std;
int n;
int pick[100];
int weight[100];

int bestpick[100];
int bestweight;
int rest;
int cur_w=0;

void backtrack(int i)
{
    if(i>n)//leaves
    {
        //bestpick, bestweight
        if(cur_w>bestweight)
        {
            for(int j=1;j<=n;j++)
            {
                bestpick[j]=pick[j];
            }
            bestweight=cur_w;
        }
        return;
    }
    //not pick i
    if(rest+cur_w>bestweight)backtrack(i+1);
    //pick i
    if(rest>=weight[i])
    {
    pick[i]=1;
    rest-=weight[i];
    cur_w+=weight[i];
    backtrack(i+1);
    pick[i]=0;
    rest+=weight[i];
    cur_w-=weight[i];
    }
}
int main()
{
    cin>>n;
    cin>>rest;
    for(int i=1;i<=n;i++)
    {
        cin>>weight[i];
    }
    bestweight=0;
    backtrack(1);
    cout<<"Best weight: "<<bestweight<<endl;
    cout<<"Items picked: ";
    for(int i=1;i<=n;i++)
    {
        if(bestpick[i]==1)cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}