/*
给定一个非负整数数组nums，你最初位于数组的第一个下标 。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个下标。

示例1：
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳1步，从下标0到达下标1, 然后再从下标1跳3步到达最后一个下标。

示例2：
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为3的位置。但该下标的最大跳跃长度是0，所以永远不可能到达最后一个下标。

提示：
1 <= nums.length <= 3 * 10^4
0 <= nums[i] <= 10^5
*/

// 贪心法？找能跳的最远距离
bool canJump(int* nums, int numsSize) {
  int longest = 0;

  // 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），
  // 整体最优解：最后得到整体最大覆盖范围，看是否能到终点
  for (int i = 0; i < numsSize; ++i) {
    // printf("%d,%d\n",longest,nums[i] + i);
    longest = fmax(longest, nums[i] + i);
    if (longest >= numsSize - 1) {
      return true;
    }
    if (i >= longest) {
      return false;
    }
  }

  // [2,3,1,1,4]
  // 0,2
  // 2,4

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
