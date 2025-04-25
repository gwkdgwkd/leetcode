/*
给一个由n个元素组成的整数数组nums和一个整数k。
请找出平均数最大且长度为k的连续子数组，并输出该最大平均数。
任何误差小于10^-5的答案都将被视为正确答案。

示例1：
输入：nums = [1,12,-5,-6,50,3], k = 4
输出：12.75
解释：最大平均数(12-5-6+50)/4 = 51/4 = 12.75

示例2：
输入：nums = [5], k = 1
输出：5.00000


提示：
n == nums.length
1 <= k <= n <= 10^5
-10^4 <= nums[i] <= 10^4
*/

class Solution {
  // 时间复杂度：O(n)，其中n是nums的长度。
  // 空间复杂度：O(1)，仅用到若干额外变量。
 public:
  double findMaxAverage(vector<int>& nums, int k) {
    int m = INT_MIN;
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];

      if (i < k - 1) {
        continue;
      }
      m = max(m, sum);
      sum -= nums[i - k + 1];
    }
    return (double)m / k;
  }
};

// 官方题解
class Solution {
  // 时间复杂度：O(n)，其中n是数组nums的长度，遍历数组一次。
  // 空间复杂度：O(1)。
 public:
  double findMaxAverage(vector<int>& nums, int k) {
    int sum = 0;
    int n = nums.size();
    for (int i = 0; i < k; i++) {
      sum += nums[i];
    }
    int maxSum = sum;
    for (int i = k; i < n; i++) {
      sum = sum - nums[i - k] + nums[i];
      maxSum = max(maxSum, sum);
    }
    return static_cast<double>(maxSum) / k;
  }
};
