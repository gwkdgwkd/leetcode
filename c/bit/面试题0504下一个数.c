/*
下一个数。给定一个正整数，找出与其二进制表达式中1的个数相同且大小最接近的那两个数（一个略大，一个略小）。

示例1:
输入：num = 2（或者0b10）
输出：[4, 1] 或者（[0b100, 0b1]）

示例2:
输入：num = 1
输出：[2, -1]

提示:
num的范围在[1, 2147483647]之间；
如果找不到前一个或者后一个满足条件的正数，那么输出-1。
*/

int cntbit(long n) {
  int cnt = 0;
  while (n > 0) {
    if (n & 1) cnt++;
    n = n >> 1;
  }

  return cnt;
}
int* findClosedNumbers(int num, int* returnSize) {
  int* res = malloc(sizeof(int) * 2);
  res[0] = res[1] = -1;
  *returnSize = 2;
  int bits = cntbit(num);
  printf("%d\r\n", bits);
  long n;
  if (num == 2147483647)
    return res;  // 特殊情况特殊考虑；
  else if (num < 2147483647) {
    for (n = num + 1; n <= 2147483647; n++) {
      if (cntbit(n) == bits) {
        res[0] = n;
        break;
      }
    }
    for (n = num - 1; n >= 0; n--) {
      if (cntbit(n) == bits) {
        res[1] = n;
        break;
      }
    }
  }

  return res;
}