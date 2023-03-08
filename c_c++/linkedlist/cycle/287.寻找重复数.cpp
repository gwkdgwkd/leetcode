/*
给定一个包含n+1个整数的数组nums，其数字都在[1,n]范围内（包括1和n），
可知至少存在一个重复的整数，假设nums只有一个重复的整数，返回这个重复的数。
设计的解决方案必须不修改数组nums且只用常量级O(1)的额外空间。

示例1：
输入：nums = [1,3,4,2,2]
输出：2

示例2：
输入：nums = [3,1,3,4,2]
输出：3

提示：
1 <= n <= 10^5
nums.length == n + 1
1 <= nums[i] <= n
nums中只有一个整数出现两次或多次，其余整数均只出现一次

进阶：
如何证明nums中至少存在一个重复的数字?
你可以设计一个线性级时间复杂度O(n)的解决方案吗？
*/

// 看着和136、268相似，但由于可能存在多个重复的数字，不能用异或来求解

// 暴力法，超时
int findDuplicate(int* nums, int numsSize) {
  for (int i = 0; i < numsSize - 1; ++i) {
    for (int j = i + 1; j < numsSize; ++j) {
      if (nums[i] == nums[j]) {
        return nums[i];
      }
    }
  }
  return 0;
}

// 快慢指针
// Floyd判圈算法，又称龟兔赛跑算法。
// 对nums数组建图，每个位置i连一条i→nums[i]的边。
// 由于存在的重复的数字target，因此target这个位置一定有起码两条指向它的边，
// 因此整张图一定存在环，且要找到的target就是这个环的入口，那么就等价于142题。
// 先设置慢指针slow和快指针fast，慢指针每次走一步，快指针每次走两步，
// 根据Floyd判圈算法两个指针在有环的情况下一定会相遇，
// 此时再将slow放到起点，两个指针每次同时移动一步，相遇点就是答案。
int findDuplicate(int* nums, int numsSize) {
  int slow = 0, fast = 0;
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (slow != fast);
  slow = 0;
  while (slow != fast) {
    slow = nums[slow];
    fast = nums[fast];
  }
  return slow;
}

class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    int slow = 0;
    int fast = 0;
    do {
      slow = nums[slow];
      fast = nums[nums[fast]];
    } while (slow != fast);

    slow = 0;
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[fast];
    }

    return slow;
  }
};
