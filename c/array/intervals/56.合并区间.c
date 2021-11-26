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