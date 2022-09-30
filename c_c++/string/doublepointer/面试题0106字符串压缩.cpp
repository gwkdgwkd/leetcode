/*
字符串压缩。
利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。
比如，字符串aabcccccaaa会变为a2b1c5a3。
若压缩后的字符串没有变短，则返回原先的字符串。
你可以假设字符串中只包含大小写英文字母（a至z）。

示例1:
输入："aabcccccaaa"
输出："a2b1c5a3"

示例2:
输入："abbccd"
输出："abbccd"
解释："abbccd"压缩后为"a1b2c2d1"，比原字符串长度更长。

提示：字符串长度在[0,50000]范围内。
*/

char* compressString(char* S) {
  int len = strlen(S);
  if (len < 2) {
    return S;
  }
  int max = len * 2 + 1;

  char* res = (char*)malloc(sizeof(char) * max);
  memset(res, 0, sizeof(char) * max);
  int slow = 0;
  int fast = 0;
  while (fast < len) {
    if (S[slow] == S[fast]) {
      ++fast;
    } else {
      sprintf(res + strlen(res), "%c%d", S[slow], fast - slow);
      slow = fast;
      ++fast;
    }
  }
  sprintf(res + strlen(res), "%c%d", S[slow], fast - slow);

  if (strlen(res) >= len) {
    return S;
  } else {
    return res;
  }
}

class Solution {
 public:
  string compressString(string S) {
    int n = S.size();
    string ans;

    int left = 0;
    int right = 0;
    while (right < n) {
      if (S[left] != S[right]) {
        ans += S[left];
        ans += to_string(right - left);
        left = right;
      }
      if (right == n - 1) {
        ans += S[left];
        ans += to_string(right - left + 1);
        left = right;
      }
      ++right;
    }

    return ans.size() < n ? ans : S;
  }
};