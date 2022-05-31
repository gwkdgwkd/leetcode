/*
给定一个非空字符串s，请判断如果最多从字符串中删除一个字符能否得到一个回文字符串。

示例1:
输入: s = "aba"
输出: true

示例2:
输入: s = "abca"
输出: true
解释: 可以删除"c"字符或者"b"字符

示例3:
输入: s = "abc"
输出: false

提示:
1 <= s.length <= 105
s由小写英文字母组成

注意：本题与680题相同
*/

// 双指针 + 贪心
bool isPalindrome(char* s, int left, int right) {
  for (; left < right; ++left, --right) {
    if (s[left] != s[right]) {
      return false;
    }
  }
  return true;
}
bool validPalindrome(char* s) {
  int len = strlen(s);
  for (int left = 0, right = len - 1; left < right; ++left, --right) {
    if (s[left] != s[right]) {  // 如果不相等，则必须删除一个
      // [left + 1,right]或者[left,right - 1]有一个是回文，则返回true
      return isPalindrome(s, left + 1, right) ||
             isPalindrome(s, left, right - 1);
    }
  }
  return true;
}