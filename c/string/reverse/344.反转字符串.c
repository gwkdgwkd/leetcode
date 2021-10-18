void reverseString(char* s, int sSize) {
  for (int start = 0, end = sSize - 1; start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}

void reverseString(char* s, int sSize) {
  int left = 0, right = sSize - 1;
  int tmp;
  while (left < right) {
    tmp = s[right];
    s[right] = s[left];
    s[left] = tmp;
    ++left;
    --right;
  }
}