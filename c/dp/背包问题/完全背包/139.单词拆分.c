/*
给你一个字符串s和一个字符串列表wordDict作为字典。
请你判断是否可以利用字典中出现的单词拼接出s。
注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

示例1：
输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回true，因为"leetcode"可以由"leet"和"code"拼接成。

示例2：
输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回true，因为"applepenapple"可以由"apple" "pen" "apple"拼接成。
注意，你可以重复使用字典中的单词。

示例3：
输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false

提示：
1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s和wordDict[i]仅有小写英文字母组成
wordDict中的所有字符串互不相同
*/

// 动态规划，完全背包
bool wordBreak(char* s, char** wordDict, int size) {
  int n = strlen(s);
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < size; ++j) {
      int len = strlen(wordDict[j]);
      if (i >= len && strncmp(wordDict[j], &s[i - len], len) == 0) {
        dp[i] |= dp[i - len];
      }
    }
  }

  return dp[n];
}
