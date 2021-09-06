/*
 * @lc app=leetcode.cn id=46 lang=c
 *
 * [46] 全排列
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** result;
int resultSize;
int* path;
int pathSize;
// 处理排列问题就不⽤使⽤startIndex了
void backtracking(int* nums, int numsSize, int* used) {
  if (pathSize == numsSize) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize++], path, sizeof(int) * pathSize);
    return;
  }

  for (int i = 0; i < numsSize; ++i) {
    // used数组，其实就是记录此时path⾥都有哪些元素使⽤了，⼀个排列⾥⼀个元素只能使⽤⼀次。
    if (used[i]) {  // path⾥已经收录的元素，直接跳过
      continue;
    }
    path[pathSize++] = nums[i];
    used[i] = 1;
    backtracking(nums, numsSize, used);
    used[i] = 0;
    pathSize--;
  }

  return;
}
int** permute(int* nums, int numsSize, int* returnSize,
              int** returnColumnSizes) {
  (*returnSize) = 1;
  for (int i = 1; i <= numsSize; i++) {
    (*returnSize) *= i;
  }
  result = (int**)malloc(sizeof(int*) * (*returnSize));
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
  for (int i = 0; i < *returnSize; ++i) {
    (*returnColumnSizes)[i] = numsSize;
  }
  resultSize = pathSize = 0;
  int used[numsSize];  // 排列问题需要⼀个used数组，标记已经选择的元素
  memset(used, 0, sizeof(used));
  backtracking(nums, numsSize, used);

  return result;
}
// @lc code=end
