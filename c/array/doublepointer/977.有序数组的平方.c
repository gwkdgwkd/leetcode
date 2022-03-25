/*
给你一个按非递减顺序排序的整数数组nums，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

示例1：
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为[16,1,0,9,100]
排序后，数组变为[0,1,9,16,100]

示例2：
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]

提示：
1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums已按非递减顺序排序

 

进阶：请你设计时间复杂度为O(n)的算法解决本问题
*/

// 双指针，时间复杂度为O(n)
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
  int* ans = malloc(sizeof(int) * numsSize);
  *returnSize = numsSize;
  for (int i = 0, j = numsSize - 1, pos = numsSize - 1; i <= j;) {
    if (nums[i] * nums[i] > nums[j] * nums[j]) {
      ans[pos] = nums[i] * nums[i];
      ++i;
    } else {
      ans[pos] = nums[j] * nums[j];
      --j;
    }
    --pos;
  }
  return ans;
}
