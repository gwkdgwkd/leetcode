/*
给一个严格升序排列的正整数数组arr和一个整数k。
请找到这个数组里第k个缺失的正整数。

示例1：
输入：arr = [2,3,4,7,11], k = 5
输出：9
解释：缺失的正整数包括[1,5,6,8,9,10,12,13,...]。第5个缺失的正整数为9。

示例2：
输入：arr = [1,2,3,4], k = 2
输出：6
解释：缺失的正整数包括[5,6,7,...]。第2个缺失的正整数为6。


提示：
1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
对于所有1 <= i < j <= arr.length的i和j满足arr[i] < arr[j]

进阶：
可以设计一个时间复杂度小于O(n)的算法解决此问题吗？
*/

class Solution {
 public:
  int findKthPositive(vector<int>& arr, int k) {
    int missCount = 0, lastMiss = -1, current = 1, ptr = 0;
    for (missCount = 0; missCount < k; ++current) {
      if (current == arr[ptr]) {
        ptr = (ptr + 1 < arr.size()) ? ptr + 1 : ptr;
      } else {
        ++missCount;
        lastMiss = current;
      }
    }
    return lastMiss;
  }
};

class Solution {
 public:
  int findKthPositive(vector<int>& arr, int k) {
    if (arr[0] > k) {
      return k;
    }

    int l = 0, r = arr.size();
    while (l < r) {
      int mid = (l + r) >> 1;
      int x = mid < arr.size() ? arr[mid] : INT_MAX;
      if (x - mid - 1 >= k) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }

    return k - (arr[l - 1] - (l - 1) - 1) + arr[l - 1];
  }
};