/*
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
输入一个数组，求出这个数组中的逆序对的总数。

示例1:
输入: [7,5,6,4]
输出: 5

限制：0 <= 数组长度 <= 50000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 离散化树状数组

// 归并排序
// 时间复杂度：同归并排序O(nlog⁡n)
// 空间复杂度：同归并排序O(n)
void print(int *nums, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");
}
int count;  // 统计最后个数，排序时不用
void Merge(int *nums, int left, int mid, int right) {
  int temp[right - left + 1];
  int l = left;
  int r = mid + 1;
  int i = 0;

  // [left ...l... mid | mid + 1 ...r... right]

  while (l <= mid || r <= right) {
    if (l > mid) {
      temp[i++] = nums[r++];
    } else if (r > right) {
      temp[i++] = nums[l++];
      // 此时要选择nums[l]，r-(mid+1)表示右边已经被排序的元素的个数，
      // nums[l]比之前选择的r-(mid+1)个右边元素都大，就有r-(mid+1)个逆序对
      count += r - (mid + 1);
    } else if (nums[l] > nums[r]) {
      temp[i++] = nums[r++];
    } else {
      temp[i++] = nums[l++];
      count += r - (mid + 1);  // 同上，排序时不需要
    }
  }
  memcpy(nums + left, temp, (right - left + 1) * sizeof(int));
}
void MergeSorting(int *nums, int left, int right) {
  if (left == right) {
    return;
  }

  int mid = left + (right - left) / 2;
  MergeSorting(nums, left, mid);
  MergeSorting(nums, mid + 1, right);
  Merge(nums, left, mid, right);
}

int reversePairs(int *nums, int numsSize) {
  if (numsSize <= 1) {
    return 0;
  }
  count = 0;
  MergeSorting(nums, 0, numsSize - 1);
  return count;
}

int main() {
  int nums[] = {7, 5, 6, 4};
  printf("%d\n", reversePairs(nums, sizeof(nums) / sizeof(int)));

  MergeSorting(nums, 0, sizeof(nums) / sizeof(int) - 1);
  print(nums, sizeof(nums) / sizeof(int));

  return 0;
}