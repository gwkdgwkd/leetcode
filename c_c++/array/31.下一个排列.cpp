/*
整数数组的一个排列就是将其所有成员以序列或线性顺序排列。
例如，arr =
[1,2,3]，以下这些都可以视作arr的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1]。
整数数组的下一个排列是指其整数的下一个字典序更大的排列。
更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，
那么数组的下一个排列就是在这个有序容器中排在它后面的那个排列。
如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。
例如，arr = [1,2,3]的下一个排列是[1,3,2]。
类似地，arr = [2,3,1]的下一个排列是[3,1,2]。
而arr = [3,2,1]的下一个排列是[1,2,3]，因为[3,2,1]不存在一个字典序更大的排列。
给你一个整数数组nums，找出nums的下一个排列。
必须原地修改，只允许使用额外常数空间。

示例1：
输入：nums = [1,2,3]
输出：[1,3,2]

示例2：
输入：nums = [3,2,1]
输出：[1,2,3]

示例3：
输入：nums = [1,1,5]
输出：[1,5,1]

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

// 我们需要将一个左边的较小数与一个右边的较大数交换，
// 以能够让当前排列变大，从而得到下一个排列。
// 同时我们要让这个较小数尽量靠右，而较大数尽可能小。
// 当交换完成后，较大数右边的数需要按照升序重新排列。
// 这样可以在保证新排列大于原来排列的情况下，使变大的幅度尽可能小。
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void reverse(int *nums, int left, int right) {
  while (left < right) {
    swap(nums + left, nums + right);
    ++left;
    --right;
  }
}
void nextPermutation(int *nums, int numsSize) {
  // 首先从后向前查找第一个顺序对(i,i+1)，满足a[i]<a[i+1]，
  // 这样较小数即为a[i]，此时[i+1,n)必然是下降序列，
  // 也就是说，从后往前找，找到第一个下降的元素，
  int i;
  for (i = numsSize - 2; i >= 0; --i) {
    if (nums[i] < nums[i + 1]) {
      break;
    }
  }

  if (i >= 0) {
    // 如果找到了顺序对，那么在区间[i+1,n)中从后向前查找第一个元素j满足a[i]<a[j]，
    // 这样较大数即为a[j]
    int j;
    for (j = numsSize - 1; j > i; --j) {
      if (nums[j] > nums[i]) {
        swap(nums + j, nums + i);
        break;
      }
    }
  }

  // 交换a[i]与a[j]，此时可以证明区间[i+1,n)必为降序。
  // 可以直接使用双指针反转区间[i+1,n)使其变为升序，而无需对该区间进行排序
  reverse(nums, i + 1, numsSize - 1);
}

// 两遍扫描
class Solution {
 public:
  void nextPermutation(vector<int> &nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      i--;
    }
    if (i >= 0) {
      int j = nums.size() - 1;
      while (j >= 0 && nums[i] >= nums[j]) {
        j--;
      }
      swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
  }
};