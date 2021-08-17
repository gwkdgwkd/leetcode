/*
 * @lc app=leetcode.cn id=368 lang=c
 *
 * [368] 最大整除子集
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
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

// @lc code=end
