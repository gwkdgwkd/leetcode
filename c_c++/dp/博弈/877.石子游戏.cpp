/*
Alice和Bob用几堆石子在做游戏。
一共有偶数堆石子，排成一行；每堆都有正整数颗石子，数目为piles[i]。
游戏以谁手中的石子最多来决出胜负。
石子的总数是奇数，所以没有平局。
Alice和Bob轮流进行，Alice先开始。
每回合，玩家从行的开始或结束处取走整堆石头。
这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
假设Alice和Bob都发挥出最佳水平，
当Alice赢得比赛时返回true，当Bob赢得比赛时返回false。

示例1：
输入：piles = [5,3,4,5]
输出：true
解释：
Alice先开始，只能拿前5颗或后5颗石子 。
假设他取了前5颗，这一行就变成了[3,4,5]。
如果Bob拿走前3颗，那么剩下的是[4,5]，Alice拿走后5颗赢得10分。
如果Bob拿走后5颗，那么剩下的是[3,4]，Alice拿走后4颗赢得9分。
这表明，取前5颗石子对Alice来说是一个胜利的举动，所以返回true。

示例2：
输入：piles = [3,7,2,3]
输出：true

提示：
2 <= piles.length <= 500
piles.length是偶数
1 <= piles[i] <= 500
sum(piles[i])是奇数
*/

// 动态规划
bool stoneGame(int* piles, int pilesSize) {
  // dp[i][j]表示当剩下的石子堆为[i,j]时，
  // 当前玩家与另一个玩家的石子数量之差的最大值
  int dp[pilesSize][pilesSize];
  for (int i = 0; i < pilesSize; i++) {
    // 当i=j时，只剩下一堆石子，当前玩家只能取走这堆石子
    dp[i][i] = piles[i];
  }
  for (int i = pilesSize - 2; i >= 0; i--) {   // 从底向上
    for (int j = i + 1; j < pilesSize; j++) {  // 从左向右
      // 当i<j时，当前玩家可以选择取走piles[i]或piles[j]，
      // 然后轮到另一个玩家在剩下的石子堆中取走石子。
      // dp[i][j]先手获得piles[i]，另一个玩家从i+1到j中选，
      // 会获得dp[i+1][j]，相减就是此轮两人的差值；
      // dp[i][j]先手获得piles[j]，另一个玩家从i到j-1中选，
      // 会获得dp[i][j-1]，相减就是此轮两人的差值；
      dp[i][j] = fmax(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
    }
  }
  return dp[0][pilesSize - 1] > 0;
}

// 先手可以选择奇数堆，还是偶数堆，直接赢
bool stoneGame(int* piles, int pilesSize) { return true; }

class Solution {
 public:
  bool stoneGame(vector<int>& piles) {
    int n = piles.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = piles[i];
    }

    for (int i = n - 2; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        dp[i][j] = fmax(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
      }
    }
    return dp[0][n - 1] > 0;
  }
};