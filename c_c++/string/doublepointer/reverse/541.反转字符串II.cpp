/*
给定一个字符串s和一个整数k，从字符串开头算起，每计数至2k个，就反转这2k中的前k个。
如果剩余字符少于k个，则将剩余字符全部反转，如果剩余字符小于2k但大于或等于k个，
则反转前k个字符，其余字符保持原样。

示例1：
输入：s = "abcdefg"，k = 2
输出："bacdfeg"

示例2：
输入：s = "abcd"，k = 2
输出："bacd"

提示：
1 <= s.length <= 10^4
s 仅由小写英文组成
1 <= k <= 10^4
*/

void reverseString(char* s, int sSize) {
  for (int start = 0, end = strlen(s) < sSize ? strlen(s) - 1 : sSize - 1;
       start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}
char* reverseStr(char* s, int k) {
  for (int i = 0; i < strlen(s); i = i + 2 * k) {
    reverseString(s + i, k);
  }

  return s;
}

char* reverseStr(char* s, int k) {
  for (int i = 0; i < strlen(s); i = i + 2 * k) {
    int start = i;
    int end = i + fmin(strlen(s + i), k) - 1;
    while (start < end) {
      char tmp = s[start];
      s[start] = s[end];
      s[end] = tmp;
      start++;
      end--;
    }
  }

  return s;
}

class Solution {
  void reverse(string& s, int left, int right) {
    while (left < right) {
      swap(s[left], s[right]);
      ++left;
      --right;
    }
  }

 public:
  string reverseStr(string s, int k) {
    int n = s.size();

    for (int i = 0; i < n; i = i + k * 2) {
      int end = i + min(k, n - i) - 1;
      reverse(s, i, end);
    }
    return s;
  }
};