int removeSpace(char* s, int len, char val) {
  int slowIndex = 0, fastIndex = 0;  // 定义快指针，慢指针
  // 去掉字符串前面的空格
  while (len > 0 && fastIndex < len && s[fastIndex] == ' ') {
    fastIndex++;
  }
  for (; fastIndex < len; fastIndex++) {
    // 去掉字符串中间部分的冗余空格
    if (fastIndex - 1 > 0 && s[fastIndex - 1] == s[fastIndex] &&
        s[fastIndex] == ' ') {
      continue;
    } else {
      s[slowIndex++] = s[fastIndex];
    }
  }
  if (slowIndex - 1 > 0 && s[slowIndex - 1] == ' ') {  // 去掉字符串末尾的空格
    s[slowIndex - 1] = 0;
    return slowIndex;
  } else {
    s[slowIndex] = 0;  // 重新设置字符串大小
    return slowIndex + 1;
  }
}

void reverseString(char* s, int sSize) {
  for (int start = 0, end = sSize - 1; start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}

char* reverseWords(char* s) {
  int len = removeSpace(s, strlen(s), ' ');
  reverseString(s, len - 1);

  int start;
  for (int i = 0; i < len; ++i) {
    if (i == 0 || (i > 0 && s[i - 1] == ' ')) {
      start = i;
    }
    if (s[i] == ' ' || i == len - 1) {
      reverseString(s + start, i - start);
    } else {
      continue;
    }
  }
  return s;
}