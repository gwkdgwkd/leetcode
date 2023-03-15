/*
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
说明：本题中，将空字符串定义为有效的回文串。

示例1：
输入："A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama"是回文串

示例2：
输入："race a car"
输出：false
解释："raceacar"不是回文串

提示：
1 <= s.length <= 2 * 10^5
字符串s由ASCII字符组成
*/

// 剑指OfferII018有效的回文

bool valid(char c) {
  return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
          (c >= 'A' && c <= 'Z'));
}
bool isPalindrome(char* s) {
  int len = strlen(s);
  for (int left = 0, right = len - 1; left < right; ++left, --right) {
    while (left < len && !valid(s[left])) {
      ++left;
    }
    while (right >= 0 && !valid(s[right])) {
      --right;
    }
    if (left < right && (s[left] | ' ') != (s[right] | ' ')) {
      return false;
    }
  }

  return true;
}

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
      return false;
    }
  }

  return true;
}

class Solution {
 public:
  bool isPalindrome(string s) {
    int n = s.size();
    int left = 0;
    int right = n - 1;
    while (left < right) {
      while (left < right && !isalnum(s[left])) {
        ++left;
      }
      while (left < right && !isalnum(s[right])) {
        --right;
      }
      if (toupper(s[left++]) != toupper(s[right--])) {
        return false;
      }
    }
    return true;
  }
};