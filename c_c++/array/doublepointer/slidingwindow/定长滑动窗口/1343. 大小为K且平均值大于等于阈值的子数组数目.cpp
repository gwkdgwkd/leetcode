/*
给一个整数数组arr和两个整数k和threshold。
请返回长度为k且平均值大于等于threshold的子数组数目。

示例1：
输入：arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
输出：3
解释：子数组[2,5,5],[5,5,5]和[5,5,8]的平均值分别为4，5和6。
     其他长度为3的子数组的平均值都小于4（threshold的值)。

示例2：
输入：arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
输出：6
解释：前6个长度为3的子数组平均值都大于5。注意平均值不是整数。


提示：
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^4
1 <= k <= arr.length
0 <= threshold <= 10^4
*/

class Solution {
  // 时间复杂度：O(n)，其中n是arr的长度。
  // 空间复杂度：O(1)，仅用到若干额外变量。

 public:
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    int ans = 0;
    int sum = 0;
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];
      if (i < k - 1) {
        continue;
      }
      if (sum / k >= threshold) {
        ++ans;
      }
      sum -= arr[i - k + 1];
    }
    return ans;
  }
};