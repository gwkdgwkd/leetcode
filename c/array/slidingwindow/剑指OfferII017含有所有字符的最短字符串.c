/*
给定两个字符串s和t。返回s中包含t的所有字符的最短子字符串。
如果s中不存在符合条件的子字符串，则返回空字符串""。
如果s中存在多个符合条件的子字符串，返回任意一个。

注意：对于t中重复字符，我们寻找的子字符串中该字符数量必须不少于t中该字符数量。

示例1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC" 
解释：最短子字符串"BANC"包含了字符串t的所有字符'A'、'B'、'C'

示例2：
输入：s = "a", t = "a"
输出："a"

示例3：
输入：s = "a", t = "aa"
输出：""
解释：t中两个字符'a'均应包含在s的子串中，因此没有符合条件的子字符串，返回空字符串。

提示：
1 <= s.length, t.length <= 10^5
s和t由英文字母组成

进阶：你能设计一个在o(n)时间内解决此问题的算法吗？

注意：本题与76题相似（本题答案不唯一）
*/

#define MAX 125
char* minWindow(char* s, char* t) {
  int lens = strlen(s);
  int lent = strlen(t);

  int hash[MAX] = {0};
  for (int i = 0; i < lent; ++i) {
    hash[t[i]]++;
  }

  int left = 0;
  int right = 0;
  int start = 0;
  int minlen = INT_MAX;
  while (right < lens) {
    if (hash[s[right++]]-- > 0) {
      --lent;
    }
    while (lent == 0) {
      if (right - left < minlen) {
        start = left;
        minlen = right - left;
      }
      if (++hash[s[left++]] > 0) {
        ++lent;
      }
    }
  }

  if (minlen == INT_MAX) {
    return "";
  }
  s[start + minlen] = 0;
  return s + start;
}