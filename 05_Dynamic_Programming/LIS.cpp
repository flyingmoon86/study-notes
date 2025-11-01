#include <bits/stdc++.h>
using namespace std;

// nlogn

int main(){
   
    int n; 
    if(!(cin >> n)) return 0;
    vector<long long> a(n);
    for(int i=0;i<n;++i) cin >> a[i];

    vector<long long> tails; // tails[k] = 长度为 k+1 的最小末尾
    for(long long x : a){
        // 对严格递增，找第一个 >= x 的位置
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if(it == tails.end()){
            // x 比所有结尾都大，可以接在最长后面，LIS 长度+1
            tails.push_back(x);
        }else{
            // 用更小的 x 替换这个长度的末尾，利于后续延长
            *it = x;
        }
    }
    cout << (int)tails.size() << "\n"; // 即 LIS 的长度
    return 0;
}