/*
给你一个整数数组nums，返回nums中最长等差子序列的长度。
nums的子序列是一个列表nums[i1],nums[i2]...nums[ik]，
且0 <= i1 < i2 < ... < ik <= nums.length - 1。
并且如果seq[i+1]-seq[i](0<=i<seq.length-1)的值都相同，
那么序列seq是等差的。

示例1：
输入：nums = [3,6,9,12]
输出：4
解释：
整个数组是公差为3的等差数列。

示例2：
输入：nums = [9,4,7,2,10]
输出：3
解释：
最长的等差子序列是[4,7,10]。

示例 3：
输入：nums = [20,1,15,3,10,5,8]
输出：4
解释：
最长的等差子序列是[20,15,10,5]。

提示：
2 <= nums.length <= 1000
0 <= nums[i] <= 500
*/

#define MAX_NUM 1001  // 最大值乘2
int max(int a, int b) { return a > b ? a : b; }
int longestArithSeqLength(int* A, int ASize) {
  int res = 1;
  int dp[ASize][MAX_NUM];
  for (int i = 0; i < ASize; i++) {
    for (int j = 0; j < MAX_NUM; j++) {
      dp[i][j] = 1;
    }
  }

  for (int i = 0; i < ASize; i++) {
    for (int j = 0; j < i; j++) {
      int diff = A[i] - A[j];
      diff += 500;  // 不考虑负数
      dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
      res = max(res, dp[i][diff]);
    }
  }
  return res;
}

class Solution {
 public:
  int longestArithSeqLength(vector<int>& nums) {
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(1001, 1));
    int ans = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        int diff = nums[i] - nums[j] + 500;
        dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
        ans = max(ans, dp[i][diff]);
      }
    }

    return ans;
  }
};
