/*
 * @lc app=leetcode.cn id=1039 lang=c
 *
 * [1039] 多边形三角剖分的最低得分
 */

// @lc code=start

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
// @lc code=end
