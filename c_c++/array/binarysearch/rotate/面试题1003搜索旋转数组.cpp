/*
给定一个排序后的数组，包含n个整数，
但这个数组已被旋转过很多次了，次数不详。
请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。
若有多个相同元素，返回索引值最小的一个。

示例1:
输入: arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 5
输出: 8（元素5在该数组中的索引）

示例2:
输入：arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 11
输出：-1 （没有找到）

提示:arr长度范围在[1,1000000]之间
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