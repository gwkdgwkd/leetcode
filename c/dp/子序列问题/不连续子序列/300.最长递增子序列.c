/*
 * @lc app=leetcode.cn id=300 lang=c
 *
 * [300] 最长递增子序列
 */

// @lc code=start

#include <stdlib.h>

int lengthOfLIS(int *nums, int numsSize) {
  // 1. dp[i]表示i之前包括i的最⻓上升⼦序列。
  int dp[numsSize];
  // 3. dp[i]的初始化：每⼀个i，对应的dp[i]（即最⻓上升⼦序列）起始⼤⼩⾄少都是是1。
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  // 4. 确定遍历顺序：dp[i]是有0到i-1各个位置的最⻓升序⼦序列推导⽽来，那么遍历i⼀定是从前向后遍历。
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        // 2. 状态转移⽅程：位置i的最⻓升序⼦序列等于j从0到i-1各个位置的最⻓升序⼦序列+1的最⼤值。
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);
    }
  }

  return max;
}

// 时间复杂度:O(N^2)。

/* 
#include <stdlib.h>

int lengthOfLIS(int *nums, int numsSize) {
  int *top = (int *)malloc(numsSize * sizeof(int));
  int len = 0;
  for (int i = 0; i < numsSize; ++i) {
    int left = 0, right = len;
    while (left < right) {
      int mid = (left + right) / 2;
      if (top[mid] > nums[i]) {
        right = mid;
      } else if (top[mid] < nums[i]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    if (left == len) ++len;
    top[left] = nums[i];
  }

  return len;
}

// 时间复杂度：O(N *logN)。
*/

// @lc code=end
