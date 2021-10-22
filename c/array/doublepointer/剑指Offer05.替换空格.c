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

  return res;
}