/*
给定两个字符串s1和s2，请编写一个程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。

示例1：
输入: s1 = "abc", s2 = "bca"
输出: true 

示例2：
输入: s1 = "abc", s2 = "bad"
输出: false

说明：
0 <= len(s1) <= 100
0 <= len(s2) <= 100
*/

bool CheckPermutation(char* s1, char* s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  if (len1 != len2) {
    return false;
  }

  int hash[256] = {0};
  for (int i = 0; i < len1; ++i) {
    hash[s1[i]]++;
  }

  for (int i = 0; i < len2; ++i) {
    hash[s2[i]]--;
  }

  for (int i = 0; i < 256; ++i) {
    if (hash[i]) {
      return false;
    }
  }

  return true;
}