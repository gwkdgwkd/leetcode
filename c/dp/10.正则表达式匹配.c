/*
给你一个字符串s和一个字符规律p，请你来实现一个支持'.'和'*'的正则表达式匹配。
'.'匹配任意单个字符
'*'匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖整个字符串s的，而不是部分字符串。

示例1：
输入：s = "aa", p = "a"
输出：false
解释："a"无法匹配"aa"整个字符串。

示例2:
输入：s = "aa", p = "a*"
输出：true
解释：因为'*'代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是'a'。
     因此，字符串"aa"可被视为'a'重复了一次。

示例3：
输入：s = "ab", p = ".*"
输出：true
解释：".*"表示可匹配零个或多个（'*'）任意字符（'.'）。

提示：
1 <= s.length <= 20
1 <= p.length <= 30
s只包含从a-z的小写字母。
p只包含从a-z的小写字母，以及字符.和*。
保证每次出现字符*时，前面都匹配到有效的字符
*/

// 递归
bool isMatch(char* s, char* p) {
  if (!*p) return !*s;
  bool match = *s && (*s == *p || *p == '.');
  if (*(p + 1) == '*') {
    // 匹配0个字符 || 匹配一个字符
    return isMatch(s, p + 2) || (match && isMatch(++s, p));
  } else {
    return match && isMatch(++s, ++p);
  }
}

// 动态规划
bool isMatch(char* s, char* p) {
  int lens = strlen(s);
  int lenp = strlen(p);
  // dp[i][j]表示s的前i个是否能被p的前j个匹配
  int dp[lens + 1][lenp + 1];
  for (int i = 0; i <= lens; i++) {
    for (int j = 0; j <= lenp; j++) {
      dp[i][j] = 0;
    }
  }
  dp[0][0] = 1;
  // 当s为空，p不为空时
  for (int j = 2; j <= lenp; j++) {
    if (p[j - 1] == '*') {
      dp[0][j] = dp[0][j - 2];
    }
  }
  // 遍历
  for (int i = 1; i <= lens; i++) {
    for (int j = 1; j <= lenp; j++) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
        dp[i][j] = dp[i - 1][j - 1];
      } else if (p[j - 1] == '*') {
        if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
          // 匹配 0次    s(0,len-1)p(0,len-3)
          //     1次    s(0,len-2)p(0,len-3)
          //     2次以上 s(0,len-2)p(0,len-1)
          dp[i][j] = dp[i][j - 2] || dp[i - 1][j - 2] || dp[i - 1][j];
        } else {
          // 匹配0次 s(0,len-1)p(0,len-3)直接丢弃
          dp[i][j] = dp[i][j - 2];
        }
      }
    }
  }
  return dp[lens][lenp];
}