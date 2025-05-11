#include <stdio.h>
#include <stdlib.h>

#include <vector>

/*
给定一个按照升序排列的整数数组nums，和一个目标值target。
找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值target，返回[-1,-1]。

进阶：可以设计并实现时间复杂度为O(logn)的算法解决此问题吗？

示例1：
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]

示例2：
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]

示例3：
输入：nums = [], target = 0
输出：[-1,-1]

提示：
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
nums是一个非递减数组
-10^9 <= target <= 10^9
*/

#if 0
// 704方法二
int left_bound(int* nums, int numsSize, int target) {
  if (numsSize == 0) return -1;

  int left = 0;
  int right = numsSize;

  // 当left==right时，[left,right)是无效空间，所以使用<
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      // 找到target时不要立即返回，而是缩小「搜索区间」的上界right，
      // 在区间[left, mid)中继续搜索，即不断向左收缩，达到锁定左侧边界的目的。
      right = mid;
    } else if (nums[mid] < target) {  // target在右区间，在[middle+1,right)中
      left = mid + 1;
    } else if (nums[mid] > target) {  // target在左区间，在[left,middle)中
      right = mid;
    }
  }

  // target比所有数都大
  if (left == numsSize) return -1;
  // 类似之前算法的处理方式
  return nums[left] == target ? left : -1;
  // 返回right也行，因为while终止的条件是left==right。
  // return nums[right] == target ? right : -1;
}
int right_bound(int* nums, int numsSize, int target) {
  if (numsSize == 0) return -1;

  int left = 0;
  int right = numsSize;

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      // 当nums[mid] == target时，不要立即返回，而是增大「搜索区间」的下界left，
      // 使得区间不断向右收缩，达到锁定右侧边界的目的。
      left = mid + 1;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid;
    }
  }

  if (left == 0) return -1;
  return nums[left - 1] == target ? (left - 1) : -1;
  // return nums[right - 1] == target ? (right - 1) : -1;  // 也行
}
#else
// 和704第一种二分搜索算法统一了，都是两端都闭的搜索区间，
// 而且最后返回的也是left变量的值：
int left_bound(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      right = mid - 1;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }

  // 检查出界情况
  if (left >= numsSize || nums[left] != target) {
    return -1;
  }
  return left;
}
int right_bound(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      left = mid + 1;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }

  // 检查出界情况
  if (right < 0 || nums[right] != target) {
    return -1;
  }
  return right;
}
#endif

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  if (numsSize == 0) {
    result[0] = result[1] = -1;
  } else {
    result[0] = left_bound(nums, numsSize, target);
    result[1] = result[0] == -1 ? -1 : right_bound(nums, numsSize, target);
  }

  return result;
}

using namespace std;
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int size = nums.size();
    if (size == 0) {
      return {-1, -1};
    }

    int begin = [&nums, &target, &size]() {
      int left = 0;
      int right = size - 1;
      while (left <= right) {
        int mid = left + (right - left) / 2;
        // if (nums[mid] < target) {
        //   left = mid + 1;
        // } else if (nums[mid] > target) {
        //   right = mid - 1;
        // } else {
        //   right = mid - 1;
        // }
        if (nums[mid] < target) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }

      // return (left >= size || nums[left] != target) ? -1 : left;
      return (left < size && nums[left] == target) ? left : -1;
    }();

    if (begin == -1) {
      return {-1, -1};
    }

    int end = [&nums, &target, &size]() {
      int left = 0;
      int right = size - 1;
      while (left <= right) {
        int mid = left + (right - left) / 2;
        // if (nums[mid] < target) {
        //   left = mid + 1;
        // } else if (nums[mid] > target) {
        //   right = mid - 1;
        // } else {
        //   left = mid + 1;
        // }
        if (nums[mid] > target) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      }

      // return (right < 0 || nums[right] != target) ? -1 : right;
      return (right >= 0 && nums[right] == target) ? right : -1;
    }();

    return {begin, end};
  }
};

// 剑指Offer53-I在排序数组中查找数字I
// 返回找到的元素个数
int search(int* nums, int numsSize, int target) {
  int left = left_bound(nums, numsSize, target);
  int right = right_bound(nums, numsSize, target);
  if (left >= 0 && right >= 0) {
    return right - left + 1;
  } else {
    return 0;
  }
}

int main() {
  int left, right;
  int nums[] = {1, 2, 2, 2, 2, 2, 3};
  left = left_bound(nums, sizeof(nums) / sizeof(int), 2);
  right = right_bound(nums, sizeof(nums) / sizeof(int), 2);

  printf("[%d, %d]:", left, right);
  for (int i = left; i <= right; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");
  // [1, 5]:2 2 2 2 2

  left = left_bound(nums, sizeof(nums) / sizeof(int), 3);
  right = right_bound(nums, sizeof(nums) / sizeof(int), 3);
  printf("[%d, %d]:", left, right);
  for (int i = left; i <= right; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");
  // [6, 6]:3

  return 0;
}

// 闭区间写法
class Solution {
  // lower_bound返回最小的满足nums[i] >= target的下标i，
  // 如果数组为空，或者所有数都<target，则返回nums.size()，
  // 要求nums是非递减的，即nums[i] <= nums[i + 1]
  int lower_bound(vector<int>& nums, int target) {
    // 闭区间[left, right]
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {  // 区间不为空
      // 循环不变量：
      // nums[left-1] < target
      // nums[right+1] >= target
      int mid = left + (right - left) / 2;  // 防止溢出
      if (nums[mid] >= target) {
        right = mid - 1;  // 范围缩小到[left, mid-1]
      } else {
        left = mid + 1;  // 范围缩小到[mid+1, right]
      }
    }

    // 循环结束后left = right+1，
    // 此时nums[left-1] < target而nums[left] = nums[right+1] >= target，
    // 所以left就是第一个>=target的元素下标：
    return left;  // right + 1
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};
    }

    // 如何理解end = lower_bound(nums, target + 1) - 1这段代码？
    // 要想找到≤target的最后一个数，无需单独再写一个二分。
    // 可以先找到这个数的右边相邻数字，也就是>target的第一个数。
    // 在所有数都是整数的前提下，>target等价于≥target+1，
    // 这样就可以复用已经写好的二分函数了，即lowerBound(nums, target + 1)，
    // 算出这个数的下标后，将其减一，就得到≤target的最后一个数的下标。
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

// 左闭右开区间写法
class Solution {
  int lower_bound(vector<int>& nums, int target) {
    // 左闭右开区间[left, right)
    int left = 0;
    int right = nums.size();
    while (left < right) {  // 区间不为空
      // 循环不变量：
      // nums[left-1] < target
      // nums[right] >= target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;  // 范围缩小到[left, mid)
      } else {
        left = mid + 1;  // 范围缩小到[mid+1, right)
      }
    }

    // 循环结束后left = right，
    // 此时nums[left-1] < target而nums[left] = nums[right] >= target，
    // 所以left就是第一个>= target的元素下标：
    return left;  // right
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};
    }

    // 如果≥target+1的第一个数不存在怎么办？
    // 在数组中有target的前提下，这意味着数组的最后一个数（下标n−1）就是target。
    // 同时，lowerBound(nums, target + 1)在这种情况下会返回n，
    // 减一得到n−1，这正是要计算的下标。
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

// 开区间写法
class Solution {
  int lower_bound(vector<int>& nums, int target) {
    // 开区间(left, right)
    int left = -1;
    int right = nums.size();
    while (left + 1 < right) {  // 区间不为空
      // 循环不变量：
      // nums[left] < target
      // nums[right] >= target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;  // 范围缩小到(left, mid)
      } else {
        left = mid;  // 范围缩小到 (mid, right)
      }
    }

    // 循环结束后left+1 = right，
    // 此时nums[left] < target而nums[right] >= target，
    // 所以right就是第一个>= target的元素下标：
    return right;  // left + 1
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};
    }
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

// 怎么判断写的是哪一种二分？
// 看while循环的条件，如果是left <= right，就是闭区间；
// 如果是left < right，就是半闭半开区间；
// 如果是left + 1 < right，就是开区间。
