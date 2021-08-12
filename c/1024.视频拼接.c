/*
 * @lc app=leetcode.cn id=1024 lang=c
 *
 * [1024] 视频拼接
 */

// @lc code=start

/*
// 动态规划，官方题解
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
  int dp[time + 1];  // dp[i]表示从时间0到i所需要的最少视频
  memset(dp, 0x3f, sizeof(dp));  // 默认为比较大的值
  dp[0] = 0;

  for (int i = 1; i <= time; ++i) {
    for (int j = 0; j < clipsSize; ++j) {
      if (clips[j][0] < i && i <= clips[j][1]) {
        dp[i] = fmin(dp[i], dp[clips[j][0]] + 1);
      }
    }
  }

  return dp[time] == 0x3f3f3f3f ? -1 : dp[time];
}
*/

int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
  int maxn[time + 1];
  memset(maxn, 0, sizeof(maxn));
  for (int i = 0; i < clipsSize; ++i) {
    if (clips[i][0] < time) {
      maxn[clips[i][0]] = fmax(maxn[clips[i][0]], clips[i][1]);
    }
  }

  int ret = 0, last = 0, pre = 0;
  for (int i = 0; i < time; ++i) {
    last = fmax(maxn[i], last);
    if (i == last) {
      return -1;
    }
    if (i == pre) {
      ++ret;
      pre = last;
    }
  }

  return ret;
}

// @lc code=end
