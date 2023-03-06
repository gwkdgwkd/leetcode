/*
给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，
唯有一个数只会出现一次，请你找出并返回只出现一次的那个数。
你设计的解决方案必须满足O(logn)时间复杂度和O(1)空间复杂度。

示例1:
输入: nums = [1,1,2,3,3,4,4,8,8]
输出: 2

示例2:
输入: nums = [3,3,7,7,10,11,11]
输出: 10

提示:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
*/

// 剑指OfferII070排序数组中只出现一次的数字

// 全数组的二分查找
// 假设只出现一次的元素位于下标x，由于其余每个元素都出现两次，
// 因此下标x的左边和右边都有偶数个元素，数组的长度是奇数。
int singleNonDuplicate(int* nums, int numsSize) {
  int low = 0, high = numsSize - 1;
  while (low < high) {
    int mid = (high - low) / 2 + low;
    // 根据mid的奇偶性决定和左边或右边的相邻元素比较：
    // 如果mid是偶数，则比较nums[mid]和nums[mid+1]是否相等；
    // 如果mid是奇数，则比较nums[mid−1]和nums[mid]是否相等。
    if (nums[mid] == nums[mid ^ 1]) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return nums[low];
}

// 偶数下标的二分查找
// 由于只出现一次的元素所在下标x的左边有偶数个元素，
// 因此下标x一定是偶数，可以在偶数下标范围内二分查找。
// 二分查找的目标是找到满足nums[x]=nums[x+1]的最小的偶数下标x，
// 则下标x处的元素是只出现一次的元素。
int singleNonDuplicate(int* nums, int numsSize) {
  int low = 0, high = numsSize - 1;
  while (low < high) {
    int mid = (high - low) / 2 + low;
    // 将mid的值减去mid&1，即可确保mid是偶数，
    // 如果原来的mid是偶数则值不变，如果原来的mid是奇数则值减1
    mid -= mid & 1;
    if (nums[mid] == nums[mid + 1]) {
      low = mid + 2;
    } else {
      high = mid;
    }
  }
  return nums[low];
}

// 位运算
int singleNonDuplicate(int* nums, int numsSize) {
  int res = 0;
  for (int i = 0; i < numsSize; ++i) {
    res ^= nums[i];
  }
  return res;
}

class Solution {
 public:
  int singleNonDuplicate(vector<int>& nums) {
    int ans = 0;
    for (int num : nums) {
      ans ^= num;
    }
    return ans;
  }
};

class Solution {
 public:
  int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
      int mid = (high - low) / 2 + low;
      if (nums[mid] == nums[mid ^ 1]) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return nums[low];
  }
};
