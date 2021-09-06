/*
 * @lc app=leetcode.cn id=47 lang=c
 *
 * [47] 全排列 II
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
int cmp(int* a, int* b) { return *a > *b; }
void backtracking(int* nums, int numsSize, int* used) {
  if (pathSize == numsSize) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize++], path, sizeof(int) * pathSize);
    return;
  }

  for (int i = 0; i < numsSize; ++i) {
    // used[i-1] == 1，说明同⼀树⽀nums[i-1]使⽤过
    // used[i-1] == 0，说明同⼀树层nums[i-1]使⽤过
    // 如果同⼀树层nums[i-1]使⽤过则直接跳过
    // 如果要对树层中前⼀位去重，就⽤ used[i-1] == false ，如果要对树枝前⼀位去重⽤used[i-1] == true 。
    // 对于排列问题，树层上去重和树枝上去重，都是可以的，但是树层上去重效率更⾼！树枝上对前⼀位去重虽然最后可以得到答案，但是做了很多⽆⽤搜索。
    // if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 1)) {  // 也正确
    if (used[i] || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 0)) {
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
int** permuteUnique(int* nums, int numsSize, int* returnSize,
                    int** returnColumnSizes) {
  int maxSize = 1;
  for (int i = 1; i <= numsSize; i++) {
    maxSize *= i;
  }
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = (int*)malloc(sizeof(int) * maxSize);
  for (int i = 0; i < maxSize; ++i) {
    (*returnColumnSizes)[i] = numsSize;
  }
  resultSize = pathSize = 0;
  int used[numsSize];
  memset(used, 0, sizeof(used));
  qsort(nums, numsSize, sizeof(int), cmp);
  backtracking(nums, numsSize, used);
  *returnSize = resultSize;

  return result;
}

// @lc code=end
