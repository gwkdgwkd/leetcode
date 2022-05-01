/*
给你一个无重复元素的整数数组candidates和一个目标整数target，
找出candidates中可以使数字和为目标数target的所有不同组合，并以列表形式返回。
你可以按任意顺序返回这些组合。
candidates中的同一个数字可以无限制重复被选取。
如果至少一个数字的被选数量不同，则两种组合是不同的。
对于给定的输入，保证和为target的不同组合数少于150个。

示例1：
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2和3可以形成一组候选，2 + 2 + 3 = 7。注意2可以使用多次。
7也是一个候选，7 = 7，仅有这两种组合。

示例2：
输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]

示例3：
输入: candidates = [2], target = 1
输出: []

提示：
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
candidate中的每个元素都互不相同
1 <= target <= 500
*/

// 剑指OfferII081允许重复选择元素的组合

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

  // 每次可以选择跳过不用第startIndex个数，即执行backtracking(target,startIndex+1)。
  backtracking(candidates, candidatesSize, target, startIndex + 1,
               returnColumnSizes);
  if (target - candidates[startIndex] >= 0) {
    path[pathSize++] = candidates[startIndex];
    // 也可以选择使用第startIndex个数，
    // 即执行backtracking(target-candidates[startIndex],startIndex)
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
  result = (int **)malloc(sizeof(int *) * 150);
  path = (int *)malloc(sizeof(int) * 30);
  resultSize = pathSize = 0;
  *returnColumnSizes = (int *)malloc(sizeof(int) * 150);
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
  result = (int **)malloc(sizeof(int *) * 150);
  path = (int *)malloc(sizeof(int) * 30);
  resultSize = pathSize = 0;
  *returnColumnSizes = malloc(sizeof(int) * 150);
  // 先对数组排序，保证[3,2,2],[2,3,2]只有一个结果。
  qsort(candidates, candidatesSize, sizeof(int), cmp);
  backtracking(candidates, candidatesSize, target, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}