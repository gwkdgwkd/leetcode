/*
 * @lc app=leetcode.cn id=39 lang=c
 *
 * [39] 组合总和
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
int **result;
int resultSize;
int *path;
int pathSize;
void backtracking(int *candidates, int candidatesSize, int target,
                  int startIndex, int **returnColumnSizes) {
  if (startIndex == candidatesSize) {
    return;
  }

  if (target == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = path[i];
    }
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
    return;
  }

  // 每次可以选择跳过不用第startIndex个数，即执行backtracking(target,startIndex+ 1)。
  backtracking(candidates, candidatesSize, target, startIndex + 1,
               returnColumnSizes);
  if (target - candidates[startIndex] >= 0) {
    path[pathSize++] = candidates[startIndex];
    // 也可以选择使用第startIndex个数，即执行backtracking(target - candidates[startIndex], startIndex)
    // 注意到每个数字可以被无限制重复选取，因此搜索的下标仍为startIndex。
    backtracking(candidates, candidatesSize, target - candidates[startIndex],
                 startIndex, returnColumnSizes);
    pathSize--;
  }

  // 按上面的方法，就可以保证[3,2,2],[2,3,2]只有一个结果？什么原理？

  return;
}
int **combinationSum(int *candidates, int candidatesSize, int target,
                     int *returnSize, int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 1001);
  path = (int *)malloc(sizeof(int) * 2000);
  resultSize = pathSize = 0;
  *returnColumnSizes = (int *)malloc(sizeof(int) * 1001);
  backtracking(candidates, candidatesSize, target, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}

int **result;
int resultSize;
int *path;
int pathSize;
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
void backtracking(int *candidates, int candidatesSize, int target,
                  int startIndex, int **returnColumnSizes) {
  if (target == 0) {
    result[resultSize] = (int *)malloc(sizeof(int) * pathSize);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = path[i];
    }
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
    return;
  }
  for (int i = startIndex; i < candidatesSize && candidates[i] <= target; ++i) {
    path[pathSize++] = candidates[i];
    // printf("%*d[%d %d]\n", pathSize * 2, candidates[i], i, target);
    // 元素为可重复选取的，不⽤i+1了，表示可以重复读取当前的数
    backtracking(candidates, candidatesSize, target - candidates[i], i,
                 returnColumnSizes);
    pathSize--;
  }

  return;
}
int **combinationSum(int *candidates, int candidatesSize, int target,
                     int *returnSize, int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 1001);
  path = (int *)malloc(sizeof(int) * 2000);
  resultSize = pathSize = 0;
  *returnColumnSizes = malloc(sizeof(int) * 1001);
  // 先对数组排序，保证[3,2,2],[2,3,2]只有一个结果。
  qsort(candidates, candidatesSize, sizeof(int), cmp);
  backtracking(candidates, candidatesSize, target, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}
// @lc code=end
