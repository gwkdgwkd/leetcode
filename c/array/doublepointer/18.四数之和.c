// 四数之和的双指针解法是两层for循环nums[k]+nums[i]为确定值，依然是循环内有left和right下表作为双指针，
// 找出nums[k]+nums[i]+nums[left]+nums[right]==target的情况。
// 对于15.三数之和双指针法就是将原本暴力O(n^3)的解法，降为O(n^2)的解法，四数之和的双指针解法就是将原本暴力O(n^4)的解法，降为O(n^3)的解法。
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int **fourSum(int *nums, int numsSize, int target, int *returnSize,
              int **returnColumnSizes) {
  int **res = (int **)malloc(sizeof(int *) * numsSize * numsSize * numsSize);
  *returnColumnSizes =
      (int *)malloc(sizeof(int) * numsSize * numsSize * numsSize);
  *returnSize = 0;

  qsort(nums, numsSize, sizeof(int), cmp);

  int left, right;
  for (int i = 0; i < numsSize - 3; ++i) {
    if (nums[i] + nums[i + 1] > target - nums[i + 2] - nums[i + 3]) {
      printf("%d\n", *returnSize);
      return res;
    }
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    for (int j = i + 1; j < numsSize - 2; ++j) {
      if (nums[i] + nums[j] > target - nums[j + 1] - nums[j + 2]) {
        break;
      }
      if (j > i + 1 && nums[j] == nums[j - 1]) {
        continue;
      }
      left = j + 1;
      right = numsSize - 1;
      while (left < right) {
        int sum = nums[i] + nums[j] + nums[left] + nums[right] - target;
        if (sum > 0) {
          right--;
        } else if (sum < 0) {
          left++;
        } else {
          res[*returnSize] = (int *)malloc(sizeof(int) * 4);
          res[*returnSize][0] = nums[i];
          res[*returnSize][1] = nums[j];
          res[*returnSize][2] = nums[left];
          res[*returnSize][3] = nums[right];
          (*returnColumnSizes)[*returnSize] = 4;
          (*returnSize)++;
          while (left < right && nums[left] == nums[++left])
            ;
          while (left < right && nums[right] == nums[--right])
            ;
        }
      }
    }
  }

  return res;
}