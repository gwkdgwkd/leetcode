/*
 * @lc app=leetcode.cn id=718 lang=c
 *
 * [718] 最长重复子数组
 */

// @lc code=start

// 动态规划
int findLength(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  // dp[i][j]：以下标i-1为结尾的A，和以下标j-1为结尾的B，最⻓重复⼦数组⻓度为dp[i][j]
  int dp[nums1Size + 1][nums2Size + 1];
  memset(dp, 0, sizeof(dp));

  int max = 0;
  for (int i = 1; i <= nums1Size; ++i) {
    for (int j = 1; j <= nums2Size; ++j) {
      if (nums1[i - 1] == nums2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        max = fmax(max, dp[i][j]);
      }
    }
  }

  // for (int i = 0; i <= nums1Size; ++i) {
  //   for (int j = 0; j <= nums2Size; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // [1,2,3,2,1],[3,2,1,4,7]
  //   0   0   0   0   0   0
  //   0   0   0   1   0   0
  //   0   0   1   0   0   0
  //   0   1   0   0   0   0
  //   0   0   2   0   0   0
  //   0   0   0   3   0   0

  return max;
}

// @lc code=end
