/*
给你一个非负整数数组nums，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
假设你总是可以到达数组的最后一个位置。

示例1:
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是2。
     从下标为0跳到下标为1的位置，跳1步，然后跳3步到达数组的最后一个位置。

示例2:
输入: nums = [2,3,0,1,4]
输出: 2

提示:
1 <= nums.length <= 10^4
0 <= nums[i] <= 1000
*/

// 动态规划，超过5%，超时边缘
int jump(int* nums, int numsSize) {
  int dp[numsSize];  // 跳的该位置所需要的最小步数
  dp[0] = 0;
  for (int i = 1; i < numsSize; ++i) {
    dp[i] = numsSize + 1;
  }

  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (j + nums[j] >= i) {
        dp[i] = fmin(dp[i], dp[j] + 1);
      }
    }
  }

  return dp[numsSize - 1];
}

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int jump(int* nums, int numsSize) {
  int curDistance = 0;   // 当前覆盖的最远距离下标
  int ans = 0;           // 记录走的最大步数
  int nextDistance = 0;  // 下一步覆盖的最远距离下标
  // 注意这里是小于numsSize-1，这是关键所在
  for (int i = 0; i < numsSize - 1; i++) {
    // 更新下一步覆盖的最远距离下标
    nextDistance = fmax(nums[i] + i, nextDistance);
    if (i == curDistance) {        // 遇到当前覆盖的最远距离下标
      curDistance = nextDistance;  // 更新当前覆盖的最远距离下标
      ans++;
    }
    // printf("i:%d,curDistance:%d,nextDistance,%d\n",i,curDistance,nextDistance);
  }

  // [2,3,1,1,4]
  // i:0,curDistance:2,nextDistance,2
  // i:1,curDistance:2,nextDistance,4
  // i:2,curDistance:4,nextDistance,4
  // i:3,curDistance:4,nextDistance,4

  return ans;
}
