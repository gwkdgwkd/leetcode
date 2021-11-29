char *multiply(char *num1, char *num2) {
  int l1 = strlen(num1);
  int l2 = strlen(num2);
  char *res = (char *)calloc(l1 + l2 + 1, sizeof(char));

  for (int i = l2 - 1; i >= 0; --i) {
    for (int j = l1 - 1; j >= 0; --j) {
      int mul = (num2[i] - '0') * (num1[j] - '0');
      int p1 = i + j;
      int p2 = i + j + 1;
      int sum = (res[p2] == 0 ? 0 : (res[p2] - '0')) + mul;
      if (res[p1]) {
        res[p1] = res[p1] - '0' + sum / 10 + '0';
      } else {
        res[p1] = sum / 10 + '0';
      }
      res[p2] = sum % 10 + '0';
    }
  }
  int index = 0;
  while (res[index]) {
    if (res[index] != '0') {
      break;
    }
    ++index;
  }
  if (strlen(res) == index) {  // 乘积为0
    res[0] = '0';
    res[1] = 0;
  } else {  // 去掉前缀0
    memmove(res, res + index, strlen(res) - index);
    res[strlen(res) - index] = 0;
  }

  return res;
}