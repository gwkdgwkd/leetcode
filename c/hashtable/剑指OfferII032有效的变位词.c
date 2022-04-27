/*
给定两个字符串s和t，编写一个函数来判断它们是不是一组变位词（字母异位词）。
注意：若s和t中每个字符出现的次数都相同且字符顺序不完全相同，则称s和t互为变位词（字母异位词）。

示例1:
输入: s = "anagram", t = "nagaram"
输出: true

示例2:
输入: s = "rat", t = "car"
输出: false

示例3:
输入: s = "a", t = "a"
输出: false

提示:
1 <= s.length, t.length <= 5 * 10^4
s and t仅包含小写字母

进阶: 如果输入字符串包含unicode字符怎么办？你能否调整你的解法来应对这种情况？

注意：本题与242题相似（字母异位词定义不同）
*/

bool isAnagram(char* s, char* t) {
  int len1 = strlen(s);
  int len2 = strlen(t);
  if (len1 != len2 || !memcmp(s, t, len1)) {
    return false;
  }

  int hash[26] = {0};
  for (int i = 0; i < len1; ++i) {
    hash[s[i] - 'a']++;
  }
  for (int i = 0; i < len2; ++i) {
    hash[t[i] - 'a']--;
  }

  for (int i = 0; i < 26; ++i) {
    if (hash[i] != 0) {
      return false;
    }
  }

  return true;
}