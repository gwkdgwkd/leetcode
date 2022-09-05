/*
给定一个数组nums，编写一个函数将所有0移动到数组的末尾，
同时保持非零元素的相对顺序。
请注意，必须在不复制数组的情况下原地对数组进行操作。

示例1:
输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]

示例2:
输入: nums = [0]
输出: [0]

提示:
1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1

进阶：你能尽量减少完成的操作次数吗？
*/

// 双指针
void moveZeroes(int* nums, int numsSize) {
  int slow = 0;
  for (int fast = 0; fast < numsSize; ++fast) {
    if (nums[fast] != 0) {
      nums[slow++] = nums[fast];
    }
  }

  for (int i = slow; i < numsSize; ++i) {
    nums[i] = 0;
  }
}

// 27题，删除元素
int removeElement(int* nums, int numsSize, int val) {
  if (numsSize == 0) return 0;
  int slow = 0;
  int fast = 0;
  while (fast < numsSize) {
    if (nums[fast] != val) {
      nums[slow++] = nums[fast];
    }
    fast++;
  }

  return slow;
}
// 复用删除元素的函数
void moveZeroes(int* nums, int numsSize) {
  int i = removeElement(nums, numsSize, 0);
  while (i < numsSize) {
    nums[i++] = 0;
  }
}

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int slow = 0;
    int fast = 0;
    int len = nums.size();

    while (fast < len) {
      if (nums[fast] != 0) {
        nums[slow++] = nums[fast];
      }
      ++fast;
    }

    while (slow < len) {
      nums[slow++] = 0;
    }
  }
};
