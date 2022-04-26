/*
给定两个字符串s和p，找到s中所有p的变位词的子串，返回这些子串的起始索引。
不考虑答案输出的顺序。
变位词指字母相同，但排列不同的字符串。

示例1：
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于0的子串是"cba",它是"abc"的变位词。
起始索引等于6的子串是"bac",它是"abc"的变位词。

示例2：
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于0的子串是"ab",它是"ab"的变位词。
起始索引等于1的子串是"ba",它是"ab"的变位词。
起始索引等于2的子串是"ab",它是"ab"的变位词。

提示:
1 <= s.length, p.length <= 3 * 10^4
s和p仅包含小写字母

注意：本题与438题相同
*/

int* findAnagrams(char* s, char* p, int* returnSize) {
  int len1 = strlen(p);
  int len2 = strlen(s);

  int hash[26] = {0};
  for (int i = 0; i < len1; ++i) {
    hash[p[i] - 'a']++;
  }

  int* res = (int*)malloc(sizeof(int) * len2);
  *returnSize = 0;
  int left = 0;
  int right = 0;
  while (right < len2) {
    if (hash[s[right++] - 'a']-- > 0) {
      --len1;
    }

    while (0 == len1) {
      if (right - left == strlen(p)) {
        res[(*returnSize)++] = left;
      }
      if (++hash[s[left++] - 'a'] > 0) {
        ++len1;
      }
    }
  }

  return res;
}