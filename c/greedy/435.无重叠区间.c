// 区间问题肯定按照区间的起点或者终点进行排序

// 贪心算法
// 时间复杂度：O(nlogn)，有一个快排
// 空间复杂度：O(1)
int cmp(const void* a, const void* b) {
  return ((*(int**)a))[1] - ((*(int**)b))[1];
}
int eraseOverlapIntervals(int** intervals, int intervalsSize,
                          int* intervalsColSize) {
  if (intervalsSize == 0) return 0;
  qsort(intervals, intervalsSize, sizeof(int*), cmp);

  // 按照右边界排序，就要从左向右遍历，因为右边界越小越好，只要右边界越小，留给下一个区间的空间就越大，所以从左向右遍历，优先选右边界小的。
  // 按照左边界排序，就要从右向左遍历，因为左边界数值越大越好（越靠右），这样就给前一个区间的空间就越大，所以可以从右向左遍历。
  // 如果按照左边界排序，还从左向右遍历的话，要处理各个区间右边界的各种情况。

  int count = 1;              // 记录非交叉区间的个数
  int end = intervals[0][1];  // 记录区间分割点
  for (int i = 1; i < intervalsSize; ++i) {
    if (end <= intervals[i][0]) {
      end = intervals[i][1];
      ++count;
    }
  }

  // 如果是求今天最多能参加几个活动，那么直接返回count

  return intervalsSize - count;
}