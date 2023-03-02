/*
给你两个字符串s1和s2，写一个函数来判断s2是否包含s1的排列。
如果是，返回true；否则，返回false。
换句话说，s1的排列之一是s2的子串。

示例1：
输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2包含s1的排列之一"ba"。

示例2：
输入：s1 = "ab" s2 = "eidboaoo"
输出：false

提示：
1 <= s1.length, s2.length <= 10^4
s1和s2仅包含小写字母
*/

// 剑指OfferII014字符串中的变位词

// 滑动窗口
bool checkInclusion(char* s1, char* s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int hash[26] = {0};
  int left = 0;
  int right = 0;
  for (int i = 0; i < len1; ++i) {
    hash[s1[i] - 'a']++;
  }

  while (right < len2) {
    if (hash[s2[right] - 'a']-- > 0) {
      len1--;
    }
    right++;
    while (0 == len1) {
      if (right - left == strlen(s1)) {
        return true;
      }
      if (++hash[s2[left] - 'a'] > 0) {
        len1++;
      }
      left++;
    }
  }

  return false;
}

class Solution {
 public:
  bool checkInclusion(string s1, string s2) {
    int hash[26] = {0};
    for (char c : s1) {
      hash[c - 'a']++;
    }

    int len1 = s1.size();
    int len = len1;
    int len2 = s2.size();
    int left = 0;
    int right = 0;

    while (right < len2) {
      if (hash[s2[right++] - 'a']-- > 0) {
        --len1;
      }
      while (len1 == 0) {
        if (right - left == len) {
          return true;
        }
        if (++hash[s2[left++] - 'a'] > 0) {
          ++len1;
        }
      }
    }

    return false;
  }
};
