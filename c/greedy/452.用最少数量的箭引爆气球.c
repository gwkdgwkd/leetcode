// 贪心算法
int cmp(const void *a, const void *b) {
  // [[-2147483646,-2147483645],[2147483646,2147483647]],signed integer overflow
  // return (*(int **)a)[0] - (*(int **)b)[0];
  return ((*((int **)a))[0] > (*((int **)b))[0]);
}
int findMinArrowShots(int **points, int pointsSize, int *pointsColSize) {
  if (pointsSize == 0) return 0;
  qsort(points, pointsSize, sizeof(int *), cmp);

  int res = 1;
  for (int i = 1; i < pointsSize; ++i) {
    if (points[i][0] > points[i - 1][1]) {
      ++res;
    } else {
      points[i][1] = fmin(points[i][1], points[i - 1][1]);
    }
  }

  return res;
}