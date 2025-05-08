/*
给一个长度为n的整数数组nums和一个正整数k。
一个数组的能量值定义为：
如果所有元素都是依次连续（即nums[i] + 1 = nums[i + 1]，i < n）且上升的，
那么能量值为最大的元素，否则为-1。
需要求出nums中所有长度为k能量值。
请返回一个长度为n - k + 1的整数数组results，
其中results[i]是子数组nums[i..(i + k - 1)]的能量值。

示例1：
输入：nums = [1,2,3,4,3,2,5], k = 3
输出：[3,4,-1,-1,-1]
解释：nums中总共有5个长度为3的子数组：
     [1, 2, 3]中最大元素为3。
     [2, 3, 4]中最大元素为4。
     [3, 4, 3]中元素不是连续的。
     [4, 3, 2]中元素不是上升的。
     [3, 2, 5]中元素不是连续的。

示例2：
输入：nums = [2,2,2,2,2], k = 4
输出：[-1,-1]

示例3：
输入：nums = [3,2,3,2,3,2], k = 2
输出：[-1,3,-1,3,-1]


提示：
1 <= n == nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= k <= n
*/

class Solution {
 public:
  vector<int> resultsArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n - k + 1, -1);
    for (int i = 0; i < n - k + 1; ++i) {
      int j = i + 1;
      while (j < i + k) {
        if (nums[j] - nums[j - 1] != 1) {
          break;
        }
        ++j;
      }
      if (j - i == k) {
        ans[i] = nums[j - 1];
      }
    }
    return ans;
  }
};

class Solution {
 public:
  vector<int> resultsArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n - k + 1, -1);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (i > 0 && nums[i] - nums[i - 1] == 1) {
        ++cnt;
      } else {
        cnt = 1;
      }
      if (cnt >= k) {
        ans[i - k + 1] = nums[i];
      }
    }
    return ans;
  }
};
