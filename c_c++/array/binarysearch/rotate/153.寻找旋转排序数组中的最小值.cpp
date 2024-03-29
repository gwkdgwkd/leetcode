/*
已知一个长度为n的数组，预先按照升序排列，经由1到n次旋转后，得到输入数组。
例如，原数组nums = [0,1,2,4,5,6,7]在变化后可能得到：
若旋转4次，则可以得到[4,5,6,7,0,1,2]
若旋转7次，则可以得到[0,1,2,4,5,6,7]
注意，数组[a[0],a[1],a[2],...,a[n-1]]旋转一次的结果为数组：
[a[n-1],a[0],a[1],a[2],...,a[n-2]]。
给你一个元素值互不相同的数组nums，
它原来是一个升序排列的数组，并按上述情形进行了多次旋转。
请你找出并返回数组中的最小元素。
你必须设计一个时间复杂度为O(logn)的算法解决此问题。

示例1：
输入：nums = [3,4,5,1,2]
输出：1
解释：原数组为[1,2,3,4,5]，旋转3次得到输入数组。

示例2：
输入：nums = [4,5,6,7,0,1,2]
输出：0
解释：原数组为[0,1,2,4,5,6,7]，旋转4次得到输入数组。

示例3：
输入：nums = [11,13,15,17]
输出：11
解释：原数组为[11,13,15,17]，旋转4次得到输入数组。

提示：
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums中的所有整数互不相同
nums原来是一个升序排序的数组，并进行了1至n次旋转
*/

// 二分查找
int findMin(int* nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;

  // 与canfinish类型的题，写法一致
  while (left < right) {  // 不包括相等的情况
    int mid = left + (right - left) / 2;
    // canfinish简单，只是一条语句
    if (nums[mid] < nums[right]) {
      right = mid;
    } else {
      // 由于不存在重复元素，所以nums[mid]和nums[right]不会相等
      left = mid + 1;
    }
  }
  return nums[left];
}

class Solution {
 public:
  int findMin(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < nums[right]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return nums[left];
  }
};