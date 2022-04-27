/*
给定一个字符串s，请你找出其中不含有重复字符的最长连续子字符串的长度。

示例1:
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子字符串是"abc"，所以其长度为3。

示例2:
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子字符串是"b"，所以其长度为1。

示例3:
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是"wke"，所以其长度为3。
     请注意，你的答案必须是子串的长度，"pwke"是一个子序列，不是子串。

示例4:
输入: s = ""
输出: 0

提示：
0 <= s.length <= 5 * 10^4
s由英文字母、数字、符号和空格组成

注意：本题与3题相同
*/

int lengthOfLongestSubstring(char* s) {
  int len = strlen(s);
  char hash[256] = {0};

  int left = 0;
  int right = 0;
  int max = 0;
  while (right < len) {
    char c = s[right++];
    hash[c]++;
    while (hash[c] > 1) {
      hash[s[left++]]--;
    }
    max = fmax(max, right - left);
  }

  return max;
}