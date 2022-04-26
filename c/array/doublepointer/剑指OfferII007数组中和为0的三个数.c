/*
给定一个包含n个整数的数组nums，判断nums中是否存在三个元素a，b，c，使得a + b + c = 0？
请找出所有和为0且不重复的三元组。

示例1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]

示例2：
输入：nums = []
输出：[]

示例3：
输入：nums = [0]
输出：[]

提示：
0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5

注意：本题与15题相同
*/

int cmp(int *a, int *b) { return *a - *b; }
int **threeSum(int *nums, int numsSize, int *returnSize,
               int **returnColumnSizes) {
  if (nums == NULL || numsSize < 3) {
    *returnSize = 0;
    return NULL;
  }

  qsort(nums, numsSize, sizeof(int), cmp);

  int **res = (int **)malloc(sizeof(int *) * numsSize * numsSize);
  *returnColumnSizes = (int *)malloc(sizeof(int) * numsSize * numsSize);

  int idx = 0;
  for (int i = 0; i < numsSize - 2; ++i) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    int left = i + 1;
    int right = numsSize - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum < 0) {
        while (++left < right && nums[left] == nums[left - 1]) {
          continue;
        }
      } else if (sum > 0) {
        while (--right > left && nums[right] == nums[right + 1]) {
          continue;
        }
      } else {
        res[idx] = (int *)malloc(sizeof(int) * 3);
        (*returnColumnSizes)[idx] = 3;
        res[idx][0] = nums[i];
        res[idx][1] = nums[left];
        res[idx][2] = nums[right];
        ++idx;
        while (++left < right && nums[left] == nums[left - 1]) {
          continue;
        }
        while (--right > left && nums[right] == nums[right + 1]) {
          continue;
        }
      }
    }
  }

  *returnSize = idx;
  return res;
}