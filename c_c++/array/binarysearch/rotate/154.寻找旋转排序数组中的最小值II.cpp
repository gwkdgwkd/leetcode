/*
已知一个长度为n的数组，预先按照升序排列，经由1到n次旋转后，得到输入数组。
例如，原数组nums = [0,1,4,4,5,6,7]在变化后可能得到：
若旋转4次，则可以得到[4,5,6,7,0,1,4]
若旋转7次，则可以得到[0,1,4,4,5,6,7]
注意，数组[a[0],a[1],a[2],...,a[n-1]]旋转一次的结果为：
     数组[a[n-1],a[0],a[1],a[2],...,a[n-2]]。
给你一个可能存在重复元素值的数组nums，它原来是一个升序排列的数组，
并按上述情形进行了多次旋转。
请找出并返回数组中的最小元素，必须尽可能减少整个过程的操作步骤。

示例1：
输入：nums = [1,3,5]
输出：1

示例2：
输入：nums = [2,2,2,0,1]
输出：0

提示：
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums原来是一个升序排序的数组，并进行了1至n次旋转

进阶：这道题与寻找旋转排序数组中的最小值类似，但nums可能包含重复元素。
允许重复会影响算法的时间复杂度吗？会如何影响，为什么？
*/

// 剑指Offer11旋转数组的最小数字

// 时间复杂度：平均时间复杂度为O(log⁡n)
// 而在最坏情况下，如果数组中的元素完全相同，时间复杂度为O(n)
// 空间复杂度：O(1)
int findMin(int* nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < nums[right]) {
      right = mid;
    } else if (nums[mid] > nums[right]) {
      left = mid + 1;
    } else {
      // 由于重复元素的存在，并不能确定nums[mid]究竟在最小值的左侧还是右侧，
      // 因此不能莽撞地忽略某一部分的元素。
      // 唯一可以知道的是，由于它们的值相同，所以无论nums[right]是不是最小值，
      // 都有一个它的替代品nums[mid]，因此可以忽略二分查找区间的右端点。
      --right;
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
      } else if (nums[mid] > nums[right]) {
        left = mid + 1;
      } else {
        // 本题与153的区别在于有相同元素，这会导致在二分查找时，
        // mid元素可能与数组末尾元素相同，此时无法确定答案在左半区间还是右半区间。
        // 当二分元素nums[mid]与区间右端点元素相同时，既然无法确定最小值所在区间，
        // 那么干脆去掉右端点元素，继续二分，这样做不会碰巧把最小值给去掉吗？
        // 这是不会的：
        // 1.如果右端点元素就是最小值，那么nums[mid]也是最小值，仍然在二分区间中；
        // 2.如果右端点元素不是最小值，这样做相当于排除了一个错误答案。
        --right;
      }
    }

    return nums[left];
  }
};