/*
符合下列属性的数组arr称为山脉数组：
arr.length >= 3
存在i（0 < i < arr.length - 1）使得：
arr[0] < arr[1] < ... arr[i-1] < arr[i]
arr[i] > arr[i+1] > ... > arr[arr.length - 1]
给由整数组成的山脉数组arr，返回任何满足：
arr[0]<arr[1]<...arr[i-1]<arr[i]>arr[i+1]>...>arr[arr.length-1]的下标i。

示例1：
输入：arr = [0,1,0]
输出：1

示例2：
输入：arr = [0,2,1,0]
输出：1

示例3：
输入：arr = [0,10,5,2]
输出：1

示例4：
输入：arr = [3,4,5,1]
输出：2

示例5：
输入：arr = [24,69,100,99,79,78,67,36,26,19]
输出：2


提示：
3 <= arr.length <= 10^4
0 <= arr[i] <= 10^6
题目数据保证arr是一个山脉数组

进阶：
很容易想到时间复杂度O(n)的解决方案，可以设计一个O(logn)的解决方案吗？
*/

// 剑指OfferII069山峰数组的顶部

int peakIndexInMountainArray(int* arr, int arrSize) {
  int left = 1;
  int right = arrSize - 2;
  int ans = 0;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] > arr[mid + 1]) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return ans;
}

// 与[162.寻找峰值]写法相同
int peakIndexInMountainArray(int* arr, int arrSize) {
  int left = 0;
  int right = arrSize - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] > arr[mid + 1]) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
      int mid = left + ((right - left) >> 1);
      if (arr[mid] > arr[mid + 1]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};