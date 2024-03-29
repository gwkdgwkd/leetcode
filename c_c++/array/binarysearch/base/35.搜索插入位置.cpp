/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为O(logn)的算法。

示例1:
输入: nums = [1,3,5,6], target = 5
输出: 2

示例2:
输入: nums = [1,3,5,6], target = 2
输出: 1

示例3:
输入: nums = [1,3,5,6], target = 7
输出: 4

提示:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums为无重复元素的升序排列数组
-10^4 <= target <= 10^4
*/

// 剑指OfferII068查找插入位置

// 704方法一
int searchInsert(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }
  // 用二分法查找如果找到了那还好说，但若是找不到呢？该怎么找到要顺序插入的下标呢？
  // 这个其实很简单，直接返回left就行，思路如下：

  // 第N-1轮：
  // target : 8
  // id     : 0     1     2     3     4     5
  // nums   : 1     3     5     7     9     11
  //                            ↑     ↑     ↑
  //                           left  mid  right

  // 第N轮：
  // target : 8
  // id     : 0     1     2     3     4     5
  // nums   : 1     3     5     7     9     11
  //                            ↑
  //                           left
  //                          right
  //                           mid

  // 第N+1轮：
  // target : 8
  // id     : 0     1     2     3     4     5
  // nums   : 1     3     5     7     9     11
  //                            ↑     ↑
  //                          right  left
  //                           mid

  // 跳出循环时，一定是第N+1轮left>right的时候，这也一定是第N轮left向后移动的结果，
  // 而且只有当nums[mid]<target的时候才执行的left=mid+1，
  // 这里的mid是第N轮的mid，也即left==right时的mid，所以可以肯定的是，
  // 第N轮mid指向的元素小于target，那么怎么确定当left>right时，
  // left指向的元素就一定大于target呢？

  // 需要思考，为什么第N轮left和right会重合呢？
  // 是不是当mid指向的元素大于target的时候，执行的right=mid-1才能让left和right重合呢？
  // 所以可以确定当left和right将要重合时，第N-1轮的left、mid和right一定是排成一排的。
  // 所以如果第N轮left和right重合时，left还要左移的话，就只能移动到第N-1轮mid指向的位置，
  // 所以也就能确定，当第N+1轮left>ritht时，有nums[right]<target<nums[left]了，
  // 故最后直接返回left即可。

  // 就是说无论开始时如何，最终left和right会分别定位在要插入元素的左右，
  // 分别是比要插入元素target小和大的元素，因此是right+1或left，而不是right，
  // 因为如果插入到right处，那么nums[right]会右移且nums[right]比target小，
  // 插入位置错误，如果插入到left处，nums[left]右移且nums[left]比target大，
  // 于是插入的位置正确。

  return left;  // right + 1也行
}

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else {
        return mid;
      }
    }

    return left;
  }
};

// 704方法二
int searchInsert(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize;

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid;
    }
  }

  return left;  // right也行
}

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size();

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid;
      } else {
        return mid;
      }
    }

    return right;
  }
};