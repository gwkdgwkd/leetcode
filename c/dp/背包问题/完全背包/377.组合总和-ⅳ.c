/*
给你一个由不同整数组成的数组nums，和一个目标整数target。
请你从nums中找出并返回总和为target的元素组合的个数。
题目数据保证答案符合32位整数范围。

示例1：
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。

示例2：
输入：nums = [9], target = 3
输出：0

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums中的所有元素互不相同
1 <= target <= 1000

进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？
如果允许负数出现，需要向题目中添加哪些限制条件？
*/

// 求装满背包有⼏种⽅法，递归公式都是⼀样的，没有什么差别，但关键在于遍历顺序！
// 本题与518.零钱兑换II就是⼀个鲜明的对⽐，⼀个是求排列，⼀个是求组合，遍历顺序完全不同。
// 如果本题要把排列都列出来的话，只能使⽤回溯算法暴搜。

// 完全背包，装满的排列数
int combinationSum4(int* nums, int numsSize, int target) {
  unsigned int dp[target + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int j = 0; j <= target; ++j) {
    for (int i = 0; i < numsSize; ++i) {
      if (j >= nums[i]) {
        dp[j] += dp[j - nums[i]];
      }
    }
  }

  return dp[target];
}
