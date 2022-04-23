/*
数字以0123456789101112131415…的格式序列化到一个字符序列中。
在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
请写一个函数，求任意第n位对应的数字。

示例1：
输入：n = 3
输出：3

示例2：
输入：n = 11
输出：0

限制：0 <= n < 2^31
*/

int findNthDigit(int n) {
  int idx = 1;
  long base = 9;

  while (n > idx * base) {
    n -= idx * base;
    base *= 10;
    idx++;
  }
  n--;
  int cnt = n / idx;
  int res = n % idx;

  char str[12];
  sprintf(str, "%d", base / 9 + cnt);

  return str[res] - '0';
}
