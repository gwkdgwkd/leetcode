/*
给你一个整数数组nums，将它重新排列成nums[0] < nums[1] > nums[2] < nums[3]... 的顺序。
你可以假设所有输入数组都可以得到满足题目要求的结果。

示例1：
输入：nums = [1,5,1,1,6,4]
输出：[1,6,1,5,1,4]
解释：[1,4,1,5,1,6]同样是符合题目要求的结果，可以被判题程序接受。

示例2：
输入：nums = [1,3,2,2,3,1]
输出：[2,3,1,3,1,2]

提示：
1 <= nums.length <= 5 * 104
0 <= nums[i] <= 5000
题目数据保证，对于给定的输入nums，总能产生满足题目要求的结果
进阶：你能用O(n)时间复杂度和/或原地O(1)额外空间来实现吗？
*/

// 快速排序
int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
void wiggleSort(int* nums, int numsSize) {
  int i, l, r;
  int* ret = (int*)malloc(sizeof(int) * numsSize);
  for (i = 0; i < numsSize; ++i) {
    ret[i] = nums[i];
  }
  qsort(ret, numsSize, sizeof(int), cmp);
  r = numsSize - 1;
  for (i = 1; i < numsSize; i += 2) {
    nums[i] = ret[r--];
  }
  for (i = 0; i < numsSize; i += 2) {
    nums[i] = ret[r--];
  }
}

// 桶排序
#define MAX_BUCKET 5001
void wiggleSort(int* nums, int numsSize) {
  int i;
  int* bucket = (int*)malloc(MAX_BUCKET * sizeof(int));
  if (bucket == NULL || nums == NULL || numsSize < 2) return;

  memset(bucket, 0, MAX_BUCKET * sizeof(int));
  for (i = 0; i < numsSize; i++) bucket[nums[i]]++;

  int half = numsSize % 2 ? (numsSize / 2 + 1) : (numsSize / 2);
  i = 0;
  for (int odd = half - 1; odd >= 0; odd--) {
    while (i < MAX_BUCKET && bucket[i] == 0) {
      i++;
    }
    nums[odd * 2] = i;
    bucket[i]--;
  }

  for (int even = numsSize - half - 1; even >= 0; even--) {
    while (i < MAX_BUCKET && bucket[i] == 0) {
      i++;
    }
    nums[even * 2 + 1] = i;
    bucket[i]--;
  }
}