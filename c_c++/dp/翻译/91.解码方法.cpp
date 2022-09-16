/*
一条包含字母A-Z的消息通过以下映射进行了编码：
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
要解码已编码的消息，所有数字必须基于上述映射的方法，
反向映射回字母（可能有多种方法）。
例如，"11106"可以映射为：
"AAJF"，将消息分组为(1 1 10 6)
"KJF"，将消息分组为(11 10 6)
注意，消息不能分组为(1 11 06)，因为"06"不能映射为"F"，
这是由于"6"和"06"在映射中并不等价。
给你一个只含数字的非空字符串s，请计算并返回解码方法的总数。
题目数据保证答案肯定是一个32位的整数。

示例1：
输入：s = "12"
输出：2
解释：它可以解码为"AB"（1 2）或者"L"（12）。

示例2：
输入：s = "226"
输出：3
解释：它可以解码为"BZ"(2 26), "VF"(22 6)或者"BBF"(2 2 6)。

示例3：
输入：s = "0"
输出：0
解释：没有字符映射到以0开头的数字。
含有0的有效映射是'J'->"10"和'T'->"20"。
由于没有字符，因此没有有效的方法对此进行解码，因为所有数字都需要映射。

提示：
1 <= s.length <= 100
s只包含数字，并且可能包含前导零。
*/

// 动态规划
int numDecodings(char* s) {
  int n = strlen(s);

  if (s[0] == '0' || n < 1) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  int dp[n];
  dp[0] = s[0] == '0' ? 0 : 1;
  if ((s[0] - '0') * 10 + s[1] - '0' <= 26) {
    dp[1] = s[1] == '0' ? 1 : 2;
  } else if ((s[0] - '0') * 10 + s[1] - '0' > 26 && s[1] == '0') {
    return 0;
  } else {
    dp[1] = 1;
  }

  for (int i = 2; i < n; ++i) {
    if (s[i] == '0') {
      if (((s[i - 1] - '0') * 10 + s[i] - '0' == 0) ||
          ((s[i - 1] - '0') * 10 + s[i] - '0' > 26)) {
        return 0;
      }
      dp[i] = dp[i - 2];
      continue;
    }
    if (s[i - 1] == '0') {
      dp[i] = dp[i - 1];
      continue;
    }
    if ((s[i - 1] - '0') * 10 + s[i] - '0' <= 26) {
      dp[i] = dp[i - 2] + dp[i - 1];
    } else {
      dp[i] = dp[i - 1];
    }
  }

  return dp[n - 1];
}

// 官方题解
int numDecodings(char* s) {
  int n = strlen(s);
  // a = f[i-2], b = f[i-1], c = f[i]
  int a = 0, b = 1, c;
  for (int i = 1; i <= n; ++i) {
    c = 0;
    if (s[i - 1] != '0') {
      c += b;
    }
    if (i > 1 && s[i - 2] != '0' &&
        ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
      c += a;
    }
    a = b, b = c;
  }
  return c;
}

class Solution {
 public:
  int numDecodings(string s) {
    int n = s.size();

    vector<int> dp(n + 1, 0);  // dp[i]表示前i个字符可以有几种解码方式
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      if (s[i - 1] != '0') {
        dp[i] += dp[i - 1];
      }
      if (i > 1 && s[i - 2] != '0' &&
          ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
        dp[i] += dp[i - 2];
      }
    }
    return dp[n];
  }
};
