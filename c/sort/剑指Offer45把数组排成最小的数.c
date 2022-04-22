/*
输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

示例1:
输入: [10,2]
输出: "102"

示例2:
输入: [3,30,34,5,9]
输出: "3033459"

提示: 0 < nums.length <= 100

说明:
输出结果可能非常大，所以你需要返回一个字符串而不是整数
拼接起来的数字可能会有前导0，最后结果不需要去掉前导0
*/

int cmp(int *x, int *y) {
  long sx = 10, sy = 10;
  while (sx <= *x) {
    sx *= 10;
  }
  while (sy <= *y) {
    sy *= 10;
  }

  return sy * (*x) + (*y) - sx * (*y) - (*x);  // 升序
}
char *minNumber(int *nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);
  int len = 100 * 14 + 1;
  char *res = (char *)malloc(sizeof(char) * len);
  memset(res, 0, sizeof(char) * len);
  for (int i = 0; i < numsSize; ++i) {
    sprintf(res + strlen(res), "%d", nums[i]);
  }

  return res;
}