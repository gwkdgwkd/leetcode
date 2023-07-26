/*
假设你有一个长度为n的数组，初始情况下所有的数字均为0，你将会被给出k个更新的操作。
其中，每个操作会被表示为一个三元组：[startIndex,endIndex,inc]，
你需要将子数组A[startIndex...endIndex]（包括startIndex和endIndex）增加inc。
请你返回k次操作后的数组。

示例：
输入：length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
输出：[-2,0,3,5,3]
解释：
初始状态：[0,0,0,0,0]
进行了操作[1,3,2]后的状态：[0,2,2,2,0]
进行了操作[2,4,3]后的状态：[0,2,5,5,3]
进行了操作[0,2,-2]后的状态：[-2,0,3,5,3]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int *p, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d ", p[i]);
  }
  printf("\n");
}

// 差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减
typedef struct Difference {
  int *diff;
  int size;
} Difference;
Difference *createDifference(int *nums, int numsSize) {
  if (numsSize <= 0) {
    return NULL;
  }
  Difference *d = (Difference *)malloc(sizeof(Difference));
  d->diff = (int *)malloc(sizeof(int) * numsSize);
  d->size = numsSize;
  d->diff[0] = nums[0];
  for (int i = 1; i < numsSize; ++i) {
    d->diff[i] = nums[i] - nums[i - 1];
  }

  print(nums, numsSize);  // 0 0 0 0 0
  return d;
}
void increment(int i, int j, int val, Difference *d) {
  // 只要花费O(1)的时间修改diff数组，就相当于给nums的整个区间做了修改
  d->diff[i] += val;  // 从i以后，所有的值都加上val
  if (j + 1 < d->size) {
    d->diff[j + 1] -= val;  // 从j+1以后，所有的值都减去val
  }
  // [i...j]内的元素都加上了val

  // j+1>=d->size说明是对nums[i]及以后的整个数组都进行修改，
  // 那么就不需要再给diff数组减val了
}
int *result(Difference *d) {
  int *res = (int *)malloc(sizeof(int) * d->size);
  res[0] = d->diff[0];
  for (int i = 1; i < d->size; ++i) {
    res[i] = res[i - 1] + d->diff[i];
  }

  return res;
}
int *getModifiedArray(int updates[][3], int updatesSize, int *nums, int len) {
  Difference *d = createDifference(nums, len);

  for (int i = 0; i < updatesSize; ++i) {
    increment(updates[i][0], updates[i][1], updates[i][2], d);
    print(d->diff, d->size);
  }
  // 0 2 0 0 -2
  // 0 2 3 0 -2
  // -2 2 3 2 -2

  return result(d);
}

int main() {
  int data[3][3] = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};

  int len = 5;
  int *a = (int *)malloc(len * (sizeof(int)));
  memset(a, 0, sizeof(int) * len);

  int *ret = getModifiedArray(data, 3, a, len);

  print(ret, len);  // -2 0 3 5 3
}
