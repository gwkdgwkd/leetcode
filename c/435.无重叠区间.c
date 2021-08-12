/*
 * @lc app=leetcode.cn id=435 lang=c
 *
 * [435] 无重叠区间
 */

// @lc code=start

/*
// 动态规划，超时
int cmp(int** a, int** b) { return (*a)[0] - (*b)[0]; }
int eraseOverlapIntervals(int** intervals, int intervalsSize,
                          int* intervalsColSize) {
  if (intervalsSize == 0) {
    return 0;
  }

  qsort(intervals, intervalsSize, sizeof(int*), cmp);

  int dp[intervalsSize];
  for (int i = 0; i < intervalsSize; ++i) {
    dp[i] = 1;
  }
  int maxn = 1;
  for (int i = 1; i < intervalsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (intervals[j][1] <= intervals[i][0]) {
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      maxn = fmax(maxn, dp[i]);
    }
  }

  return intervalsSize - maxn;
}

// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
*/

// 贪心算法可以认为是动态规划算法的一个特例，相比动态规划，使用贪心算法需要满足更多的条件（贪心选择性质），但是效率比动态规划要高。
// 比如说一个算法问题使用暴力解法需要指数级时间，如果能使用动态规划消除重叠子问题，就可以降到多项式级别的时间，如果满足贪心选择性质，那么可以进一步降低时间复杂度，达到线性级别的。
// 什么是贪心选择性质呢，简单说就是：每一步都做出一个局部最优的选择，最终的结果就是全局最优。注意哦，这是一种特殊性质，其实只有一小部分问题拥有这个性质。

// 贪心算法
int cmp(int** a, int** b) { return (*a)[1] - (*b)[1]; }
int eraseOverlapIntervals(int** intervals, int intervalsSize,
                          int* intervalsColSize) {
  if (intervalsSize == 0) {
    return 0;
  }

  qsort(intervals, intervalsSize, sizeof(int*), cmp);

  int right = intervals[0][1];
  int ans = 1;
  for (int i = 1; i < intervalsSize; ++i) {
    if (intervals[i][0] >= right) {
      ++ans;
      right = intervals[i][1];
    }
  }
  return intervalsSize - ans;
}

// 时间复杂度：O(nlogn)
// 空间复杂度：O(logn)

// @lc code=end
