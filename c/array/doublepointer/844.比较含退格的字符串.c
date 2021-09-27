/*
 * @lc app=leetcode.cn id=844 lang=c
 *
 * [844] 比较含退格的字符串
 */

// @lc code=start

// 双指针
bool backspaceCompare(char* s, char* t) {
  // 一个字符是否会被删掉，只取决于该字符后面的退格符，而与该字符前面的退格符无关。因此当我们逆序地遍历字符串，就可以立即确定当前字符是否会被删掉。
  int ls = strlen(s);
  int lt = strlen(t);

  int slow1 = ls - 1;
  int skip = 0;
  for (int fast = ls - 1; fast >= 0; --fast) {
    if (s[fast] != '#') {
      if (skip > 0) {
        skip--;
        continue;
      }
      s[slow1--] = s[fast];
    } else {
      skip++;
    }
  }
  // printf("%s\n",s + slow1 + 1);
  int slow2 = lt - 1;
  skip = 0;
  for (int fast = lt - 1; fast >= 0; --fast) {
    if (t[fast] != '#') {
      if (skip > 0) {
        skip--;
        continue;
      }
      t[slow2--] = t[fast];
    } else {
      skip++;
    }
  }
  // printf("%s\n",t + slow2 + 1);

  return (ls - slow1 == lt - slow2) &&
         !memcmp(s + slow1 + 1, t + slow2 + 1, ls - slow1 - 1);
}

// @lc code=end
