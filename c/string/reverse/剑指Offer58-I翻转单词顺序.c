/*
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
为简单起见，标点符号和普通字母一样处理。
例如输入字符串"I am a student. "，则输出"student. a am I"。

示例1：
输入: "the sky is blue"
输出: "blue is sky the"

示例2：
输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

示例3：
输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

说明：
无空格字符构成一个单词。
输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

注意：本题与151题相同
*/

void removeSpace(char* s) {
  int len = strlen(s);
  int fast = 0;
  int slow = 0;

  while (len > 0 && fast < len && s[fast] == ' ') {
    ++fast;
  }

  while (fast < len) {
    while (fast < len - 1 && s[fast] == ' ' && s[fast + 1] == ' ') {
      ++fast;
    }
    s[slow++] = s[fast++];
  }

  if (slow > 0 && s[slow - 1] == ' ') {
    --slow;
  }
  s[slow] = 0;
}
void reverse(char* s, int left, int right) {
  while (left < right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    ++left;
    --right;
  }
}
char* reverseWords(char* s) {
  removeSpace(s);

  int len = strlen(s);
  reverse(s, 0, len - 1);

  int l = 0;
  for (int r = 0; r < len; ++r) {
    if (s[r] == ' ') {
      reverse(s, l, r - 1);
      l = r + 1;
    }
    if (r == len - 1) {
      reverse(s, l, r);
    }
  }

  return s;
}