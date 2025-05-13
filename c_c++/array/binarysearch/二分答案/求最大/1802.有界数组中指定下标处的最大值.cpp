/*
给三个正整数n、index 和 maxSum。
需要构造一个同时满足下述所有条件的数组nums（下标从0开始计数）：
nums.length == n
nums[i]是正整数，其中 0 <= i < n
abs(nums[i] - nums[i+1]) <= 1 ，其中0 <= i < n-1
nums中所有元素之和不超过maxSum
nums[index]的值被最大化
返回所构造的数组中的nums[index]。
注意：abs(x)等于x的前提是x >= 0；否则，abs(x)等于-x。

示例1：
输入：n = 4, index = 2,  maxSum = 6
输出：2
解释：数组[1,1,2,1]和[1,2,2,1]满足所有条件。
     不存在其他在指定下标处具有更大值的有效数组。

示例2：
输入：n = 6, index = 1,  maxSum = 10
输出：3


提示：
1 <= n <= maxSum <= 10^9
0 <= index < n
*/

class Solution {
 public:
  int maxValue(int n, int index, int maxSum) {
    // check(mid)：判断当nums[index]=mid时，能否让数组总和≤maxSum
    auto check = [&](int mid) -> bool {
      long long sum = 0;

      // 1.中心点
      sum += mid;

      // 2.左侧部分：从mid-1递减到1，然后补1
      long l_len = index;   // 左侧元素个数
      long l_st = mid - 1;  // 左侧首项值
      if (l_len <= l_st) {
        // 完全用上递减序列l_st, l_st-1, …
        // 求和公式：l_len * (首项 + 末项) / 2
        sum += l_len * (l_st + (l_st - l_len + 1)) / 2;
      } else {
        // 只能递减到1，再剩余位置全部填1
        // 1 + 2 + … + l_st
        sum += l_st * (l_st + 1) / 2
               // 剩余(l_len - l_st)个位置，每个都填1
               + (l_len - l_st);
      }

      // 3. 右侧部分：同左侧逻辑
      long r_len = n - index - 1;  // 右侧元素个数
      long r_st = mid - 1;         // 右侧首项值
      if (r_len <= r_st) {
        sum += r_len * (r_st + (r_st - r_len + 1)) / 2;
      } else {
        sum += r_st * (r_st + 1) / 2 + (r_len - r_st);
      }

      // 4. 判断总和是否超限
      return sum <= maxSum;
    };

    int left = 1;
    int right = maxSum;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};

// 超时
class Solution {
 public:
  int maxValue(int n, int index, int maxSum) {
    auto check = [&](int m) {
      long long sum = m;
      for (int i = index - 1; i >= 0; --i) {
        if (index - i >= m) {
          sum++;
        } else {
          sum += m - (index - i);
        }
      }

      for (int i = index + 1; i < n; ++i) {
        if (i - index >= m) {
          sum++;
        } else {
          sum += m - (i - index);
        }
      }

      return sum <= maxSum;
    };

    int left = 1;
    int right = maxSum;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return right;
  }
};