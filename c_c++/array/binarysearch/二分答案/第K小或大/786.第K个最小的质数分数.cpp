/*
给一个按递增顺序排序的数组arr和一个整数k。
数组arr由1和若干质数组成，且其中所有整数互不相同。
对于每对满足0 <= i < j < arr.length的i和j，可以得到分数arr[i] / arr[j]。
那么第k个最小的分数是多少呢？
以长度为2的整数数组返回你的答案，这里answer[0]==arr[i]且answer[1]==arr[j]。

示例1：
输入：arr = [1,2,3,5], k = 3
输出：[2,5]
解释：已构造好的分数,排序后如下所示:
     1/5, 1/3, 2/5, 1/2, 3/5, 2/3
     很明显第三个最小的分数是2/5

示例2：
输入：arr = [1,7], k = 1
输出：[1,7]


提示：
2 <= arr.length <= 1000
1 <= arr[i] <= 3 * 10^4
arr[0] == 1
arr[i]是一个质数，i > 0
arr中的所有数 互不相同，且按严格递增排序
1 <= k <= arr.length * (arr.length - 1) / 2

进阶：可以设计并实现时间复杂度小于 O(n2) 的算法解决此问题吗？
*/

class Solution {
 public:
  vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
    int n = arr.size();
    double left = 0.0, right = 1.0;
    while (true) {
      double mid = (left + right) / 2;
      int i = -1, count = 0;
      // 记录最大的分数
      int x = 0, y = 1;

      for (int j = 1; j < n; ++j) {
        while ((double)arr[i + 1] / arr[j] < mid) {
          ++i;
          if (arr[i] * y > arr[j] * x) {
            x = arr[i];
            y = arr[j];
          }
        }
        count += i + 1;
      }

      if (count == k) {
        return {x, y};
      }
      if (count < k) {
        left = mid;
      } else {
        right = mid;
      }
    }
  }
};