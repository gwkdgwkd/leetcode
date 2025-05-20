/*
给一个整数数组nums。
数组nums的唯一性数组是一个按元素从小到大排序的数组，包含了nums的所有非空中不同元素的个数。
换句话说，这是由所有0<=i<=j<nums.length的distinct(nums[i..j])组成的递增数组。
其中，distinct(nums[i..j])表示从下标i到下标j的子数组中不同元素的数量。
返回nums唯一性数组的中位数。
注意，数组的中位数定义为有序数组的中间元素。如果有两个中间元素，则取值较小的那个。

示例1：
输入：nums = [1,2,3]
输出：1
解释：nums的唯一性数组为[distinct(nums[0..0]), distinct(nums[1..1]),
     distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]),
     distinct(nums[0..2])]，即[1, 1, 1, 2, 2, 3]。
     唯一性数组的中位数为1，因此答案是1。

示例2：
输入：nums = [3,4,3,4,5]
输出：2
解释：nums的唯一性数组为[1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3]。
     唯一性数组的中位数为2，因此答案是2。

示例 3：
输入：nums = [4,3,5,4]
输出：2
解释：nums的唯一性数组为 [1, 1, 1, 1, 2, 2, 2, 3, 3, 3]。
     唯一性数组的中位数为2，因此答案是2。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
*/

class Solution {
 public:
  int medianOfUniquenessArray(vector<int>& nums) {
    int n = nums.size();
    long long k = ((long long)n * (n + 1) / 2 + 1) / 2;

    auto check = [&](int upper) {
      long long cnt = 0;
      int l = 0;
      unordered_map<int, int> freq;
      for (int r = 0; r < n; r++) {
        freq[nums[r]]++;               // 移入右端点
        while (freq.size() > upper) {  // 窗口内元素过多
          int out = nums[l++];
          if (--freq[out] == 0) {  // 移出左端点
            freq.erase(out);
          }
        }
        cnt += r - l + 1;  // 右端点固定为r时，有r-l+1个合法左端点
        if (cnt >= k) {
          return true;
        }
      }
      return false;
    };

    int left = 0, right = n;
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};
