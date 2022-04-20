/*
输入数字n，按顺序打印出从1到最大的n位十进制数。
比如输入3，则打印出1、2、3一直到最大的3位数999。

示例1:
输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]

说明：
用返回一个整数列表来代替打印
n为正整数
*/

int* printNumbers(int n, int* returnSize) {
  int len = 1;
  for (int i = 0; i < n; ++i) {
    len *= 10;
  }

  int* res = (int*)malloc(sizeof(int) * (len - 1));

  for (int i = 0; i < len - 1; ++i) {
    res[i] = i + 1;
  }

  *returnSize = len - 1;

  return res;
}