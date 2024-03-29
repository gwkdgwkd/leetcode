/*
给定一个排序后的数组，包含n个整数，
但这个数组已被旋转过很多次了，次数不详。
请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。
若有多个相同元素，返回索引值最小的一个。

示例1：
输入：arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 5
输出：8（元素5在该数组中的索引）

示例2：
输入：arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 11
输出：-1 （没有找到）

提示：arr长度范围在[1,1000000]之间
*/

int binary_search(int* arr, int left, int right, int target) {
  if (left > right) {
    return -1;
  }

  int mid = left + ((right - left) >> 1);

  // 查找左边部分
  int left_ans = binary_search(arr, left, mid - 1, target);

  // 左边部分找到目标值时，直接返回
  if (left_ans != -1) {
    return left_ans;
  }

  // 当前mid是目标值时，直接返回
  if (arr[mid] == target) {
    return mid;
  }

  // 查找右边部分
  return binary_search(arr, mid + 1, right, target);
}

int search(int* arr, int arrSize, int target) {
  return binary_search(arr, 0, arrSize - 1, target);
}

class Solution {
 public:
  int binary_search(vector<int>& arr, int left, int right, int target) {
    if (left > right) {
      return -1;
    }

    int mid = left + ((right - left) >> 1);

    int left_ans = binary_search(arr, left, mid - 1, target);

    if (left_ans != -1) {
      return left_ans;
    }

    if (arr[mid] == target) {
      return mid;
    }

    return binary_search(arr, mid + 1, right, target);
  }
  int search(vector<int>& arr, int target) {
    return binary_search(arr, 0, arr.size() - 1, target);
  }
};

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {  // 循环结束条件left==right
      int mid = left + (right - left) / 2;
      if (nums[left] < nums[mid]) {
        // 如果左值小于中值，说明左边区间升序
        if (nums[left] <= target && target <= nums[mid]) {
          // 如果目标在左边的升序区间中，右边界移动到mid
          right = mid;
        } else {
          // 否则目标在右半边，左边界移动到mid+1
          left = mid + 1;
        }
      } else if (nums[left] > nums[mid]) {
        // 如果左值大于中值，说明左边不是升序，右半边升序
        if (nums[left] <= target || target <= nums[mid]) {
          // 如果目标在左边，右边界移动到mid
          right = mid;
        } else {
          // 否则目标在右半边，左边界移动到mid+1
          left = mid + 1;
        }
      } else if (nums[left] == nums[mid]) {
        // 如果左值等于中值，可能是已经找到了目标，也可能是遇到了重复值
        if (nums[left] != target) {
          // 如果左值不等于目标，说明还没找到，需要逐一清理重复值
          left++;
        } else {
          // 如果左值等于目标，说明已经找到最左边的目标值
          right = left;  // 将右边界移动到left，循环结束
        }
      }
    }

    return (nums[left] == target) ? left : -1;  // 返回left，或者-1
  }
};

class Solution {
 public:
  int search(vector<int>& arr, int target) {
    if (arr[0] == target) {
      return 0;
    }

    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;

      if (arr[mid] == target) {
        while (mid > 0 && arr[mid - 1] == arr[mid]) {
          --mid;
        }
        return mid;
      }

      if (arr[mid] < arr[right]) {
        if (arr[mid] < target && target <= arr[right]) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      } else if (arr[mid] > arr[right]) {
        if (arr[left] <= target && target < arr[mid]) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } else {
        --right;
      }
    }

    return -1;
  }
};