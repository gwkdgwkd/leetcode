/*
给你一个整数数组nums，你可以对它进行一些操作。
每次操作中，选择任意一个nums[i]，删除它并获得nums[i]的点数。
之后，你必须删除所有等于nums[i] - 1和nums[i] + 1的元素。
开始你拥有0个点数。返回你能通过这些操作获得的最大点数。

示例1：
输入：nums = [3,4,2]
输出：6
解释：
删除4获得4个点数，因此3也被删除。
之后，删除2获得2个点数。总共获得6个点数。

示例2：
输入：nums = [2,2,3,3,3,4]
输出：9
解释：
删除3获得3个点数，接着要删除两个2和4。
之后，再次删除3获得3个点数，再次删除3获得3个点数。
总共获得9个点数。

提示：
1 <= nums.length <= 2 * 10^4
1 <= nums[i] <= 10^4
*/

// 动态规划，和打家劫舍相似
int deleteAndEarn(int* nums, int numsSize) {
  if (numsSize == 1) {
    return nums[0];
  }
  int max = 0;
  for (int i = 0; i < numsSize; ++i) {
    max = fmax(max, nums[i]);
  }

  int sum[max + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 0; i < numsSize; ++i) {
    sum[nums[i]] += nums[i];
  }

  int dp[max + 1];  // 可以压缩
  memset(dp, 0, sizeof(dp));
  dp[0] = sum[0];
  dp[1] = fmax(sum[0], sum[1]);
  for (int i = 2; i <= max; ++i) {
    dp[i] = fmax(dp[i - 1], dp[i - 2] + sum[i]);
  }
  // for (int i = 0; i <= max; ++i) {
  //   printf("%d ", sum[i]);
  // }
  // printf("\n");
  // for (int i = 0; i <= max; ++i) {
  //   printf("%d ", dp[i]);
  // }
  // printf("\n");
  // [2,2,3,3,3,4]
  // 0 0 4 9 4
  // 0 0 4 9 9

  return dp[max];
}

class Solution {
 public:
  int deleteAndEarn(vector<int>& nums) {
    int m = 0;
    for (auto& i : nums) {
      m = max(m, i);
    }

    vector<int> sum(m + 1, 0);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      sum[nums[i]] += nums[i];
    }

    vector<int> dp(m + 1, 0);
    dp[0] = sum[0];
    dp[1] = max(sum[0], sum[1]);

    for (int i = 2; i <= m; ++i) {
      dp[i] = fmax(dp[i - 1], dp[i - 2] + sum[i]);
    }

    return dp[m];
  }
};
