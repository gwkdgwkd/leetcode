/*
给你一个字符串s，请你统计并返回这个字符串中回文子串的数目。
回文字符串是正着读和倒过来读一样的字符串。
子字符串是字符串中的由连续字符组成的一个序列。
具有不同开始位置或结束位置的子串，
即使是由相同的字符组成，也会被视作不同的子串。

示例1：
输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"

示例2：
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

提示：
1 <= s.length <= 1000
s由小写英文字母组成
*/

// 剑指OfferII020回文子字符串的个数

// 动态规划
int countSubstrings(char* s) {
  int len = strlen(s);
  bool dp[len][len];
  memset(dp, 0, sizeof(dp));

  int count = 0;
  for (int i = 0; i < len; ++i) {
    dp[i][i] = true;
    ++count;
  }

  for (int i = len - 2; i >= 0; --i) {
    for (int j = i + 1; j < len; ++j) {
      if (s[i] == s[j]) {
        if (i + 1 == j || dp[i + 1][j - 1]) {
          dp[i][j] = true;
          ++count;
        }
      }
    }
  }

  return count;
}

int countSubstrings(char* s) {
  int n = strlen(s);
  // 布尔类型的dp[i][j]：
  // 表示区间范围[i,j]（注意是左闭右闭）的⼦串是否是回⽂⼦串，
  // 如果是dp[i][j]为true，否则为false。
  bool dp[n][n];
  int result = 0;
  memset(dp, 0, sizeof(dp));

  // 如果这矩阵是从上到下，从左到右遍历，
  // 那么会⽤到没有计算过的dp[i+1][j-1]，
  // 也就是根据不确定是不是回⽂的区间[i+1,j-1]，
  // 来判断了[i,j]是不是回⽂，那结果⼀定是不对的。
  // 所以⼀定要从下到上，从左到右遍历，
  // 这样保证dp[i+1][j-1]都是经过计算的。
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i; j < n; ++j) {
      // 递推公式整体上是两种：
      // 就是s[i]与s[j]相等，s[i]与s[j]不相等这两种。
      // 1.当s[i]与s[j]不相等，那没啥好说的了，dp[i][j]⼀定是false。
      // 2.当s[i]与s[j]相等时，这就复杂⼀些了，有如下三种情况：
      //   a：下标i与j相同，同⼀个字符例如a，当然是回⽂⼦串；
      //   b：下标i与j相差为1，例如aa，也是⽂⼦串；
      //   c：下标i与j相差⼤于1的时候，例如cabac，
      //      此时s[i]与s[j]已经相同了，那么就看区间i+1与j-1区间，
      //      这个区间是不是回⽂就看dp[i+1][j-1]是否为true。
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

class Solution {
 public:
  int countSubstrings(string s) {
    int n = s.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));
    int count = 0;
    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j < n; ++j) {
        if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
          dp[i][j] = 1;
          ++count;
        }
      }
    }
    return count;
  }
};

class Solution {
 public:
  int countSubstrings(string s) {
    int n = s.size();

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = true;
    }

    int ans = n;
    for (int i = n - 2; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j] && (j == i + 1 || dp[i + 1][j - 1])) {
          dp[i][j] = true;
          ++ans;
        }
      }
    }

    return ans;
  }
};
