/*
给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。
只有当c <= a且b <= d时，我们才认为区间[a,b)被区间[c,d)覆盖。
在完成所有删除操作后，请你返回列表中剩余区间的数目。

示例：
输入：intervals = [[1,4],[3,6],[2,8]]
输出：2
解释：区间[3,6]被区间[2,8]覆盖，所以它被删除了。

提示：​​​​​​
1 <= intervals.length <= 1000
0 <= intervals[i][0] < intervals[i][1] <= 10^5
对于所有的i != j：intervals[i] != intervals[j]
*/

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