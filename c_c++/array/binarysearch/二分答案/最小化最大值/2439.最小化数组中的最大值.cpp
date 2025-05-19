/*
给一个下标从0开始的数组nums，它含有n个非负整数。
每一步操作中，需要：
选择一个满足1 <= i < n的整数i，且nums[i]>0。
将nums[i]减1。
将nums[i - 1]加1。
可以对数组执行任意次上述操作，请返回可以得到的nums数组中最大值最小为多少。

示例1：
输入：nums = [3,7,1,6]
输出：5
解释：一串最优操作是：
     1.选择i = 1，nums变为[4,6,1,6]。
     2.选择i = 3，nums变为[4,6,2,5]。
     3.选择i = 1，nums变为[5,5,2,5]。
     nums中最大值为5。无法得到比5更小的最大值。
     所以我们返回5。

示例2：
输入：nums = [10,1]
输出：10
解释：最优解是不改动nums，10是最大值，所以返回10。


提示：
n == nums.length
2 <= n <= 10^5
0 <= nums[i] <= 10^9
*/

class Solution {
 public:
  int minimizeArrayValue(vector<int>& nums) {
    int n = nums.size();
    auto check = [&](int m) {
      // 从后往前模拟：
      // 如果nums[i]>m，那么应当去掉多余的extra=nums[i]−m加到nums[i−1]上，
      // 最后如果 nums[0]≤limit，则二分判定成功。
      long long extra = 0;
      for (int i = n - 1; i >= 1; --i) {
        extra = max(nums[i] + extra - m, 0LL);  // 有点想不明白
      }
      return nums[0] + extra <= m;
    };

    int left = 0;
    int right = *max_element(nums.begin(), nums.end());
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

/* 分类讨论
从nums[0]开始讨论：
1.如果数组中只有nums[0]，那么最大值为nums[0]。
2.再考虑nums[1]，如果nums[1]≤nums[0]，最大值还是nums[0]；
  否则可以平均这两个数，平均后的最大值为平均值的上取整，即⌈2nums[0]+nums[1]​⌉。
3.再考虑nums[2]，如果nums[2]≤前面算出的最大值，
  或者这三个数的平均值不超过前面算出的最大值，那么最大值不变；
  否则可以平均这三个数，做法同上。
4.依此类推，直到最后一个数。
5.过程中的最大值为答案。

关于上取整的计算，有[a/b] = [(a+b-1)/b]，
讨论a被b整除，和不被b整除两种情况，可以证明上式的正确性。
所以平均值的计算公式为：[s/(i+1)]=[(s+i)/(i+1)]
*/
class Solution {
 public:
  int minimizeArrayValue(vector<int>& nums) {
    long long ans = 0, s = 0;
    for (int i = 0; i < nums.size(); i++) {
      s += nums[i];
      ans = max(ans, (s + i) / (i + 1));
    }

    return ans;
  }
};
