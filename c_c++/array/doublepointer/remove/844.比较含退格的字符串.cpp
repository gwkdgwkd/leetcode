/*
给定s和t两个字符串，当它们分别被输入到空白的文本编辑器后，
如果两者相等，返回true，#代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

示例1：
输入：s = "ab#c", t = "ad#c"
输出：true
解释：s和t都会变成"ac"。

示例2：
输入：s = "ab##", t = "c#d#"
输出：true
解释：s和t都会变成""。

示例3：
输入：s = "a#c", t = "b"
输出：false
解释：s会变成"c"，但t仍然是"b"。

提示：
1 <= s.length, t.length <= 200
s和t只含有小写字母以及字符'#'

进阶：你可以用O(n)的时间复杂度和O(1)的空间复杂度解决该问题吗？
*/

// 双指针
int removeback(char* str) {
  int len = strlen(str);
  int slow = len - 1;
  int skip = 0;

  // 一个字符是否会被删掉，只取决于该字符后面的退格符，而与该字符前面的退格符无关。
  // 因此当我们逆序地遍历字符串，就可以立即确定当前字符是否会被删掉。
  for (int fast = len - 1; fast >= 0; --fast) {
    if (str[fast] != '#') {
      if (skip > 0) {
        skip--;
        continue;
      }
      str[slow--] = str[fast];
    } else {
      skip++;
    }
  }

  return slow;
}
bool backspaceCompare(char* s, char* t) {
  int i = removeback(s);
  int j = removeback(t);

  return (strlen(s) - i == strlen(t) - j) &&
         !memcmp(s + i + 1, t + j + 1, strlen(s) - i - 1);
}

class Solution {
 public:
  bool backspaceCompare(string s, string t) {
    auto remove = [](string& str) {
      int slow = str.size() - 1;
      int fast = slow;

      int c = 0;
      while (fast >= 0) {
        if (str[fast] == '#') {
          ++c;
        } else {
          if (c > 0) {
            --c;
          } else {
            str[slow--] = str[fast];
          }
        }
        --fast;
      }
      return slow;
    };

    int i = remove(s);
    int j = remove(t);

    return string(s.begin() + i + 1, s.end()) ==
           string(t.begin() + j + 1, t.end());
  }
};