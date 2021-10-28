/*
 * @lc app=leetcode.cn id=55 lang=c
 *
 * [55] 跳跃游戏
 */

// @lc code=start

// 贪心法？找能跳的最远距离
bool canJump(int* nums, int numsSize) {
  int longest = 0;

  // 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点
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

// 贪心算法
bool canJump(int* nums, int numsSize) {
  int cover = 0;
  if (numsSize == 1) return true;     // 只有一个元素，就是能达到
  for (int i = 0; i <= cover; i++) {  // 注意这里是小于等于cover
    cover = fmax(i + nums[i], cover);
    if (cover >= numsSize - 1) return true;  // 说明可以覆盖到终点了
  }
  return false;
}
// @lc code=end
