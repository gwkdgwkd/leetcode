/*
有一个凸的n边形，其每个顶点都有一个整数值。
给定一个整数数组values，其中values[i]是第i个顶点的值（即顺时针顺序）。
假设将多边形剖分为n-2个三角形，对于每个三角形，该三角形的值是顶点标记的乘积，
三角剖分的分数是进行三角剖分后所有n-2个三角形的值之和。
返回多边形进行三角剖分后可以得到的最低分。

示例1：
输入：values = [1,2,3]
输出：6
解释：多边形已经三角化，唯一三角形的分数为6。

示例2：
输入：values = [3,7,4,5]
输出：144
解释：有两种三角剖分，可能得分分别为：3*7*5 + 4*5*7 = 245，或 3*4*5 + 3*4*7 =144。
     最低分数为144。

示例3：
输入：values = [1,3,1,4,1,5]
输出：13
解释：最低分数三角剖分的得分情况为1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13。

提示：
n == values.length
3 <= n <= 50
1 <= values[i] <= 100
*/

// 动态规划
int minScoreTriangulation(int* values, int valuesSize) {
  int dp[valuesSize][valuesSize];
  memset(dp, 0, sizeof(dp));
  // 遍历方向比较特殊，从左下到右下，斜着遍历
  for (int k = 2; k < valuesSize; k++) {
    for (int i = 0, j = i + k; j < valuesSize; i++, j++) {
      dp[i][j] = 0x7fffffff;
      for (int m = 1; m < k; m++) {
        dp[i][j] = fmin(dp[i][j], dp[i][i + m] + dp[i + m][j] +
                                      values[i + m] * values[i] * values[j]);
        // printf("dp[%d][%d]:%3d,%d[%d],%d[%d],%d[%d]\n", i, j, dp[i][j],
        //        values[i], i, values[i + m], i + m, values[j], j);
      }
    }
  }

  // for (int i = 0; i < valuesSize; ++i) {
  //   for (int j = 0; j < valuesSize; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // [1,3,1,4,1,5]
  // dp[0][2]:  3,1[0],3[1],1[2]
  // dp[1][3]: 12,3[1],1[2],4[3]
  // dp[2][4]:  4,1[2],4[3],1[4]
  // dp[3][5]: 20,4[3],1[4],5[5]
  // dp[0][3]: 24,1[0],3[1],4[3]
  // dp[0][3]:  7,1[0],1[2],4[3]
  // dp[1][4]:  7,3[1],1[2],1[4]
  // dp[1][4]:  7,3[1],4[3],1[4]
  // dp[2][5]: 40,1[2],4[3],5[5]
  // dp[2][5]:  9,1[2],1[4],5[5]
  // dp[0][4]: 10,1[0],3[1],1[4]
  // dp[0][4]:  8,1[0],1[2],1[4]
  // dp[0][4]:  8,1[0],4[3],1[4]
  // dp[1][5]: 24,3[1],1[2],5[5]
  // dp[1][5]: 24,3[1],4[3],5[5]
  // dp[1][5]: 22,3[1],1[4],5[5]
  // dp[0][5]: 37,1[0],3[1],5[5]
  // dp[0][5]: 17,1[0],1[2],5[5]
  // dp[0][5]: 17,1[0],4[3],5[5]
  // dp[0][5]: 13,1[0],1[4],5[5]
  //   0   0   3   7   8  13
  //   0   0   0  12   7  22
  //   0   0   0   0   4   9
  //   0   0   0   0   0  20
  //   0   0   0   0   0   0
  //   0   0   0   0   0   0

  return dp[0][valuesSize - 1];
}

class Solution {
 public:
  int minScoreTriangulation(vector<int>& values) {
    int n = values.size();

    // vector<vector<int>> dp(n,vector<int>(n,0));
    int dp[n][n];  // 比上面快很多
    memset(dp, 0, sizeof(dp));

    for (int i = n - 3; i >= 0; --i) {
      for (int j = i + 2; j < n; ++j) {
        for (int k = i + 1; k < j; ++k) {
          if (dp[i][j] == 0) {
            dp[i][j] = values[i] * values[j] * values[k] + dp[i][k] + dp[k][j];
          } else {
            dp[i][j] = min(dp[i][j], values[i] * values[j] * values[k] +
                                         dp[i][k] + dp[k][j]);
          }
        }
      }
    }

    return dp[0][n - 1];
  }
};
