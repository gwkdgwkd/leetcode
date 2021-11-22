#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

// 回溯算法，以数字的视角，超时
// n个数字，每个数字有k个桶可供选择，所以组合出的结果个数为k^n，时间复杂度也就是O(k^n)。
int *bucket;
bool cmp(const void *a, const void *b) { return *(int *)a > *(int *)b; }
bool backtrack1(int *nums, int numsSize, int k, int index, int target) {
  if (index == numsSize) {
    // 检查所有桶的数字之和是否都是target
    for (int i = 0; i < k; ++i) {
      if (bucket[i] != target) {
        return false;
      }
    }
    return true;  // nums成功平分成k个子集
  }

  for (int i = 0; i < k; ++i) {  // 穷举nums[index]可能装入的桶
    if (bucket[i] + nums[index] > target) {  // 剪枝，桶装装满了
      continue;
    }

    bucket[i] += nums[index];  // 将nums[index]装入bucket[i]
    // 递归穷举下一个数字的选择
    if (backtrack1(nums, numsSize, k, index + 1, target)) {
      return true;
    }
    bucket[i] -= nums[index];  // 撤销选择
  }

  return false;  // nums[index]装入哪个桶都不行
}
bool canPartitionKSubsets1(int *nums, int numsSize, int k) {
  if (k > numsSize) {
    return false;
  }
  bucket = (int *)calloc(k, sizeof(int));

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % k) {
    return false;
  }

  qsort(nums, numsSize, sizeof(int), cmp);

  return backtrack1(nums, numsSize, k, 0, sum / k);
}

// 回溯算法，从桶的视角
// 每个桶要遍历n个数字，选择「装入」或「不装入」，组合的结果有2^n种；而我们有k个桶，所以总的时间复杂度为O(k*2^n)。
// 当然，这是理论上的最坏复杂度，实际的复杂度肯定要好一些，毕竟我们添加了这么多剪枝逻辑。不过，从复杂度的上界已经可以看出第一种思路要慢很多了。
// 通俗来说，我们应该尽量「少量多次」，就是说宁可多做几次选择，也不要给太大的选择空间；宁可「二选一」选k次，也不要「k选一」选一次。
bool *used;
bool backtrack2(int *nums, int numsSize, int k, int start, int target,
                int bucket) {
  // base case
  if (k == 0) {
    // 所有桶都被装满了，而且nums一定全部用完了，因为target == sum / k
    return true;
  }
  if (bucket == target) {
    // 装满了当前桶，递归穷举下一个桶的选择，让下一个桶从nums[0]开始选数字
    return backtrack2(nums, numsSize, k - 1, 0, target, 0);
  }

  // 从start开始向后探查有效的nums[i]装入当前桶
  for (int i = start; i < numsSize; i++) {
    // 剪枝
    if (used[i]) {
      continue;  // nums[i]已经被装入别的桶中
    }
    if (nums[i] + bucket > target) {
      continue;  // 当前桶装不下nums[i]
    }
    // 做选择，将nums[i]装入当前桶中
    used[i] = true;
    bucket += nums[i];
    // 递归穷举下一个数字是否装入当前桶
    if (backtrack2(nums, numsSize, k, i + 1, target, bucket)) {
      return true;
    }
    // 撤销选择
    used[i] = false;
    bucket -= nums[i];
  }
  // 穷举了所有数字，都无法装满当前桶
  return false;
}
bool canPartitionKSubsets2(int *nums, int numsSize, int k) {
  if (k > numsSize) {
    return false;
  }
  used = (bool *)calloc(numsSize, sizeof(bool));

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % k) {
    return false;
  }

  return backtrack2(nums, numsSize, k, 0, sum / k, 0);
}

int main() {
  int nums1[] = {3522, 181, 521, 515,  304,  123,  2512, 312,
                 922,  407, 146, 1932, 4037, 2646, 3871, 269};

  printf("%d\n", canPartitionKSubsets1(nums1, sizeof(nums1) / sizeof(int), 5));
  printf("%d\n", canPartitionKSubsets2(nums1, sizeof(nums1) / sizeof(int), 5));
  int nums2[] = {2240, 3029, 520,  203, 1908, 505,  2600, 739,
                 696,  345,  1197, 76,  394,  2902, 1276};
  printf("%d\n", canPartitionKSubsets1(nums2, sizeof(nums2) / sizeof(int), 6));
  printf("%d\n", canPartitionKSubsets2(nums2, sizeof(nums2) / sizeof(int), 6));

  return 0;
}