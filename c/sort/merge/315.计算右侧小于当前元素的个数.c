/*
给你一个整数数组nums，按要求返回一个新数组counts。
数组counts有该性质：counts[i]的值是nums[i]右侧小于nums[i]的元素的数量。

示例1：
输入：nums = [5,2,6,1]
输出：[2,1,1,0] 
解释：
5的右侧有2个更小的元素(2和1)
2的右侧仅有1个更小的元素(1)
6的右侧有1个更小的元素(1)
1的右侧有0个更小的元素

示例2：
输入：nums = [-1]
输出：[0]

示例3：
输入：nums = [-1,-1]
输出：[0,0]

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 离散化树状数组

// 归并排序
typedef struct {
  int index;
  int value;
  int cnt;
} Data;
void print(Data* data, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d(%d,%d) ", data[i].value, data[i].index, data[i].cnt);
  }
  printf("\n");
}

void Merge(Data* numbers, int left, int mid, int right) {
  // tmpArr保存left-right区间内排序后的结果，然后回填给numbers
  Data tmpArr[right - left + 1];
  int lleft = left;
  int rleft = mid + 1;
  int k = 0;
  while (lleft <= mid || rleft <= right) {
    if (rleft > right) {  // 右侧取完
      tmpArr[k++] = numbers[lleft++];
    } else if (lleft > mid) {  // 左侧取完
      tmpArr[k++] = numbers[rleft++];
    } else if (numbers[lleft].value > numbers[rleft].value) {
      // 左边大于右边，把右边比左小的数量加给左边
      numbers[lleft].cnt += right - rleft + 1;
      tmpArr[k++] = numbers[lleft++];
    } else {  // 右边大于等于左边
      tmpArr[k++] = numbers[rleft++];
    }
  }

  for (int i = 0; i < k; i++) {
    numbers[left++] = tmpArr[i];
  }
  print(tmpArr, right - left + 1);

  return;
}

void MergeSorting(Data* numbers, int left, int right) {
  if (left == right) {
    return;
  }

  int mid = left + (right - left) / 2;
  MergeSorting(numbers, left, mid);
  MergeSorting(numbers, mid + 1, right);
  Merge(numbers, left, mid, right);
  return;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
  // 通过归并排序求解，排序过程中index会变化，需要保存原始index值
  Data* numbers = (Data*)malloc(sizeof(Data) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    numbers[i].index = i;
    numbers[i].value = nums[i];
    numbers[i].cnt = 0;
  }

  MergeSorting(numbers, 0, numsSize - 1);
  int* counts = (int*)malloc(sizeof(int) * numsSize);
  memset(counts, 0, sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    counts[numbers[i].index] = numbers[i].cnt;
  }
  *returnSize = numsSize;
  return counts;
}

int main() {
  int nums[] = {5, 2, 6, 1};

  int size;
  int* result = countSmaller(nums, sizeof(nums) / sizeof(int), &size);

  for (int i = 0; i < size; ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");

  return 0;
}