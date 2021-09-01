/*
 * @lc app=leetcode.cn id=376 lang=c
 *
 * [376] 摆动序列
 */

// @lc code=start

/*
// 动态规划
int wiggleMaxLength(int* nums, int numsSize) {
  if (numsSize < 2) {
    return numsSize;
  }
  int up[numsSize], down[numsSize];
  up[0] = down[0] = 1;
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > nums[i - 1]) {
      up[i] = fmax(up[i - 1], down[i - 1] + 1);
      down[i] = down[i - 1];
    } else if (nums[i] < nums[i - 1]) {
      up[i] = up[i - 1];
      down[i] = fmax(up[i - 1] + 1, down[i - 1]);
    } else {
      up[i] = up[i - 1];
      down[i] = down[i - 1];
    }
  }
  return fmax(up[numsSize - 1], down[numsSize - 1]);
}
*/

int wiggleMaxLength(int* nums, int numsSize) {
  // dp[i][0]表示前i个数中最大摆动长度，nums[i−1]>nums[i]；
  // dp[i][1]表示前i个数中最大摆动长度，nums[i−1]<nums[i]。
  int dp[numsSize][2];
  for (int i = 0; i < numsSize; ++i) {
    dp[i][0] = dp[i][1] = 1;
  }

  for (int i = 1; i < numsSize; ++i) {
    if (nums[i - 1] > nums[i]) {
      dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + 1);
    } else if (nums[i - 1] < nums[i]) {
      dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] + 1);
    } else {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1];
    }
  }

  return fmax(dp[numsSize - 1][0], dp[numsSize - 1][1]);
}

int wiggleMaxLength(int* nums, int numsSize) {
  if (numsSize < 2) {
    return numsSize;
  }
  int up = 1, down = 1;
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > nums[i - 1]) {
      up = fmax(up, down + 1);
    } else if (nums[i] < nums[i - 1]) {
      down = fmax(up + 1, down);
    }
  }
  return fmax(up, down);
}

// @lc code=end
