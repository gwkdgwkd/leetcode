// 暴力法，超时
bool checkNum(int num) {
  int max = 10;
  while (num) {
    int t = num % 10;
    if (max >= t)
      max = t;
    else
      return false;
    num = num / 10;
  }
  return true;
}
int monotoneIncreasingDigits(int n) {
  for (int i = n; i >= 0; --i) {
    if (checkNum(i)) {
      return i;
    }
  }

  return 0;
}

// 贪心算法
void itoa(int num, char* str, int* strSize) {
  *strSize = 0;
  while (num > 0) {
    str[(*strSize)++] = num % 10 + '0';
    num /= 10;
  }
  for (int i = 0; i < (*strSize) / 2; i++) {
    int tmp = str[i];
    str[i] = str[(*strSize) - 1 - i];
    str[(*strSize) - 1 - i] = tmp;
  }
}
int monotoneIncreasingDigits(int n) {
  int strNSize;
  char strN[11];
  itoa(n, strN, &strNSize);
  int i = 1;
  while (i < strNSize && strN[i - 1] <= strN[i]) {
    i += 1;
  }
  if (i < strNSize) {
    while (i > 0 && strN[i - 1] > strN[i]) {
      strN[i - 1] -= 1;
      i -= 1;
    }
    for (i += 1; i < strNSize; ++i) {
      strN[i] = '9';
    }
  }
  return atoi(strN);
}