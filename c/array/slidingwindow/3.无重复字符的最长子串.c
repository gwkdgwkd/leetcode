int lengthOfLongestSubstring(char *s) {
  char *cur = s, *head = s;
  int max = 0;
  while (*cur) {
    for (char *p = head; p < cur; ++p) {
      if (*p == *cur) {
        head = p + 1;
        break;
      }
    }
    max = cur - head + 1 > max ? cur - head + 1 : max;
    ++cur;
  }
  return max;
}

// 滑动窗口
int lengthOfLongestSubstring(char *s) {
  int len = strlen(s);
  int left = 0;
  int right = 0;
  int hash[256] = {0};
  int max = 0;

  while (right < len) {
    char c = s[right];
    hash[c]++;
    right++;
    while (hash[c] > 1) {
      hash[s[left]]--;
      left++;
    }
    max = fmax(max, right - left);
  }

  return max;
}