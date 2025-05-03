/*
给定一个排序好的数组arr，两个整数k和x，从数组中找到最靠近x（差最小）的k个数。
返回的结果必须要是按升序排好的。
整数a比整数b更接近x需要满足：
|a - x| < |b - x|或者|a - x| == |b - x|且a < b

示例1：
输入：arr = [1,2,3,4,5], k = 4, x = 3
输出：[1,2,3,4]

示例2：
输入：arr = [1,1,2,3,4,5], k = 4, x = -1
输出：[1,1,2,3]


提示：
1 <= k <= arr.length
1 <= arr.length <= 10^4
arr按升序排列
-10^4 <= arr[i], x <= 10^4
*/

class Solution {
 public:
  vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int left = 0;
    int right = arr.size() - 1;
    while (right - left + 1 > k) {
      if (abs(arr[left] - x) > abs(arr[right] - x)) {
        ++left;
      } else {
        --right;
      }
    }
    return vector(arr.begin() + left, arr.begin() + right + 1);
  }
};