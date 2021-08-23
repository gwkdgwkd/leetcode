/*
 * @lc app=leetcode.cn id=55 lang=c
 *
 * [55] 跳跃游戏
 */

// @lc code=start

// 贪心法？找能跳的最远距离
bool canJump(int* nums, int numsSize) {
  int longest = 0;

  for (int i = 0; i < numsSize; ++i) {
    longest = fmax(longest, nums[i] + i);
    if (longest >= numsSize - 1) {
      return true;
    }
    if (i >= longest) {
      return false;
    }
  }

  return longest >= numsSize - 1;
}
// @lc code=end
