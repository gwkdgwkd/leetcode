int cmp(const void *a, const void *b) {
  // 区间问题常见的排序方法就是先按照起点升序排序，若起点相同，则按照终点降序排序。
  int va = (*((int **)a))[0];
  int vb = (*((int **)b))[0];

  if (va == vb) {
    return (*((int **)b))[1] - (*((int **)a))[1];
  }
  return va - vb;
}
int removeCoveredIntervals(int **intervals, int intervalsSize,
                           int *intervalsColSize) {
  if (intervalsSize < 2) {
    return intervalsSize;
  }

  qsort(intervals, intervalsSize, sizeof(int *), cmp);

  int preindex = 0;
  int count = 1;
  for (int i = 1; i < intervalsSize; ++i) {
    if (intervals[i][1] <= intervals[preindex][1]) {
      continue;
    }
    count++;
    preindex = i;
  }

  return count;
}