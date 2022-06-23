/*
给定两个以字符串形式表示的非负整数num1和num2，
返回num1和num2的乘积，它们的乘积也表示为字符串形式。
注意：不能使用任何内置的BigInteger库或直接将输入转换为整数。

示例1:
输入: num1 = "2", num2 = "3"
输出: "6"

示例2:
输入: num1 = "123", num2 = "456"
输出: "56088"

提示：
1 <= num1.length, num2.length <= 200
num1和num2只能由数字组成。
num1和num2都不包含任何前导零，除了数字0本身。
*/

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