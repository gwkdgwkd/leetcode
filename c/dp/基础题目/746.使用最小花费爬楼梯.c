/*
给你一个整数数组cost，其中cost[i]是从楼梯第i个台阶向上爬需要支付的费用。
一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为0或下标为1的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。

示例1：
输入：cost = [10,15,20]
输出：15
解释：你将从下标为1的台阶开始。
- 支付15，向上爬两个台阶，到达楼梯顶部。
总花费为15。

示例2：
输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为0的台阶开始。
- 支付1，向上爬两个台阶，到达下标为2的台阶。
- 支付1，向上爬两个台阶，到达下标为4的台阶。
- 支付1，向上爬两个台阶，到达下标为6的台阶。
- 支付1，向上爬一个台阶，到达下标为7的台阶。
- 支付1，向上爬两个台阶，到达下标为9的台阶。
- 支付1，向上爬一个台阶，到达楼梯顶部。
总花费为6。

提示：
2 <= cost.length <= 1000
0 <= cost[i] <= 999
*/

// 剑指OfferII088爬楼梯的最少成本

// 动态规划
int minCostClimbingStairs(int* cost, int costSize) {
  int dp[costSize + 1];
  dp[0] = dp[1] = 0;
  for (int i = 2; i <= costSize; ++i) {
    dp[i] = fmin(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
  }

  for (int i = 0; i <= costSize; ++i) {
    printf("%3d ", dp[i]);
  }
  printf("\n");
  // [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
  // 0   0   1   2   2   3   3   4   4   5   6

  return dp[costSize];
}

int minCostClimbingStairs(int* cost, int costSize) {
  int pre = 0;
  int curr = 0;
  for (int i = 2; i <= costSize; ++i) {
    int tmp = fmin(curr + cost[i - 1], pre + cost[i - 2]);
    pre = curr;
    curr = tmp;
  }

  return curr;
}

int minCostClimbingStairs(int* cost, int costSize) {
  int pre1 = cost[0];
  int pre2 = cost[1];
  int cur;
  for (int i = 2; i < costSize; ++i) {
    cur = fmin(pre1, pre2) + cost[i];
    pre1 = pre2;
    pre2 = cur;
  }

  return fmin(pre1, pre2);
}
