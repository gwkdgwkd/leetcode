/*
给定一个字符串s，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

示例1：
输入：s = "Let's take LeetCode contest"
输出："s'teL ekat edoCteeL tsetnoc"

示例2:
输入： s = "God Ding"
输出："doG gniD"

提示：
1 <= s.length <= 5 * 10^4
s包含可打印的ASCII字符。
s不包含任何开头或结尾空格。
s里至少有一个词。
s中的所有单词都用一个空格隔开。
*/

// 双指针
void reverse(char *s, int start, int end) {
  for (int l = start, r = end; l < r; ++l, --r) {
    char ch = s[l];
    s[l] = s[r];
    s[r] = ch;
  }
}
char *reverseWords(char *s) {
  int len = strlen(s);
  for (int l = -1, r = 0; r < len; ++r) {
    if (s[r] == ' ') {
      reverse(s, l + 1, r - 1);
      l = r;
    }
    if (r == len - 1) {
      reverse(s, l + 1, r);
    }
  }

  return s;
}

// 官方题解
char *reverseWords(char *s) {
  int length = strlen(s);
  int i = 0;
  while (i < length) {
    int start = i;
    while (i < length && s[i] != ' ') {
      i++;
    }

    int left = start, right = i - 1;
    while (left < right) {
      char tmp = s[left];
      s[left] = s[right], s[right] = tmp;
      left++;
      right--;
    }
    while (i < length && s[i] == ' ') {
      i++;
    }
  }
  return s;
}