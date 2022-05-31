/*
请实现一个函数，把字符串s中的每个空格替换成"%20"。

示例1：
输入：s = "We are happy."
输出："We%20are%20happy."

限制：0 <= s的长度 <= 10000
*/

// 面试题0103URL化

char* replaceSpace(char* s) {
  int count = 0;
  int len = strlen(s);

  for (int i = 0; i < len; ++i) {
    if (s[i] == ' ') {
      ++count;
    }
  }

  int newlen = len + 2 * count;
  char* res = (char*)malloc(sizeof(char) * (newlen + 1));
  res[newlen] = 0;

  int slow = len - 1;
  int fast = newlen - 1;
  while (slow >= 0) {
    if (s[slow] == ' ') {
      res[fast--] = '0';
      res[fast--] = '2';
      res[fast--] = '%';
      slow--;
    } else {
      res[fast--] = s[slow--];
    }
  }

  // int index = 0;
  // for (int i = 0; i < len; ++i) {
  //   if (s[i] == ' ') {
  //     memcpy(res + index, "%20", sizeof(char) * 3);
  //     index += 3;
  //   } else {
  //     res[index++] = s[i];
  //   }
  // }

  return res;
}