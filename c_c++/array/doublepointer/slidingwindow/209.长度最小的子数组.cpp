/*
给定一个含有n个正整数的数组和一个正整数target。
找出该数组中满足其和≥target的长度最小的连续子数组[numsl,numsl+1,...,numsr-1,numsr]，并返回其长度。
如果不存在符合条件的子数组，返回0。

示例1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组[4,3]是该条件下的长度最小的子数组。

示例2：
输入：target = 4, nums = [1,4,4]
输出：1

示例3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0

提示：
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5

进阶：如果你已经实现O(n)时间复杂度的解法，请尝试设计一个O(nlog(n))时间复杂度的解法。
*/

// 剑指OfferII008和大于等于target的最短子数组

// 暴力法，时间复杂度：O(n^2)
int minSubArrayLen(int target, int* nums, int numsSize) {
  int ret = INT_MAX;
  for (int i = 0; i < numsSize; ++i) {
    int sum = 0;
    for (int j = i; j < numsSize; ++j) {
      sum += nums[j];
      if (sum >= target) {
        ret = fmin(ret, j - i + 1);
        break;
      }
    }
  }

  return ret == INT_MAX ? 0 : ret;
}

// 滑动窗口也可以理解为双指针法的一种！
// 只不过这种解法更像是一个窗口的移动，所以叫做滑动窗口更适合一些。
// 滑动窗口的精妙之处在于根据当前子序列和大小的情况，不断调节子序列的起始位置。
// 从而将O(n^2)的暴力解法降为O(n)。
int minSubArrayLen(int target, int* nums, int numsSize) {
  int result = INT_MAX;
  int sum = 0;        // 滑动窗口数值之和
  int i = 0;          // 滑动窗口起始位置
  int subLength = 0;  // 滑动窗口的长度

  // 不要以为for里放一个while就以为是O(n^2)啊，
  // 主要是看每一个元素被操作的次数，每个元素在滑动窗后进来操作一次，
  // 出去操作一次，每个元素都是被被操作两次，所以时间复杂度是2*n也就是O(n)。
  for (int j = 0; j < numsSize; j++) {
    sum += nums[j];
    // 注意这里使用while，每次更新i(起始位置)，并不断比较子序列是否符合条件
    while (sum >= target) {
      subLength = (j - i + 1);  // 取子序列的长度
      result = result < subLength ? result : subLength;
      // 这里体现出滑动窗口的精髓之处，不断变更i(子序列的起始位置)
      sum -= nums[i++];
    }
  }
  // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
  return result == INT_MAX ? 0 : result;
}

// 滑动窗口
int minSubArrayLen(int target, int* nums, int numsSize) {
  int left = 0;
  int right = 0;
  int len = INT_MAX;
  int sum = 0;

  while (right < numsSize) {
    sum += nums[right++];
    while (sum >= target) {
      len = fmin(len, right - left);
      sum -= nums[left++];
    }
  }

  return len == INT_MAX ? 0 : len;
}

// 前缀和 + 二分查找
// 时间复杂度：O(nlog⁡n)
// 空间复杂度：O(n)
class Solution {
 public:
  int minSubArrayLen(int s, vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
      return 0;
    }
    int ans = INT_MAX;
    vector<int> sums(n + 1, 0);
    for (int i = 0; i < n; i++) {
      sums[i + 1] = sums[i] + nums[i];
    }
    for (int i = 1; i <= n; i++) {
      int target = s + sums[i - 1];
      auto bound = lower_bound(sums.begin(), sums.end(), target);
      if (bound != sums.end()) {
        ans = min(ans, static_cast<int>((bound - sums.begin()) - (i - 1)));
      }
    }
    return ans == INT_MAX ? 0 : ans;
  }
};

// 滑动窗口
class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0;
    int right = 0;
    int res = INT_MAX;
    int sum = 0;

    while (right < nums.size()) {
      sum += nums[right++];
      while (sum >= target) {
        res = min(res, right - left);
        sum -= nums[left++];
      }
    }
    return res == INT_MAX ? 0 : res;
  }
};
