void reverseString(char* s, int sSize) {
  for (int start = 0, end = strlen(s) < sSize ? strlen(s) - 1 : sSize - 1;
       start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}
char* reverseStr(char* s, int k) {
  for (int i = 0; i < strlen(s); i = i + 2 * k) {
    reverseString(s + i, k);
  }

  return s;
}

char* reverseStr(char* s, int k) {
  for (int i = 0; i < strlen(s); i = i + 2 * k) {
    int start = i;
    int end = i + fmin(strlen(s + i), k) - 1;
    while (start < end) {
      char tmp = s[start];
      s[start] = s[end];
      s[end] = tmp;
      start++;
      end--;
    }
  }

  return s;
}