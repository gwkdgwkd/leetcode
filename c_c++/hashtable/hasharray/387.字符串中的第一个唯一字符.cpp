/*
给定一个字符串s，找到它的第一个不重复的字符，并返回它的索引，如果不存在，则返回-1。

示例1：
输入：s = "leetcode"
输出：0

示例2：
输入：s = "loveleetcode"
输出：2

示例3：
输入：s = "aabb"
输出：-1

提示：
1 <= s.length <= 10^5
s只包含小写字母
*/

int firstUniqChar(char* s) {
  int hash[26];
  memset(hash, 0, sizeof(hash));

  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    hash[s[i] - 'a']++;
  }

  for (int i = 0; i < len; ++i) {
    if (hash[s[i] - 'a'] == 1) {
      return i;
    }
  }

  return -1;
}

class Solution {
 public:
  int firstUniqChar(string s) {
    int n = s.size();
    int hash[26] = {0};
    for (int i = 0; i < n; ++i) {
      hash[s[i] - 'a']++;
    }
    for (int i = 0; i < n; ++i) {
      if (hash[s[i] - 'a'] == 1) {
        return i;
      }
    }

    return -1;
  }
};

// 剑指Offer50第一个只出现一次的字符
// 在字符串s中找出第一个只出现一次的字符，如果没有，返回一个单空格。
char firstUniqChar(char* s) {
  int hash[26];
  memset(hash, 0, sizeof(hash));

  int len = strlen(s);
  for (int i = 0; i < len; ++i) {
    hash[s[i] - 'a']++;
  }

  for (int i = 0; i < len; ++i) {
    if (hash[s[i] - 'a'] == 1) {
      return s[i];
    }
  }

  return ' ';
}