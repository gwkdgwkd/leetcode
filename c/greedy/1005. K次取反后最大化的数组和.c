// 贪心算法
int cmp(void *a, void *b) { return abs(*(int *)b) - abs(*(int *)a); }
int largestSumAfterKNegations(int *nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), cmp);

  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] < 0 && k > 0) {
      nums[i] *= -1;
      --k;
    }
  }

  while (k--) {
    nums[numsSize - 1] *= -1;
  }

  int ret = 0;
  for (int i = 0; i < numsSize; ++i) {
    ret += nums[i];
  }

  return ret;
}