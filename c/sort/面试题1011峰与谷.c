/*
在一个整数数组中，“峰”是大于或等于相邻整数的元素，相应地，“谷”是小于或等于相邻整数的元素。
例如，在数组{5, 8, 4, 2, 3, 4, 6}中，{8, 6}是峰，{5,2}是谷。
现在给定一个整数数组，将该数组按峰与谷的交替顺序排序。

示例:
输入: [5, 3, 1, 2, 3]
输出: [5, 1, 3, 2, 3]

提示：nums.length <= 10000
*/

// 排序后两两交换
int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
void wiggleSort(int *nums, int numsSize) {
  if (numsSize <= 1) {
    return;
  }
  qsort(nums, numsSize, sizeof(int), cmp);
  int i = 0;
  int max = numsSize - 1;
  int tmp;
  while (i < max) {
    tmp = nums[i];
    nums[i] = nums[i + 1];
    nums[i + 1] = tmp;

    i += 2;
  }
}

// 奇偶判断
void Swap(int *a, int *b) {
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}
void wiggleSort(int *nums, int numsSize) {
  for (int i = 0; i < numsSize - 1; i++) {
    if (i % 2 == 0) {
      if (nums[i] < nums[i + 1]) {
        Swap(&nums[i], &nums[i + 1]);
      }
    } else {
      if (nums[i] > nums[i + 1]) {
        Swap(&nums[i], &nums[i + 1]);
      }
    }
  }
}