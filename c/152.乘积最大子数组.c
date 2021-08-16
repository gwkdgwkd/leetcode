/*
 * @lc app=leetcode.cn id=152 lang=c
 *
 * [152] 乘积最大子数组
 */

// @lc code=start

// 动态规划
int maxProduct(int* nums, int numsSize) {
  int maxF = nums[0], minF = nums[0], ans = nums[0];
  for (int i = 1; i < numsSize; ++i) {
    int mx = maxF, mn = minF;
    maxF = fmax(mx * nums[i], fmax(nums[i], mn * nums[i]));
    minF = fmin(mn * nums[i], fmin(nums[i], mx * nums[i]));
    ans = fmax(maxF, ans);
  }
  return ans;
}

// @lc code=end
