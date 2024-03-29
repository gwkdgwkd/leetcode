/*
魔术索引。在数组A[0...n-1]中，有所谓的魔术索引，满足条件A[i]=i。
给定一个有序整数数组，编写一种方法找出魔术索引，
若有的话，在数组A中找出一个魔术索引，如果没有，则返回-1。
若有多个魔术索引，返回索引值最小的一个。

示例1：
输入：nums = [0, 2, 3, 4, 5]
输出：0
说明：0下标的元素为0

示例2：
输入：nums = [1, 1, 1]
输出：1

说明：
nums长度在[1,1000000]之间
此题为原书中的Follow-up，即数组中可能包含重复元素的版本
*/

// 跳跃查找
int findMagicIndex(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] == i) return i;
    if (nums[i] > i) i = nums[i] - 1;  // 后面的数都比这个大
  }
  return -1;
}

// 二分查找
// 与[面试题1003搜索旋转数组]类似，都是找索引值最小的那个，
// 所以按顺序搜索左边区间，中间元素，右边区间。
int* g_nums;
int find(int start, int end) {
  if (start > end) {
    return -1;
  }
  int half = (start + end) / 2;
  int res = -1;
  res = find(start, half - 1);
  if (res != -1) {
    return res;
  } else if (g_nums[half] == half) {
    return half;
  } else {
    res = find(half + 1, end);
  }
  return res;
}
int findMagicIndex(int* nums, int numsSize) {
  g_nums = nums;
  return find(0, numsSize - 1);
}

class Solution {
 public:
  int find(vector<int>& nums, int left, int right) {
    if (left > right) {
      return -1;
    }
    int mid = left + (right - left) / 2;

    int res = -1;
    if ((res = find(nums, left, mid - 1)) >= 0) {
      return res;
    }

    if (nums[mid] == mid) {
      return mid;
    }

    return find(nums, mid + 1, right);
  }
  int findMagicIndex(vector<int>& nums) {
    return find(nums, 0, nums.size() - 1);
  }
};
