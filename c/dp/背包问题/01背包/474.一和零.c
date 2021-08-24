/*
 * @lc app=leetcode.cn id=474 lang=c
 *
 * [474] 一和零
 */

// @lc code=start

/*
// 动态规划
int findMaxForm(char** strs, int strsSize, int m, int n) {
  int dp[strsSize + 1][m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= strsSize; ++i) {
    int c0 = 0;
    int c1 = 0;
    for (int s = 0; s < strlen(strs[i - 1]); ++s) {
      if (strs[i - 1][s] - '0') {
        ++c1;
      } else {
        ++c0;
      }
    }
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k <= n; ++k) {
        dp[i][j][k] = dp[i - 1][j][k];
        if (j >= c0 && k >= c1) {
          dp[i][j][k] = fmax(dp[i][j][k], dp[i - 1][j - c0][k - c1] + 1);
        }
      }
    }
  }

  return dp[strsSize][m][n];
}
*/

/*
// 用01背包的方式计算
int findMaxForm(char** strs, int strsSize, int m, int n) {
  // 不是多重背包，多重背包是每个物品，数量不同的情况
  // strs数组里的元素就是物品，每个物品都是一个！而m和n相当于一个背包，两个维度的背包。
  // dp[i][j]:最多有i个0和j个1的strs的最大子集的大小为dp[i][j]。
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));  // 物品的价值不会是负数，初始化为0。

  for (int i = 0; i < strsSize; ++i) {
    int c0 = 0;
    int c1 = 0;
    int len = strlen(strs[i]);
    for (int s = 0; s < len; ++s) {
      if (strs[i][s] == '0') {
        ++c0;
      } else {
        ++c1;
      }
    }
    // 遍历物品重量两个维度的顺序可变
    for (int j = m; j >= c0; --j) {
      for (int k = n; k >= c1; --k) {
        // c0和c1相当于物品的重量，字符串本身的个数相当于物品的价值，这就是一个典型的01背包问题，不过物品的重量有两个维度而已。
        dp[j][k] = fmax(dp[j][k], dp[j - c0][k - c1] + 1);
      }
    }
  }

  return dp[m][n];
}
*/

// 压缩dp
int findMaxForm(char** strs, int strsSize, int m, int n) {
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= strsSize; ++i) {
    int c0 = 0;
    int c1 = 0;
    for (int s = 0; s < strlen(strs[i - 1]); ++s) {
      if (strs[i - 1][s] - '0') {
        ++c1;
      } else {
        ++c0;
      }
    }
    for (int j = m; j >= 0; --j) {
      for (int k = n; k >= 0; --k) {
        if (j >= c0 && k >= c1) {
          dp[j][k] = fmax(dp[j][k], dp[j - c0][k - c1] + 1);
        }
      }
    }
  }

  return dp[m][n];
}

// @lc code=end
