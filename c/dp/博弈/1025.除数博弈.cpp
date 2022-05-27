/*
爱丽丝和鲍勃一起玩游戏，他们轮流行动。爱丽丝先手开局。
最初，黑板上有一个数字n。在每个玩家的回合，玩家需要执行以下操作：
选出任一x，满足0 < x < n且n % x == 0。
用n - x替换黑板上的数字n。
如果玩家无法执行这些操作，就会输掉游戏。
只有在爱丽丝在游戏中取得胜利时才返回true。假设两个玩家都以最佳状态参与游戏。

示例1：
输入：n = 2
输出：true
解释：爱丽丝选择1，鲍勃无法进行操作。

示例2：
输入：n = 3
输出：false
解释：爱丽丝选择1，鲍勃也选择1，然后爱丽丝无法进行操作。

提示：1 <= n <= 1000
*/

// 动态规划
bool divisorGame(int n) {
  if (1 == n) {
    return false;
  }
  bool dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[1] = false;
  dp[2] = true;

  for (int i = 3; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (i % j == 0 && !dp[i - j]) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[n];
}

// 数学
bool divisorGame(int n) { return n % 2 == 0; }

class Solution {
 public:
  bool divisorGame(int n) {
    if (n == 1) {
      return false;
    }

    deque<bool> dp(n + 1, false);
    // dp[1] = false;
    dp[2] = true;
    for (int i = 3; i <= n; ++i) {
      for (int j = 1; j < i; ++j) {
        if (i % j == 0 && dp[i - j] == false) {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[n];
  }
};
