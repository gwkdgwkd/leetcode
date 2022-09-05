/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

示例：
输入：nums = [1,2,3,4]
输出：[1,3,2,4]
注：[3,1,2,4]也是正确的答案之一。

提示：
0 <= nums.length <= 50000
0 <= nums[i] <= 10000
*/

int* exchange(int* nums, int numsSize, int* returnSize) {
  int left = 0;
  int right = numsSize - 1;
  while (left < right) {
    while (left < right && nums[right] % 2 == 0) {
      --right;
    }
    while (left < right && nums[left] % 2 == 1) {
      ++left;
    }

    if (left < right) {
      int tmp = nums[right];
      nums[right] = nums[left];
      nums[left] = tmp;
    }
    ++left;
    --right;
  }

  *returnSize = numsSize;
  return nums;
}

class Solution {
 public:
  vector<int> exchange(vector<int>& nums) {
    int len = nums.size();
    int left = 0;
    int right = len - 1;

    while (left < right) {
      while (left < len && nums[left] % 2) {
        ++left;
      }
      while (right > 0 && nums[right] % 2 == 0) {
        --right;
      }
      if (left < right) {
        swap(nums[left], nums[right]);
      }
      ++left;
      --right;
    }

    return nums;
  }
};