/*
在两条独立的水平线上按给定的顺序写下nums1和nums2中的整数。
现在，可以绘制一些连接两个数字nums1[i]和nums2[j]的直线，这些直线需要同时满足满足：
nums1[i] == nums2[j]
且绘制的直线不与任何其他连线（非水平线）相交。
请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。
以这种方法绘制线条，并返回可以绘制的最大连线数。

示例1：
输入：nums1 = [1,4,2], nums2 = [1,2,4]
输出：2
解释：可以画出两条不交叉的线。
但无法画出第三条不相交的直线，
因为从nums1[1]=4到nums2[2]=4的直线将与从nums1[2]=2到nums2[1]=2的直线相交。

示例2：
输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
输出：3

示例3：
输入：nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
输出：2

提示：
1 <= nums1.length, nums2.length <= 500
1 <= nums1[i], nums2[j] <= 2000
*/

// 动态规划，与1143（最长公共子序列）是相似问题
// 注意与718的区别：子序列和子数组
// 本题说是求绘制的最⼤连线数，其实就是求两个字符串的最⻓公共⼦序列的⻓度！
int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
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

class Solution {
 public:
  int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (nums1[i - 1] == nums2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }

    return dp[m][n];
  }
};
