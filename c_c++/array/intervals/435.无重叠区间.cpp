/*
给定一个区间的集合intervals，其中intervals[i] = [starti, endi]。
返回需要移除区间的最小数量，使剩余区间互不重叠。

示例1：
输入：intervals = [[1,2],[2,3],[3,4],[1,3]]
输出：1
解释：移除[1,3]后，剩下的区间没有重叠。

示例2：
输入：intervals = [[1,2], [1,2], [1,2]]
输出：2
解释：你需要移除两个[1,2]来使剩下的区间没有重叠。

示例3：
输入：intervals = [[1,2], [2,3]]
输出：0
解释：你不需要移除任何区间，因为它们已经是无重叠的了。

提示：
1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 10^4 <= starti < endi <= 5 * 10^4
*/

// 贪心算法可以认为是动态规划算法的一个特例，相比动态规划，
// 使用贪心算法需要满足更多的条件（贪心选择性质），但是效率比动态规划要高。
// 比如说一个算法问题使用暴力解法需要指数级时间，如果能使用动态规划消除重叠子问题，
// 就可以降到多项式级别的时间，如果满足贪心选择性质，
// 那么可以进一步降低时间复杂度，达到线性级别的。
// 什么是贪心选择性质呢，简单说就是：
// 每一步都做出一个局部最优的选择，最终的结果就是全局最优。
// 注意哦，这是一种特殊性质，其实只有一小部分问题拥有这个性质。

// 区间问题肯定按照区间的起点或者终点进行排序

// 贪心算法
// 时间复杂度：O(nlogn)，有一个快排
// 空间复杂度：O(1)
int cmp(const void* a, const void* b) {
  return ((*(int**)a))[1] - ((*(int**)b))[1];
}
// int cmp(int** a, int** b) { return (*a)[1] - (*b)[1]; }
int eraseOverlapIntervals(int** intervals, int intervalsSize,
                          int* intervalsColSize) {
  if (intervalsSize == 0) return 0;
  qsort(intervals, intervalsSize, sizeof(int*), cmp);

  // 1.按照右边界排序，就要从左向右遍历，因为右边界越小越好，只要右边界越小，
  //   留给下一个区间的空间就越大，所以从左向右遍历，优先选右边界小的。
  // 2.按照左边界排序，就要从右向左遍历，因为左边界数值越大越好（越靠右），
  //   这样就给前一个区间的空间就越大，所以可以从右向左遍历。
  // 3.如果按照左边界排序，还从左向右遍历的话，要处理各个区间右边界的各种情况。

  int count = 1;              // 记录非交叉区间的个数
  int end = intervals[0][1];  // 记录区间分割点
  for (int i = 1; i < intervalsSize; ++i) {
    // [1,2]和[2,3]不算重叠，所以使用<=：
    if (end <= intervals[i][0]) {
      end = intervals[i][1];
      ++count;
    }
  }

  // 如果是求今天最多能参加几个活动，那么直接返回count，比如452
  return intervalsSize - count;
}

class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a[1] < b[1]; });

    int count = 1;
    int right = intervals[0][1];
    int n = intervals.size();
    for (int i = 1; i < n; ++i) {
      if (intervals[i][0] >= right) {
        ++count;
        right = intervals[i][1];
      }
    }

    return n - count;
  }
};

// 动态规划，超时
// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
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
