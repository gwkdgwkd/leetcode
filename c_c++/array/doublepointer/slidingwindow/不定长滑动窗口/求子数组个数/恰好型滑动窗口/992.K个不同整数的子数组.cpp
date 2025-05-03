/*
给定一个正整数数组nums和一个整数k，返回nums中好子数组的数目。
如果nums的某个子数组中不同整数的个数恰好为k，
则称nums的这个连续、不一定不同的子数组为好子数组。
例如，[1,2,3,1,2]中有3个不同的整数：1，2，以及3。
子数组是数组的连续部分。

示例1：
输入：nums = [1,2,1,2,3], k = 2
输出：7
解释：恰好由2个不同整数组成的子数组：
     [1,2],[2,1],[1,2],[2,3],[1,2,1],[2,1,2],[1,2,1,2].

示例2：
输入：nums = [1,2,1,3,4], k = 3
输出：3
解释：恰好由3个不同整数组成的子数组：[1,2,1,3],[2,1,3],[1,3,4].


提示：
1 <= nums.length <= 2 * 10^4
1 <= nums[i], k <= nums.length
*/

class Solution {
 public:
  int subarraysWithKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    int l1 = 0, l2 = 0;
    int r = 0;
    int ans = 0;
    unordered_map<int, int> cnt1;
    unordered_map<int, int> cnt2;
    while (r < n) {
      cnt1[nums[r]]++;
      while (cnt1.size() >= k) {
        if (--cnt1[nums[l1]] == 0) {
          cnt1.erase(nums[l1]);
        }
        ++l1;
      }
      cnt2[nums[r]]++;
      while (cnt2.size() >= k + 1) {
        if (--cnt2[nums[l2]] == 0) {
          cnt2.erase(nums[l2]);
        }
        ++l2;
      }
      ans += l1 - l2;
      ++r;
    }

    return ans;
  }
};

class Solution {
 public:
  int subarraysWithKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    int l1 = 0, l2 = 0;
    int r = 0;
    int ans = 0;
    unordered_map<int, int> cnt1;
    unordered_map<int, int> cnt2;
    while (r < n) {
      cnt1[nums[r]]++;
      while (cnt1.size() > k) {
        if (--cnt1[nums[l1]] == 0) {
          cnt1.erase(nums[l1]);
        }
        ++l1;
      }
      cnt2[nums[r]]++;
      while (cnt2.size() > k - 1) {
        if (--cnt2[nums[l2]] == 0) {
          cnt2.erase(nums[l2]);
        }
        ++l2;
      }
      ans += l2 - l1;
      ++r;
    }

    return ans;
  }
};