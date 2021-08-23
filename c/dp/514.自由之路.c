/*
 * @lc app=leetcode.cn id=514 lang=c
 *
 * [514] 自由之路
 */

// @lc code=start

// 官方题解
int findRotateSteps(char* ring, char* key) {
  int n = strlen(ring), m = strlen(key);
  // pos保存ring中各个字母出现的位置，posSize保存ring中各个字母出现的次数
  int pos[26][n], posSize[26];
  memset(posSize, 0, sizeof(posSize));
  for (int i = 0; i < n; ++i) {
    int x = ring[i] - 'a';
    pos[x][posSize[x]++] = i;
  }
  int dp[m][n];
  memset(dp, 0x3f3f3f3f, sizeof(dp));
  // 设置key中第一个字母在ring中移动到12点需要的步数
  for (int i = 0; i < posSize[key[0] - 'a']; i++) {
    int x = pos[key[0] - 'a'][i];
    dp[0][x] = fmin(x, n - x) + 1;
  }
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < posSize[key[i] - 'a']; ++j) {
      int x = pos[key[i] - 'a'][j];
      for (int k = 0; k < posSize[key[i - 1] - 'a']; ++k) {
        int y = pos[key[i - 1] - 'a'][k];
        dp[i][x] =
            fmin(dp[i][x], dp[i - 1][y] + fmin(abs(x - y), n - abs(x - y)) + 1);
      }
    }
  }
  int ret = dp[m - 1][0];
  for (int i = 1; i < n; ++i) {
    ret = fmin(ret, dp[m - 1][i]);
  }
  return ret;
}

// 时间复杂度：O(mn^2)
// 空间复杂度：O(mn)

// @lc code=end
