/*
数对(a,b)由整数a和b组成，其数对距离定义为a和b的绝对差值。
给一个整数数组nums和一个整数k，
数对由nums[i]和nums[j]组成且满足0 <= i < j < nums.length。
返回所有数对距离中第k小的数对距离。

示例1：
输入：nums = [1,3,1], k = 1
输出：0
解释：数对和对应的距离如下：
     (1,3) -> 2
     (1,1) -> 0
     (3,1) -> 2
     距离第1小的数对是(1,1)，距离为0。

示例2：
输入：nums = [1,1,1], k = 2
输出：0

示例3：
输入：nums = [1,6,1], k = 3
输出：5


提示：
n == nums.length
2 <= n <= 10^4
0 <= nums[i] <= 10^6
1 <= k <= n * (n - 1) / 2
*/

class Solution {
 public:
  int smallestDistancePair(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    auto check = [&](int d) {
      int cnt = 0;
      for (int l = 0, r = 0; r < n; ++r) {
        while (nums[r] - nums[l] > d) {
          ++l;
        }
        cnt += r - l;
      }
      return cnt >= k;
    };

    int left = 0;
    int right = nums[n - 1] - nums[0];
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};