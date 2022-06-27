/*
给你一个整数数组nums和一个整数k，按以下方法修改该数组：
选择某个下标i并将nums[i]替换为-nums[i]。
重复这个过程恰好k次。可以多次选择同一个下标i。
以这种方式修改数组后，返回数组可能的最大和。

示例1：
输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标1，nums变为[4,-2,3] 。

示例2：
输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标(1, 2, 2)，nums变为[3,1,0,2]。

示例3：
输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标(1, 4)，nums变为[2,3,-1,5,4]。

提示：
1 <= nums.length <= 10^4
-100 <= nums[i] <= 100
1 <= k <= 10^4
*/

// 贪心算法
int cmp(void *a, void *b) { return abs(*(int *)b) - abs(*(int *)a); }
int largestSumAfterKNegations(int *nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), cmp);  // 5,-4,-3,2,-1

  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] < 0 && k > 0) {  // 从大到小，把负数变正数
      nums[i] *= -1;
      --k;
    }
  }

  while (k--) {  // k还有剩余，一直用最小的数变来变去
    nums[numsSize - 1] *= -1;
  }

  int ret = 0;
  for (int i = 0; i < numsSize; ++i) {
    ret += nums[i];
  }

  return ret;
}