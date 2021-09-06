/*
 * @lc app=leetcode.cn id=90 lang=c
 *
 * [90] 子集 II
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
int** result;
int resultSize;
int* path;
int pathSize;
int cmp(int* a, int* b) { return *a - *b; }
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes, int* used) {
  result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
  memcpy(result[resultSize], path, sizeof(int) * pathSize);
  (*returnColumnSizes)[resultSize] = pathSize;
  resultSize++;

  for (int i = startIndex; i < numsSize; i++) {
    if (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == 0) {
      continue;
    }
    path[pathSize++] = nums[i];
    used[i] = 1;
    backtracking(nums, numsSize, i + 1, returnColumnSizes, used);
    used[i] = 0;
    pathSize--;
  }

  return;
}
int** subsetsWithDup(int* nums, int numsSize, int* returnSize,
                     int** returnColumnSizes) {
  int maxSize = 1 << numsSize;
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = malloc(sizeof(int) * maxSize);
  resultSize = pathSize = 0;
  int used[numsSize];
  memset(used, 0, sizeof(used));
  qsort(nums, numsSize, sizeof(int), cmp);
  backtracking(nums, numsSize, 0, returnColumnSizes, used);
  *returnSize = resultSize;

  return result;
}

// @lc code=end
