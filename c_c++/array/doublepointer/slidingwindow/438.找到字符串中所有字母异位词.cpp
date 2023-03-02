/*
给定两个字符串s和p，找到s中所有p的异位词的子串，
返回这些子串的起始索引，不考虑答案输出的顺序。
异位词指由相同字母重排列形成的字符串（包括相同的字符串）。

示例1:
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于0的子串是"cba",它是"abc"的异位词。
起始索引等于6的子串是"bac",它是"abc"的异位词。

示例2:
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于0的子串是"ab",它是"ab"的异位词。
起始索引等于1的子串是"ba",它是"ab"的异位词。
起始索引等于2的子串是"ab",它是"ab"的异位词。

提示:
1 <= s.length, p.length <= 3 * 10^4
s和p仅包含小写字母
*/

// 剑指OfferII015字符串中的所有变位词

// 滑动窗口+哈希
int *findAnagrams(char *s, char *p, int *returnSize) {
  int lens = strlen(s);
  int lenp = strlen(p);
  int count = lenp;
  int hash[26] = {0};

  int tmp[lens];
  memset(tmp, 0, sizeof(tmp));
  *returnSize = 0;

  for (int i = 0; i < lenp; ++i) {
    hash[p[i] - 'a']++;  // 统计串t中各元素的哈希值
  }

  int start = 0, end = 0;
  while (end < lens) {  // 右指针从串s头移动到串s尾
    // 串s中当前元素在串t中出现过时，其值大于0，串s中当前元素的哈希值减1
    if (hash[s[end] - 'a']-- > 0) {
      count--;
    }
    end++;  // 右指针向右移动

    while (count == 0) {               // 出现匹配的子串
      if (end - start == lenp) {       // 当前子串与串t匹配
        tmp[(*returnSize)++] = start;  // 更新匹配数组的值
      }

      // 串s当前start的哈希值加1
      if (++hash[s[start] - 'a'] > 0) {
        // 若大于0，则表示左指针start移动后的子串不符合条件
        // 若小于等于0，则表示左指针start移动后的字串还能符合条件
        count++;
      }
      start++;  // 左指针向右移动
    }
  }

  if (*returnSize > 0) {
    int *ret = (int *)malloc(sizeof(int) * (*returnSize));
    memcpy(ret, tmp, sizeof(int) * (*returnSize));
    return ret;
  } else {
    return NULL;
  }
}

// 采用26个字母的hash运算法+移动窗口，时间复杂度O(n)
int *findAnagrams(char *s, char *p, int *returnSize) {
  int ls = strlen(s);
  int lp = strlen(p);
  int lenp = lp;
  int hash[26] = {0};
  int left = 0;
  int right = 0;
  for (int i = 0; i < lp; ++i) {
    hash[p[i] - 'a']++;
  }

  int *res = (int *)malloc(sizeof(int) * ls);
  *returnSize = 0;
  while (right < ls) {
    if (hash[s[right] - 'a']-- > 0) {
      lp--;
    }
    right++;
    while (0 == lp) {
      if (right - left == lenp) {
        res[(*returnSize)++] = left;
      }
      hash[s[left] - 'a']++;
      if (hash[s[left] - 'a'] > 0) {
        lp++;
      }
      left++;
    }
  }

  return res;
}

class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    int hash[26] = {0};
    for (char c : p) {
      hash[c - 'a']++;
    }

    int lenp = p.size();
    int len = lenp;
    int lens = s.size();
    int left = 0;
    int right = 0;

    vector<int> res;
    while (right < lens) {
      if (hash[s[right++] - 'a']-- > 0) {
        --lenp;
      }

      while (lenp == 0) {
        if (right - left == len) {
          res.emplace_back(left);
        }
        if (++hash[s[left++] - 'a'] > 0) {
          ++lenp;
        }
      }
    }

    return res;
  }
};