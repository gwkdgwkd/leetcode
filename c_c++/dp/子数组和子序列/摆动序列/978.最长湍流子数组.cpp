/*
给定一个整数数组arr，返回arr的最大湍流子数组的长度。
如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组，
即当arr的子数组A[i],A[i+1],...,A[j]满足仅满足下列条件时，称其为湍流子数组：
若i <= k < j：当k为奇数时，A[k] > A[k+1]，且当k为偶数时，A[k] < A[k+1]；
或若i <= k < j：当k为偶数时，A[k] > A[k+1]，且当k为奇数时，A[k] < A[k+1]。

示例1：
输入：arr = [9,4,2,10,7,8,8,1,9]
输出：5
解释：arr[1] > arr[2] < arr[3] > arr[4] < arr[5]

示例2：
输入：arr = [4,8,12,16]
输出：2

示例3：
输入：arr = [100]
输出：1

提示：
1 <= arr.length <= 4 * 10^4
0 <= arr[i] <= 10^9
*/

// 动态规划
// 和[376.摆动序列]的区别：子序列和子数组
int maxTurbulenceSize(int* arr, int arrSize) {
  // dp[i][0]为以arr[i]结尾，且arr[i−1]>arr[i]的湍流子数组的最大长度；
  // dp[i][1]为以arr[i]结尾，且arr[i−1]<arr[i]的湍流子数组的最大长度。
  int dp[arrSize][2];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < arrSize; i++) {
    dp[i][0] = dp[i][1] = 1;
  }

  int max = 1;
  for (int i = 1; i < arrSize; ++i) {
    if (arr[i - 1] > arr[i]) {
      dp[i][0] = dp[i - 1][1] + 1;
    } else if (arr[i - 1] < arr[i]) {
      dp[i][1] = dp[i - 1][0] + 1;
    }
    max = fmax(max, fmax(dp[i][0], dp[i][1]));
  }

  return max;
}

class Solution {
 public:
  int maxTurbulenceSize(vector<int>& arr) {
    int n = arr.size();

    // dp[i][0]：表示从0到i且nums[i]>nums[i-1]的最大长度
    // dp[i][1]：表示从0到i且nums[i]<nums[i-1]的最大长度
    vector<vector<int>> dp(n, vector<int>(2, 1));

    int m = 1;
    for (int i = 1; i < n; ++i) {
      if (arr[i] > arr[i - 1]) {
        dp[i][0] = dp[i - 1][1] + 1;
      } else if (arr[i] < arr[i - 1]) {
        dp[i][1] = dp[i - 1][0] + 1;
      }
      // else，如果相等，重新计数

      m = max(m, max(dp[i][0], dp[i][1]));
    }

    return m;
  }
};

// 分组循环
class Solution {
 public:
  int maxTurbulenceSize(vector<int>& arr) {
    int n = arr.size();
    int ans = 1, i = 0;  // ans要初始化为1
    while (i < n - 1) {
      if (arr[i + 1] == arr[i]) {  //处理连续相同的元素
        i++;
        continue;
      }
      int start = i;
      i++;
      while (i < n - 1 &&
             (long long)(arr[i + 1] - arr[i]) * (arr[i] - arr[i - 1]) < 0) {
        i++;
      }
      ans = max(ans, i - start + 1);
    }
    return ans;
  }
};
