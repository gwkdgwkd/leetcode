/*
 * @lc app=leetcode.cn id=392 lang=c
 *
 * [392] 判断子序列
 */

// @lc code=start

// 双指针
bool isSubsequence(char* s, char* t) {
  int m = strlen(s);
  int n = strlen(t);

  int i = 0, j = 0;
  while (i < m && j < n) {
    if (s[i] == t[j]) {
      ++i;
    }
    ++j;
  }

  return i == m;
}

// 时间复杂度：O(m+n)
// 空间复杂度：O(1)

// @lc code=end
