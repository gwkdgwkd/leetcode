/*
给你一个整数数组nums，找到其中最长严格递增子序列的长度。
子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7]是数组[0,3,1,6,2,2,7]的子序列。

示例1：
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是[2,3,7,101]，因此长度为4。

示例2：
输入：nums = [0,1,0,3,2,3]
输出：4

示例3：
输入：nums = [7,7,7,7,7,7,7]
输出：1

提示：
1 <= nums.length <= 2500
-104 <= nums[i] <= 104

进阶：你能将算法的时间复杂度降低到O(nlog(n))吗?
*/

// 时间复杂度:O(N^2)
int lengthOfLIS(int *nums, int numsSize) {
  // 1.dp[i]表示i之前包括i的最⻓上升⼦序列
  int dp[numsSize];
  // 3.dp[i]的初始化：每⼀个i，对应的dp[i]（即最⻓上升⼦序列）起始⼤⼩⾄少都是是1
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  // 4.确定遍历顺序：dp[i]是有0到i-1各个位置的最⻓升序⼦序列推导⽽来，那么遍历i⼀定是从前向后遍历
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        // 2.状态转移⽅程：位置i的最⻓升序⼦序列等于j从0到i-1各个位置的最⻓升序⼦序列+1的最⼤值
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);  // 放到if里面也可以
    }
  }

  return max;
}

// 时间复杂度：O(N *logN)
int lengthOfLIS(int *nums, int numsSize) {
  // 长度为i+1的所有上升子序列的结尾的最小值
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
