/*
 * @lc app=leetcode.cn id=300 lang=c
 *
 * [300] 最长递增子序列
 */

// @lc code=start

#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int lengthOfLIS(int *nums, int numsSize) {
  int *dp = (int *)malloc(numsSize * sizeof(int));
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
  }
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        dp[i] = MAX(dp[i], dp[j] + 1);
      }
    }
  }

  int max = dp[0];
  for (int i = 1; i < numsSize; ++i) {
    max = MAX(max, dp[i]);
  }

  free(dp);

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
