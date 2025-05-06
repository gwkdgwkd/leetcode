/*
给定一个未经排序的整数数组，找到最长且连续递增的子序列，并返回该序列的长度。
连续递增的子序列可以由两个下标l和r（l<r）确定，
如果对于每个l<=i<r，都有nums[i]<nums[i + 1]，
那么子序列[nums[l],nums[l + 1],...,nums[r - 1],nums[r]]就是连续递增子序列。

示例1：
输入：nums = [1,3,5,4,7]
输出：3
解释：最长连续递增序列是[1,3,5], 长度为3。
     尽管[1,3,5,7]也是升序的子序列，但它不是连续的，因为5和7在原数组里被4隔开。

示例2：
输入：nums = [2,2,2,2,2]
输出：1
解释：最长连续递增序列是[2],长度为1。

提示：
1 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
*/

int findLengthOfLCIS(int* nums, int numsSize) {
  // 1.确定dp数组以及下标的含义
  // dp[i]：以下标i为结尾的数组的连续递增的⼦序列⻓度为dp[i]。
  int dp[numsSize];
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  for (int i = 1; i < numsSize; ++i) {
    // 2.确定递推公式
    // 如果nums[i+1]>nums[i]，那么以i为结尾的数组的连续递增的⼦
    // 序列⻓度⼀定等于以i-1为结尾的数组的连续递增的⼦序列⻓度+1。
    if (nums[i] > nums[i - 1]) {
      dp[i] = dp[i - 1] + 1;
    }
    max = fmax(max, dp[i]);
  }

  return max;
}

int findLengthOfLCIS(int* nums, int numsSize) {
  int dp[numsSize];
  int max = dp[0] = 1;

  for (int i = 1; i < numsSize; ++i) {
    if (nums[i] > nums[i - 1]) {
      dp[i] = dp[i - 1] + 1;
    } else {
      dp[i] = 1;
    }
    max = fmax(max, dp[i]);
  }

  return max;
}

class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> dp(n, 1);
    int max = 1;
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        dp[i] = dp[i - 1] + 1;
        max = std::max(max, dp[i]);
      }
    }

    return max;
  }
};

class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    int n = nums.size();
    int pre = 1;
    int ans = 1;
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++pre;
        ans = max(ans, pre);
      } else {
        pre = 1;
      }
    }

    return ans;
  }
};

// 贪心
class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    int start = 0;
    for (int i = 0; i < n; i++) {
      if (i > 0 && nums[i] <= nums[i - 1]) {
        start = i;
      }
      ans = max(ans, i - start + 1);
    }
    return ans;
  }
};

// 分组循环
class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    int n = nums.size();
    int i = 0, ans = 0;
    while (i < n) {
      int start = i;
      i++;
      while (i < n && nums[i] > nums[i - 1]) i++;
      ans = max(ans, i - start);
    }
    return ans;
  }
};
