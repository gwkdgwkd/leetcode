/*
给定一个字符串s，验证s是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
本题中，将空字符串定义为有效的回文串。

示例1:
输入: s = "A man, a plan, a canal: Panama"
输出: true
解释："amanaplanacanalpanama"是回文串

示例2:
输入: s = "race a car"
输出: false
解释："raceacar"不是回文串

提示：
1 <= s.length <= 2 * 10^5
字符串s由ASCII字符组成

注意：本题与125题相同
*/

bool isPalindrome(char* s) {
  int len = strlen(s);

  for (int left = 0, right = len - 1; left < right; ++left, --right) {
    while (left < right && !isalnum(s[left])) {
      ++left;
    }
    while (left < right && !isalnum(s[right])) {
      --right;
    }
    if (toupper(s[left]) != toupper(s[right])) {
      // if((s[left]|' ') != (s[right] | ' ')) {
      return false;
    }
  }

  return true;
}