/*
一个机器人位于一个mxn网格的左上角，机器人每次只能向下或者向右移动一步，
机器人试图达到网格的右下角，问总共有多少条不同的路径？

示例1：
输入：m = 3，n = 7
输出：28

示例2：
输入：m = 3，n = 2
输出：3
解释：
从左上角开始，总共有3条路径可以到达右下角。
1.向右 -> 向下 -> 向下
2.向下 -> 向下 -> 向右
3.向下 -> 向右 -> 向下

示例3：
输入：m = 7, n = 3
输出：28

示例4：
输入：m = 3, n = 3
输出：6

提示：
1 <= m, n <= 100
题目数据保证答案小于等于2*10^9
*/

// 剑指OfferII098路径的数目

// 组合计算
// 从左上角到右下角的过程中，需要移动m+n−2次，其中有m−1次向下移动，n−1次向右移动。
// 因此路径的总数，就等于从m+n−2次移动中选择m−1次向下移动的方案数，即组合数。
int uniquePaths(int m, int n) {
  long long ans = 1;
  for (int x = n, y = 1; y < m; ++x, ++y) {
    ans = ans * x / y;
  }
  return ans;
}

// 动态规划
int uniquePaths(int m, int n) {
  int dp[m][n];                  // 从start到dp[i][j]的路径
  for (int i = 0; i < m; ++i) {  // 只能向下，所以路径是1
    dp[i][0] = 1;
  }
  for (int j = 1; j < n; ++j) {  // 只能向右，所以路径是1
    dp[0][j] = 1;
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
    }
  }

  return dp[m - 1][n - 1];
}

class Solution {
 public:
  int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }

    return dp[m - 1][n - 1];
  }
};
