/*
以数组intervals表示若干个区间的集合，其中单个区间为intervals[i]=[starti,endi]。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

示例1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间[1,3]和[2,6]重叠,将它们合并为[1,6].

示例2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间[1,4]和[4,5]可被视为重叠区间。

提示：
1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
*/

// 时间复杂度：O(nlogn) ，有一个快排
// 空间复杂度：O(1)，不算result数组（返回值所需容器占的空间）
int cmp(const void *a, const void *b) {
  return (*(int **)a)[0] - (*(int **)b)[0];
  // return ((*(int **)a))[0] - ((*(int **)b))[0];
  // int* aa = *(int**)a;
  // int* bb = *(int**)b;
  // return aa[0] - bb[0];
}
int **merge(int **intervals, int intervalsSize, int *intervalsColSize,
            int *returnSize, int **returnColumnSizes) {
  int **res = (int **)malloc(sizeof(int *) * intervalsSize);
  *returnSize = 0;
  *returnColumnSizes = (int *)malloc(sizeof(int) * intervalsSize);

  qsort(intervals, intervalsSize, sizeof(int *), cmp);

  res[(*returnSize)++] = (int *)malloc(sizeof(int) * 2);
  res[0][0] = intervals[0][0];
  res[0][1] = intervals[0][1];
  (*returnColumnSizes)[0] = 2;
  for (int i = 1; i < intervalsSize; ++i) {
    // printf("%d: %d %d\n",i,intervals[i][0],intervals[i][1]);
    if (res[*returnSize - 1][1] >= intervals[i][0]) {
      res[*returnSize - 1][1] = fmax(res[*returnSize - 1][1], intervals[i][1]);
    } else {
      res[*returnSize] = (int *)malloc(sizeof(int) * 2);
      res[*returnSize][0] = intervals[i][0];
      res[*returnSize][1] = intervals[i][1];
      (*returnColumnSizes)[*returnSize] = 2;
      (*returnSize)++;
    }
  }

  return res;
}