/*
 * @lc app=leetcode.cn id=283 lang=c
 *
 * [283] 移动零
 */

// @lc code=start

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
  for (; i < numsSize; ++i) {
    nums[i] = 0;
  }
}
// @lc code=end
