/*
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
请定义一个函数实现字符串左旋转操作的功能。
比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

示例1：
输入: s = "abcdefg", k = 2
输出: "cdefgab"

示例2：

输入: s = "lrloseumgh", k = 6
输出: "umghlrlose"

限制： 1 <= k < s.length <= 10000
*/

void reverse(char* s, int left, int right) {
  while (left < right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    ++left;
    --right;
  }
}
char* reverseLeftWords(char* s, int n) {
  int len = strlen(s);
  reverse(s, 0, len - 1);
  reverse(s, 0, len - n - 1);
  reverse(s, len - n, len - 1);
  return s;
}