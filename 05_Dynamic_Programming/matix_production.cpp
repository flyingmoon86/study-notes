#include <iostream>
#include <climits>

using namespace std;

const int MAX = 105;
int p[MAX], dp[MAX][MAX], s[MAX][MAX];

int main() {
    int n; // n = 矩阵数量
    if (!(cin >> n)) return 0;
    // 对于 n 个矩阵，需要 n+1 个维度值 p[0..n]
    for (int i = 0; i <= n; ++i) {
        if (!(cin >> p[i])) return 0;
    }

    // 初始化
    for (int i = 0; i < n; ++i) dp[i][i] = 0;
    
    // 枚举链长度
    for (int len = 2; len <= n; ++len) {// len表示子链长度，第一层循环控制规模
        for (int i = 0; i < n - len + 1; ++i) {// i表示子链起点，第二次循环控制起点
            int j = i + len - 1;      // j表示子链终点，根据起点和长度计算终点
            // 初始化为无穷大
            dp[i][j] = INT_MAX;
            s[i][j] = i;
            // 枚举分割点
            for (int k = i; k < j; ++k) {// k表示分割点，第三层循环控制分割点
                // 计算代价
                int cost = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                // 更新最小代价
                if (cost < dp[i][j]){
                    dp[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}