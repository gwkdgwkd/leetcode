/*
一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金，
影响偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算不触动警报装置的情况下，
一夜之内能够偷窃到的最高金额。

示例1：
输入：[1,2,3,1]
输出：4
解释：偷窃1号房屋(金额 = 1)，然后偷窃3号房屋(金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4。

示例2：
输入：[2,7,9,3,1]
输出：12
解释：偷窃1号房屋(金额 = 2)，偷窃3号房屋(金额 = 9)，
     接着偷窃5号房屋(金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12。

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 400
*/

// 剑指OfferII089房屋偷盗
// 面试题1716按摩师

// 动态规划
int rob1(int* nums, int numsSize) {
  if (numsSize == 0) {
    return numsSize;
  }
  if (numsSize == 1) {
    return nums[0];
  }

  // dp[i]：i（包括i）以内的房屋，最多可以偷窃的⾦额为dp[i]。
  int dp[numsSize];
  memset(dp, 0, sizeof(dp));
  dp[0] = nums[0];
  dp[1] = fmax(nums[0], nums[1]);

  for (int i = 2; i < numsSize; ++i) {
    // 如果偷第i房间，那么dp[i]=dp[i-2]+nums[i]，
    // 第i-1房⼀定是不考虑的，找出下标i-2（包括i-2）以内的房屋，
    // 最多可以偷窃的⾦额为dp[i-2]加上第i房间偷到的钱。
    // 如果不偷第i房间，那么dp[i]=dp[i-1]，即考虑i-1房。
    dp[i] = fmax(dp[i - 1], dp[i - 2] + nums[i]);
  }

  return dp[numsSize - 1];
}

// 压缩dp
int rob2(int* nums, int numsSize) {
  if (numsSize == 0) {
    return numsSize;
  }
  if (numsSize == 1) {
    return nums[0];
  }

  int pre1 = nums[0];
  int pre2 = fmax(nums[1], nums[0]);

  for (int i = 2; i < numsSize; ++i) {
    int curr = fmax(pre2, pre1 + nums[i]);
    pre1 = pre2;
    pre2 = curr;
  }

  return pre2;
}

class Solution {
 public:
  int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
      return nums[0];
    }
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; ++i) {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[n - 1];
  }
};
