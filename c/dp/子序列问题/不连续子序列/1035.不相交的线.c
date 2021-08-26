/*
 * @lc app=leetcode.cn id=1035 lang=c
 *
 * [1035] 不相交的线
 */

// @lc code=start

// 动态规划
int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  // 与1143（最长公共子序列）是相似问题
  // 注意与718的区别：子序列和子数组
  // 本题说是求绘制的最⼤连线数，其实就是求两个字符串的最⻓公共⼦序列的⻓度！
  int dp[nums1Size + 1][nums2Size + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= nums1Size; ++i) {
    for (int j = 1; j <= nums2Size; ++j) {
      if (nums1[i - 1] == nums2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  // for (int i = 0; i <= nums1Size; ++i) {
  //   for (int j = 0; j <= nums2Size; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // [1,4,2] [1,2,4]
  //  0   0   0   0
  //  0   1   1   1
  //  0   1   1   2
  //  0   1   2   2

  return dp[nums1Size][nums2Size];
}

// @lc code=end
