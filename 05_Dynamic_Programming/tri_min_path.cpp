#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

ll MAXn=100;
ll tri[100][100];// triangle array
ll dp[100][100];// dp array to store min path sums
ll rem[100][100];// to reconstruct the path

ll minPathSum(int n) {
    // Initialize the dp array with the last row of the triangle
    for (int j = 0; j < n; ++j) {
        dp[n-1][j] = tri[n-1][j];
        rem[n-1][j] = j; // Initialize rem for the last row
    }

    // Bottom-up calculation of min path sums
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            
            if(dp[i+1][j] <= dp[i+1][j+1]) {
                rem[i][j] = j; // Choose the left child
                dp[i][j] = tri[i][j] + dp[i+1][j];
            } else {
                rem[i][j] = j + 1; // Choose the right child
                dp[i][j] = tri[i][j] + dp[i+1][j+1];
            }
        }
    }

    return dp[0][0]; // The top element contains the minimum path sum
}
void printPath(int n) {
    int j = 0; // Start from the top of the triangle
    cout << "Path: ";
    for (int i = 0; i < n; ++i) {
        cout << tri[i][j] << " ";
        j = rem[i][j]; // Move to the next index in the path
    }
    cout << endl;
}
int main() {
    int n;
    cout << "Enter the number of rows in the triangle: ";
    cin >> n;

    cout << "Enter the triangle values row by row:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> tri[i][j];
        }
    }

    ll result = minPathSum(n);
    cout << "Minimum path sum: " << result << endl;
    printPath(n);

    return 0;
}