/*
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

示例1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是"abc"，所以其长度为3。

示例2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是"b"，所以其长度为1。

示例3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是"wke"，所以其长度为3。
     请注意，你的答案必须是子串的长度，"pwke"是一个子序列，不是子串。

提示：s.length <= 40000

注意：本题与主站3题相同
*/

int lengthOfLongestSubstring(char* s) {
  int len = strlen(s);
  int hash[256] = {0};
  int left = 0;
  int right = 0;
  int max = 0;

  while (right < len) {
    char c = s[right++];
    hash[c]++;
    while (hash[c] > 1) {
      hash[s[left]]--;
      ++left;
    }
    max = fmax(max, right - left);
  }

  return max;
}