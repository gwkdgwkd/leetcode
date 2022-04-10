/*
给两个整数数组nums1和nums2，返回两个数组中公共的 、长度最长的子数组的长度。

示例1：
输入：nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
输出：3
解释：长度最长的公共子数组是[3,2,1] 。

示例2：
输入：nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
输出：5

提示：
1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 100
*/

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
