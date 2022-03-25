/*
给定s和t两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回true。#代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

示例1：
输入：s = "ab#c", t = "ad#c"
输出：true
解释：s 和 t 都会变成 "ac"。

示例2：
输入：s = "ab##", t = "c#d#"
输出：true
解释：s 和 t 都会变成 ""。

示例3：
输入：s = "a#c", t = "b"
输出：false
解释：s 会变成 "c"，但 t 仍然是 "b"。

提示：
1 <= s.length, t.length <= 200
s和t只含有小写字母以及字符'#'

进阶：你可以用O(n)的时间复杂度和O(1)的空间复杂度解决该问题吗？
*/

// 双指针
bool backspaceCompare(char* s, char* t) {
  // 一个字符是否会被删掉，只取决于该字符后面的退格符，而与该字符前面的退格符无关。
  // 因此当我们逆序地遍历字符串，就可以立即确定当前字符是否会被删掉。
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
