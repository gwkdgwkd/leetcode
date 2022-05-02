/*
假如有一排房子，共n个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，
你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。
每个房子粉刷成不同颜色的花费是以一个nx3的正整数矩阵costs来表示的。
例如，costs[0][0]表示第0号房子粉刷成红色的成本花费；
costs[1][2]表示第1号房子粉刷成绿色的花费，以此类推。
请计算出粉刷完所有房子最少的花费成本。

示例1：
输入: costs = [[17,2,17],[16,16,5],[14,3,19]]
输出: 10
解释: 将0号房子粉刷成蓝色，1号房子粉刷成绿色，2号房子粉刷成蓝色。
     最少花费: 2 + 5 + 3 = 10。

示例2：
输入: costs = [[7,6,2]]
输出: 2

提示:
costs.length == n
costs[i].length == 3
1 <= n <= 100
1 <= costs[i][j] <= 20

注意：本题与256题相同
*/

// 动态规划
int minCost(int** costs, int costsSize, int* costsColSize) {
  int dp[costsSize][3];
  dp[0][0] = costs[0][0];
  dp[0][1] = costs[0][1];
  dp[0][2] = costs[0][2];

  for (int i = 1; i < costsSize; ++i) {
    dp[i][0] = fmin(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
    dp[i][1] = fmin(dp[i - 1][0], dp[i - 1][2]) + costs[i][1];
    dp[i][2] = fmin(dp[i - 1][0], dp[i - 1][1]) + costs[i][2];
  }

  return fmin(fmin(dp[costsSize - 1][0], dp[costsSize - 1][1]),
              dp[costsSize - 1][2]);
}

// 压缩dp
int minCost(int** costs, int costsSize, int* costsColSize) {
  int rpre = costs[0][0];
  int bpre = costs[0][1];
  int gpre = costs[0][2];

  for (int i = 1; i < costsSize; ++i) {
    int rcurr = fmin(bpre, gpre) + costs[i][0];
    int bcurr = fmin(rpre, gpre) + costs[i][1];
    int gcurr = fmin(rpre, bpre) + costs[i][2];
    rpre = rcurr;
    bpre = bcurr;
    gpre = gcurr;
  }

  return fmin(fmin(rpre, bpre), gpre);
}