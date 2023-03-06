/*
给定一个非负整数数组nums，你最初位于数组的第一个下标。
数组中的每个元素代表你在该位置可以跳跃的最大长度，判断你是否能够到达最后一个下标。

示例1：
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳1步，从下标0到达下标1，
     然后再从下标1跳3步到达最后一个下标。

示例2：
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为3的位置。
     但该下标的最大跳跃长度是0，所以永远不可能到达最后一个下标。

提示：
1 <= nums.length <= 3 * 10^4
0 <= nums[i] <= 10^5
*/

// 贪心法
bool canJump(int* nums, int numsSize) {
  int longest = 0;

  // 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），
  // 整体最优解：最后得到整体最大覆盖范围，看是否能到终点
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

// 动态规划，超时
class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int n = nums.size();
    vector<bool> dp(n, false);
    dp[0] = true;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (dp[j] && j + nums[j] >= i) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[n - 1];
  }
};

// 对于数组中的任意一个位置y，如何判断它是否可以到达？
// 根据题目的描述，只要存在一个位置x，它本身可以到达，
// 并且它跳跃的最大长度为x+nums[x]，这个值大于等于y，
// 即x+nums[x]≥y，那么位置y也可以到达。
// 换句话说，对于每一个可以到达的位置x，
// 它使得x+1,x+2,⋯,x+nums[x]这些连续的位置都可以到达。

// 贪心算法
class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int n = nums.size();
    int longest = 0;
    for (int i = 0; i < n; ++i) {
      // 对于当前遍历到的位置i，如果它在最远可以到达的位置的范围内，
      // 那么就可以从起点通过若干次跳跃到达该位置，
      // 因此可以用x+nums[x]更新最远可以到达的位置：
      longest = max(longest, nums[i] + i);
      // 如果最远可以到达的位置大于等于数组中的最后一个位置，那就说明最后一个位置可达：
      if (longest >= n - 1) {
        return true;
      }
      // i之前没有任何一个位置，可以走到i：
      if (i >= longest) {
        return false;
      }
    }

    return longest >= n - 1;
  }
};
