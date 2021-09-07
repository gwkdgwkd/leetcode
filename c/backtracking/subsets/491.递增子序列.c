/*
 * @lc app=leetcode.cn id=491 lang=c
 *
 * [491] 递增子序列
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
// 递增⼦序列⽐较像是取有序的⼦集。⽽且也要求不能有相同的递增⼦序列。
// ⼜是⼦集，⼜是去重，是不是不由⾃主的想起了90，子集-ii，但求⾃增⼦序列，是不能对原数组经⾏排序的，排完序的数组都是⾃增⼦序列了。
// 所以不能使⽤之前的去重逻辑！
int** result;
int resultSize;
int* path;
int pathSize;
// 求⼦序列，很明显⼀个元素不能重复使⽤，所以需要startIndex，调整下⼀层递归的起始位置。
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes) {
  if (pathSize > 1) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
  }

  // 和78⼀样，可以不加终⽌条件，startIndex每次都会加1，并不会⽆限递归。

  // 同⼀⽗节点下的同层上使⽤过的元素就不能在使⽤了
  int used[201];  // hash
  memset(used, 0, sizeof(used));
  for (int i = startIndex; i < numsSize; ++i) {
    if ((pathSize > 0 && nums[i] < path[pathSize - 1]) ||
        (used[nums[i] + 100] == 1)) {
      continue;
    }
    // 只有赋值，没有复位
    used[nums[i] + 100] = 1;  // 记录元素在本层⽤过了，本层后⾯不能再⽤
    path[pathSize++] = nums[i];
    backtracking(nums, numsSize, i + 1, returnColumnSizes);
    pathSize--;
  }

  return;
}
int** findSubsequences(int* nums, int numsSize, int* returnSize,
                       int** returnColumnSizes) {
  int maxSize = 1 << numsSize;
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = malloc(sizeof(int) * maxSize);
  resultSize = pathSize = 0;
  backtracking(nums, numsSize, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}
// @lc code=end
