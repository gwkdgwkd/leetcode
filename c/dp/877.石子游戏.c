// 动态规划
bool stoneGame(int* piles, int pilesSize) {
  int dp[pilesSize][pilesSize];
  for (int i = 0; i < pilesSize; i++) {
    dp[i][i] = piles[i];
  }
  for (int i = pilesSize - 2; i >= 0; i--) {
    for (int j = i + 1; j < pilesSize; j++) {
      dp[i][j] = fmax(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
    }
  }
  return dp[0][pilesSize - 1] > 0;
}

// 先手可以选择奇数堆，还是偶数堆，直接赢
bool stoneGame(int* piles, int pilesSize) { return true; }