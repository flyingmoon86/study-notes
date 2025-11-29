#include<iostream>
#include<vector>
using namespace std;

void maxContSum(const vector<int>& arr) {
    if (arr.empty()) return;

    int maxSum = arr[0];
    int currentSum = arr[0];
    int start = 0;
    int end=0;
    for (size_t i = 1; i < arr.size(); ++i) {
        currentSum = max(arr[i], currentSum + arr[i]);
        maxSum = max(maxSum, currentSum);
        if(currentSum == arr[i]) start = i; // Reset start index when currentSum is just the current element

        if(maxSum == currentSum ) end = i; // Update end index to the current position

    }
    // Optional: Print the subarray with the maximum sum
    cout << "Maximum subarray from index " << start << " to " << end << " is: ";
    for (int j = start; j <= end; ++j) {
        cout << arr[j] << " ";
    }
    cout << endl;
    cout << "Maximum contiguous sum is: " << maxSum << endl;
}
int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    maxContSum(arr);
    return 0;
}