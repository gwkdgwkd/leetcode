/*
给定两个字符串s1和s2，写一个函数来判断s2是否包含s1的某个变位词。
换句话说，第一个字符串的排列之一是第二个字符串的子串 。

示例1：
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2包含s1的排列之一("ba")

示例2：
输入: s1= "ab" s2 = "eidboaoo"
输出: False
 
提示：
1 <= s1.length, s2.length <= 10^4
s1和s2仅包含小写字母

注意：本题与567题相同
*/

bool checkInclusion(char* s1, char* s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);

  int hash[26] = {0};
  for (int i = 0; i < len1; ++i) {
    hash[s1[i] - 'a']++;
  }

  int left = 0;
  int right = 0;
  while (right < len2) {
    if (hash[s2[right++] - 'a']-- > 0) {
      --len1;
    }

    while (0 == len1) {
      if (right - left == strlen(s1)) {
        return true;
      }
      if (++hash[s2[left++] - 'a'] > 0) {
        ++len1;
      }
    }
  }

  return false;
}