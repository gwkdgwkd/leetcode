/*
给一个整数数组nums，请返回其中包含偶数个数位的数字的个数。

示例1：
输入：nums = [12,345,2,6,7896]
输出：2
解释：12是2位数字（位数为偶数）
     345是3位数字（位数为奇数）
     2是1位数字（位数为奇数）
     6是1位数字（位数为奇数）
     7896是4位数字（位数为偶数）
     因此只有12和7896是位数为偶数的数字

示例2：
输入：nums = [555,901,482,1771]
输出：1
解释：只有1771是位数为偶数的数字。


提示：
1 <= nums.length <= 500
1 <= nums[i] <= 10^5
*/

class Solution {
 public:
  int findNumbers(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int cnt = 0;
      while (nums[i]) {
        nums[i] = nums[i] / 10;
        ++cnt;
      }
      if (cnt > 0 && cnt % 2 == 0) {
        ++ans;
      }
    }
    return ans;
  }
};

class Solution {
  // 时间复杂度：O(nlogU)，其中n是nums的长度，U=max(nums)。
  // 空间复杂度：O(1)。
 public:
  int findNumbers(vector<int>& nums) {
    int ans = 0;
    for (int x : nums) {
      while (x >= 100) {
        x /= 100;
      }
      ans += x >= 10;
    }
    return ans;
  }
};
