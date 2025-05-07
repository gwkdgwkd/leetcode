/*
把符合下列属性的数组arr称为山脉数组：
arr.length >= 3，存在下标i（0 < i < arr.length - 1），满足：
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
给出一个整数数组arr，返回最长山脉子数组的长度。如果不存在山脉子数组，返回0。

示例1：
输入：arr = [2,1,4,7,3,2,5]
输出：5
解释：最长的山脉子数组是[1,4,7,3,2]，长度为5。

示例2：
输入：arr = [2,2,2]
输出：0
解释：不存在山脉子数组。


提示：
1 <= arr.length <= 10^4
0 <= arr[i] <= 10^4

进阶：
可以仅用一趟扫描解决此问题吗？
可以用O(1)空间解决此问题吗？
*/

// 分组循环
class Solution {
  // 时间复杂度：O(n)，其中n是数组arr的长度。
  // 空间复杂度：O(1)。
 public:
  int longestMountain(vector<int>& arr) {
    int n = arr.size();
    int right = 1;
    int ans = 0;
    while (right < n) {
      while (right < n && arr[right - 1] >= arr[right]) {
        ++right;
      }
      int left = right - 1;
      while (right < n && arr[right - 1] < arr[right]) {
        ++right;
      }
      int top = right - 1;
      while (right < n && arr[right - 1] > arr[right]) {
        ++right;
      }
      if (right - left >= 3 && right - 1 > top) {
        ans = max(ans, right - left);
      }
    }

    return ans;
  }
};

// 枚举山脚
class Solution {
  // 时间复杂度：O(n)，其中n是数组arr的长度。
  // 空间复杂度：O(1)。
 public:
  int longestMountain(vector<int>& arr) {
    int n = arr.size();
    int ans = 0;
    int left = 0;
    while (left + 2 < n) {
      int right = left + 1;
      if (arr[left] < arr[left + 1]) {
        while (right + 1 < n && arr[right] < arr[right + 1]) {
          ++right;
        }
        if (right < n - 1 && arr[right] > arr[right + 1]) {
          while (right + 1 < n && arr[right] > arr[right + 1]) {
            ++right;
          }
          ans = max(ans, right - left + 1);
        } else {
          ++right;
        }
      }
      left = right;
    }
    return ans;
  }
};
