/*
一个下标从0开始的数组的交替和定义为偶数下标处元素之和减去奇数下标处元素之和。
比方说，数组[4,2,5,3]的交替和为(4+5)-(2+3)=4。
给你一个数组nums，请你返回nums中任意子序列的最大交替和（子序列的下标重新从0开始编号）。
一个数组的子序列是从原数组中删除一些元素后（也可能一个也不删除）剩余元素不改变顺序组成的数组。
比方说，[2,7,4]是[4,2,3,7,2,1,4]的一个子序列，但是[2,4,2]不是。

示例1：
输入：nums = [4,2,5,3]
输出：7
解释：最优子序列为[4,2,5]，交替和为(4 + 5) - 2 = 7。

示例2：
输入：nums = [5,6,7,8]
输出：8
解释：最优子序列为[8] ，交替和为8。

示例3：
输入：nums = [6,2,1,2,4,5]
输出：10
解释：最优子序列为[6,1,5]，交替和为(6 + 5) - 1 = 10。

提示：
1 <= nums.length <= 105
1 <= nums[i] <= 105
*/

// 动态规划，模拟股票交易
long long maxAlternatingSum(int* nums, int numsSize) {
  long ans = 0;
  int pre = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] > pre) {  // 价格比原先买入价格高，就卖出一股，并买入
      ans += nums[i] - pre;
      pre = nums[i];
    } else {
      pre = nums[i];  // 如果遇到价格更低的，则换成该天买入
    }
  }
  return ans;
}

long long maxAlternatingSum(int* nums, int numsSize) {
  long long dp[numsSize][2];
  // 1.f[i][0]表示在数组nums[0...i]中选择元素组成子序列，
  //   且最后一个选择的元素下标为奇数时，可以得到的最大交替和
  // 2.f[i][1]表示在数组nums[0...i]中选择元素组成子序列，
  //   且最后一个选择的元素下标为偶数时，可以得到的最大交替和
  // 注意：最大一个选择的元素下标奇偶表示的是在子序列中的下标

  memset(dp, 0, sizeof(dp));

  // nums[0]被选择，下标是0，不是奇数，与定义冲突，所以不选nums[0]，dp[0][0] = 0
  dp[0][0] = 0;
  // nums[0]被选择，下标是0，是偶数，与定义符合，所以选择，dp[0][1] = nums[0]
  dp[0][1] = nums[0];

  for (int i = 1; i < numsSize; ++i) {
    // 1.不选择nums[i]，dp[i][0] = dp[i - 1][0]
    // 2.选择nums[i]，下标是奇数，应该减去，dp[i][0] = dp[i - 1][1] - nums[i]
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] - nums[i]);
    // 1.不选择nums[i]，dp[i][1] = dp[i - 1][1]
    // 2.选择nums[i]，下标是偶数，应该加上，dp[i][1] = dp[i - 1][0] + nums[i]
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] + nums[i]);
  }

  return dp[numsSize - 1][1];
}

// 动态规划
long long maxAlternatingSum(int* nums, int numsSize) {
  long long dp[2];
  dp[0] = 0;
  dp[1] = nums[0];

  for (int i = 1; i < numsSize; ++i) {
    long long temp = dp[0];
    dp[0] = fmax(dp[0], dp[1] - nums[i]);
    dp[1] = fmax(dp[1], temp + nums[i]);
  }

  return dp[1];
}