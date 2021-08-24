/*
 * @lc app=leetcode.cn id=494 lang=c
 *
 * [494] 目标和
 */

// @lc code=start

// 官方解法，动态规划，压缩dp
int findTargetSumWays(int* nums, int numsSize, int target) {
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  // (sum - seg) - seg = target   =>   seg = (sum - target)/2
  int neg = sum - target;
  if (neg < 0 || neg % 2) {
    return 0;
  }
  neg /= 2;

  int dp[neg + 1];
  for (int i = 1; i <= neg; ++i) {
    dp[i] = 0;
  }
  dp[0] = 1;

  for (int i = 0; i < numsSize; ++i) {
    for (int j = neg; j >= nums[i]; --j) {
      dp[j] += dp[j - nums[i]];
    }
  }

  return dp[neg];
}

// 时间复杂度：O(n×(sum-target))。
// 空间复杂度：O(sum-target)。

// todo:使用二位数组

/*
// 这也算是用01背包的方法进行计算么?
int findTargetSumWays(int* nums, int numsSize, int target) {
  if (numsSize == 1 && nums[0] != target && nums[0] != -target) {
    return 0;
  }

  // 把所有的nums分成两组，一组加+，一组加-，和为target
  // left-right=target && left+right=sum，所以left-(sum-left)=target，即left=(sum+target)/2
  // 所以问题就变成了装满容量为x的背包，有几种方法
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  int dpsize = sum + target;
  if (dpsize % 2) {  // 此时没有方法，直接返回
    return 0;
  }
  dpsize /= 2;

  int dp[dpsize + 1];  // 表示填满j(包括j)这么大容积的背包，有dp[i]种方法
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;  // 装满容量为0的背包，有一种方法，就是装0件物品
  for (int i = 0; i < numsSize; ++i) {
    for (int j = dpsize; j >= nums[i]; --j) {
      // 不考虑nums[i]的情况下，填满容量为j-nums[i]的背包，有dp[j-nums[i]]种方法。
      // 那么只要搞到nums[i]的话，凑成dp[j]就有dp[j-nums[i]]种方法。
      dp[j] += dp[j - nums[i]];
      // 求组合类问题的公式，都与上面的递推公式类似。
    }
  }

  return dp[dpsize];
}
*/

// @lc code=end
