/*
给你一个由无重复正整数组成的集合nums，请你找出并返回其中最大的整除子集answer，
子集中每一元素对(answer[i], answer[j])都应当满足：
answer[i] % answer[j] == 0，或answer[j] % answer[i] == 0
如果存在多个有效解子集，返回其中任何一个均可。

示例1：
输入：nums = [1,2,3]
输出：[1,2]
解释：[1,3]也会被视为正确答案。

示例2：
输入：nums = [1,2,4,8]
输出：[1,2,4,8]

提示：
1 <= nums.length <= 1000
1 <= nums[i] <= 2 * 109
nums中的所有整数互不相同
*/

// 动态规划
int cmp(int* a, int* b) { return *a - *b; }
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
  int len = numsSize;
  qsort(nums, numsSize, sizeof(int), cmp);

  // 第1步：动态规划找出最大子集的个数、最大子集中的最大整数
  int dp[len];
  for (int i = 0; i < len; i++) {
    dp[i] = 1;
  }
  int maxSize = 1;
  int maxVal = dp[0];
  for (int i = 1; i < len; i++) {
    for (int j = 0; j < i; j++) {
      // 题目中说「没有重复元素」很重要
      if (nums[i] % nums[j] == 0) {
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
    }

    if (dp[i] > maxSize) {
      maxSize = dp[i];
      maxVal = nums[i];
    }
  }

  // 第2步：倒推获得最大子集
  int* res = malloc(sizeof(int) * len);
  *returnSize = 0;
  if (maxSize == 1) {
    res[(*returnSize)++] = nums[0];
    return res;
  }

  for (int i = len - 1; i >= 0 && maxSize > 0; i--) {
    if (dp[i] == maxSize && maxVal % nums[i] == 0) {
      res[(*returnSize)++] = nums[i];
      maxVal = nums[i];
      maxSize--;
    }
  }
  return res;
}
