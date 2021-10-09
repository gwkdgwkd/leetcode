/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] 最小覆盖子串
 */

// @lc code=start

// 滑动窗口问题思想：
// 如果不满足条件，右边界向前推移，寻找解
// 如果满足条件，右边界停止更新，左边界向前推移，寻找最优解，并存储最优解；
// 条件指的是有效字符数和每个字符的个数都对应上；
#define MAX_NUM 128
char* minWindow(char* s, char* t) {
  int left = 0;
  int right = 0;
  int need[MAX_NUM] = {0};
  int window[MAX_NUM] = {0};
  int valid = 0;
  int cur = 0;
  int start = 0;
  int len = INT_MAX;
  for (int i = 0; i < strlen(t); i++) {
    if (need[t[i]] == 0) {
      valid++;
    }
    need[t[i]]++;
  }

  while (right < strlen(s)) {
    if (need[s[right]] > 0) {
      window[s[right]]++;
      if (need[s[right]] == window[s[right]]) {
        cur++;
      }
    }
    right++;
    // 停止更新窗口
    while (cur == valid) {
      if (right - left < len) {
        start = left;
        len = right - left;
      }
      char a = s[left];
      if (need[a] > 0) {
        window[a]--;
        if (need[a] > window[a]) {
          cur--;
        }
      }
      left++;
    }
  }

  if (len == INT_MAX) {
    return "";
  } else {
    *(s + start + len) = '\0';
    return s + start;
  }
}

// @lc code=end
