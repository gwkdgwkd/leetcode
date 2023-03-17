/*
给一个二进制字符串数组strs和两个整数m和n，请找出并返回strs的最大子集的长度，
该子集中最多有m个0和n个1，如果x的所有元素也是y的元素，集合x是集合y的子集。

示例1：
输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
输出：4
解释：最多有5个0和3个1的最大子集是{"10","0001","1","0"}，因此答案是4。
     其他满足题意但较小的子集包括{"0001","1"}和{"10","1","0"}。
     {"111001"}不满足题意，因为它含4个1，大于n的值3。

示例2：
输入：strs = ["10", "0", "1"], m = 1, n = 1
输出：2
解释：最大的子集是{"0", "1"}，所以答案是2。

提示：
1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i]仅由'0'和'1'组成
1 <= m, n <= 100
*/

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

// 用01背包的方式计算
int findMaxForm(char** strs, int strsSize, int m, int n) {
  // 不是多重背包，多重背包是每个物品，数量不同的情况
  // strs数组里的元素就是物品，每个物品都是一个！
  // 而m和n相当于一个背包，两个维度的背包。
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
        // c0和c1相当于物品的重量，字符串本身的个数相当于物品的价值，
        // 这就是一个典型的01背包问题，不过物品的重量有两个维度而已。
        dp[j][k] = fmax(dp[j][k], dp[j - c0][k - c1] + 1);
      }
    }
  }

  return dp[m][n];
}

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

class Solution {
 public:
  int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < strs.size(); ++i) {
      int c0 = 0;
      int c1 = 0;
      for (int k = 0; k < strs[i].size(); ++k) {
        if (strs[i][k] == '0') {
          ++c0;
        } else {
          ++c1;
        }
      }

      // 物品是字符串，价值是1，重量是0和1的个数，有2个维度
      for (int j1 = m; j1 >= c0; --j1) {
        for (int j2 = n; j2 >= c1; --j2) {
          dp[j1][j2] = max(dp[j1][j2], dp[j1 - c0][j2 - c1] + 1);
        }
      }
    }
    return dp[m][n];
  }
};
