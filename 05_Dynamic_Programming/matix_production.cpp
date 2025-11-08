#include <iostream>

using namespace std;

const int MAX = 105;
int p[MAX], dp[MAX][MAX];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i - 1] >> p[i];  // 第i个矩阵是 p[i-1] x p[i]
    }

    // 初始化
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;

    // 枚举链长度
    for (int len = 2; len <= n; ++len) {// len表示子链长度，第一层循环控制规模
        for (int i = 1; i <= n - len + 1; ++i) {// i表示子链起点，第二次循环控制起点
            int j = i + len - 1;      // j表示子链终点，根据起点和长度计算终点
            // 初始化为无穷大
            dp[i][j] = INT_MAX;
            // 枚举分割点
            for (int k = i; k < j; ++k) {// k表示分割点，第三层循环控制分割点
                // 计算代价
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                // 更新最小代价
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    cout << dp[1][n] << endl;
    return 0;
}