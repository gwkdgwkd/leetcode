/*
给定一个整数数组nums，处理以下类型的多个查询:
计算索引left和right（包含left和right）之间的nums元素的和，其中left<=right

实现NumArray类：
NumArray(int[] nums) 使用数组nums初始化对象
int sumRange(int i, int j)返回数组nums中索引left和right之间的元素的总和，
包含left和right两点（也就是nums[left]+nums[left + 1]+...+nums[right] )

示例1：
输入：
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
输出：
[null, 1, -1, -3]
解释：
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))

提示：
1 <= nums.length <= 104
-105 <= nums[i] <= 105
0 <= i <= j < nums.length
最多调用104次sumRange方法
*/

#include <stdio.h>
#include <stdlib.h>

// 前缀和主要适用的场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和
typedef struct {
  int* pre;
} NumArray;
NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray* na = (NumArray*)malloc(sizeof(NumArray));
  na->pre = (int*)calloc(numsSize + 1, sizeof(int));

  // for(int i = 1; i < numsSize + 1; ++i) {
  //     na->pre[i] = na->pre[i - 1] + nums[i - 1];
  // }
  for (int i = 0; i < numsSize; i++) {
    na->pre[i + 1] = na->pre[i] + nums[i];
  }

  return na;
}
int numArraySumRange(NumArray* obj, int left, int right) {
  return obj->pre[right + 1] - obj->pre[left];  // 查询闭区间[left,right]累加和
}
void numArrayFree(NumArray* obj) {
  free(obj->pre);
  free(obj);
}

int main() {
  int a[] = {-2, 0, 3, -5, 2, -1};
  NumArray* na = numArrayCreate(a, sizeof(a) / sizeof(int));
  for (int i = 0; i < sizeof(a) / sizeof(int) + 1; ++i) {
    printf("%d ", na->pre[i]);
  }
  printf("\n");
  // 0 -2 -2 1 -4 -2 -3

  printf("%d\n", numArraySumRange(na, 0, 2));  // 1
  printf("%d\n", numArraySumRange(na, 2, 5));  // -1
  printf("%d\n", numArraySumRange(na, 0, 5));  // -3
  numArrayFree(na);

  return 0;
}