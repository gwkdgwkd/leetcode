/*
输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
如果有多对数字的和等于s，则输出任意一对即可。

示例1：
输入：nums = [2,7,11,15], target = 9
输出：[2,7]或者[7,2]

示例2：
输入：nums = [10,26,30,31,47,60], target = 40
输出：[10,30]或者[30,10]

限制：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
*/

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int left = 0;
  int right = numsSize - 1;

  while (left <= right) {
    if (nums[left] + nums[right] < target) {
      ++left;
    } else if (nums[left] + nums[right] > target) {
      --right;
    } else {
      break;
    }
  }

  *returnSize = 2;
  int* res = (int*)malloc(sizeof(int) * 2);
  res[0] = nums[left];
  res[1] = nums[right];

  return res;
}

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int sum = nums[left] + nums[right];
      if (sum < target) {
        ++left;
      } else if (sum > target) {
        --right;
      } else {
        return {nums[left], nums[right]};
      }
    }

    return {};
  }
};
