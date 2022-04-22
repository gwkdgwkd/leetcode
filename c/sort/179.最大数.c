/*
给定一组非负整数nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。

示例1：
输入：nums = [10,2]
输出："210"

示例2：
输入：nums = [3,30,34,5,9]
输出："9534330"

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 109
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 按每位数字的大小排序，不是按数字大小排序
long cmp(int *x, int *y) {
  long sx = 10, sy = 10;
  while (sx <= *x) {
    sx *= 10;
  }
  while (sy <= *y) {
    sy *= 10;
  }

  // printf("sx:%ld,sy:%ld\n", sx, sy);
  // printf("(%d*%ld+%d)-(%d*%ld+%d)=%ld\n", sx, *y, *x, sy, *x, *y,
  //        sx * (*y) + (*x) - sy * (*x) - (*y));
  return sx * (*y) + (*x) - sy * (*x) - (*y);  // 降序
}
char *largestNumber(int *nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);

  // for (int i = 0; i < numsSize; ++i) {
  //   printf("%d", nums[i]);
  // }
  // printf("\n");

  if (nums[0] == 0) {
    char *ret = malloc(sizeof(char) * 2);
    ret[0] = '0', ret[1] = '\0';
    return "0";
  }
  char *ret = malloc(sizeof(char) * 1000);
  char *p = ret;
  for (int i = 0; i < numsSize; i++) {
    sprintf(p, "%d", nums[i]);
    p += strlen(p);
  }
  return ret;
}

int main() {
  int nums[] = {3, 30, 34, 5, 9};
  largestNumber(nums, sizeof(nums) / sizeof(int));

  cmp(nums + 0, nums + 1);  // 3, 30
  // sx:10,sy:100
  // (10*30+3)-(100*3+30)=-27
  cmp(nums + 0, nums + 2);  // 3, 34
  // sx:10,sy:100
  // (10*34+3)-(100*3+34)=9
  cmp(nums + 1, nums + 2);  // 30, 34
  // sx:100,sy:100
  // (100*34+30)-(100*30+34)=396

  return 0;
}