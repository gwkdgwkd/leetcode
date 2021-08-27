/*
 * @lc app=leetcode.cn id=647 lang=c
 *
 * [647] 回文子串
 */

// @lc code=start

// 动态规划
int countSubstrings(char* s) {
  int n = strlen(s);
  int dp[n][n];
  int ret = 0;
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
    ++ret;
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      if (j == i + 1) {
        dp[i][j] = s[i] == s[j] ? 1 : 0;
      } else {
        dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] : 0;
      }
      if (dp[i][j]) {
        ++ret;
      }
    }
  }

  return ret;
}

int countSubstrings(char* s) {
  int n = strlen(s);
  // 布尔类型的dp[i][j]：表示区间范围[i,j]（注意是左闭右闭）的⼦串是否是回⽂⼦串，如果是dp[i][j]为true，否则为false。
  bool dp[n][n];
  int result = 0;
  memset(dp, 0, sizeof(dp));

  // 如果这矩阵是从上到下，从左到右遍历，那么会⽤到没有计算过的dp[i+1][j-1]，也就是根据不确定是不是回⽂的区间[i+1,j-1]，来判断了[i,j]是不是回⽂，
  // 那结果⼀定是不对的。所以⼀定要从下到上，从左到右遍历，这样保证dp[i+1][j-1]都是经过计算的。
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i; j < n; ++j) {
      // 递推公式整体上是两种，就是s[i]与s[j]相等，s[i]与s[j]不相等这两种。
      // 当s[i]与s[j]不相等，那没啥好说的了，dp[i][j]⼀定是false。
      // 当s[i]与s[j]相等时，这就复杂⼀些了，有如下三种情况：
      //   情况⼀：下标i与j相同，同⼀个字符例如a，当然是回⽂⼦串
      //   情况⼆：下标i与j相差为1，例如aa，也是⽂⼦串
      //   情况三：下标i与j相差⼤于1的时候，例如cabac，此时s[i]与s[j]已经相同了，那么就看区间i+1与j-1区间，这个区间是不是回⽂就看dp[i+1][j-1]是否为true。
      if (s[i] == s[j]) {
        if (j - i <= 1) {  // 情况一和情况二
          ++result;
          dp[i][j] = true;
        } else if (dp[i + 1][j - 1]) {  // 情况三
          ++result;
          dp[i][j] = true;
        }
      }

      // 整合到一起：
      // if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
      //   ++result;
      //   dp[i][j] = true;
      // }
    }
  }

  return result;
}

// @lc code=end
