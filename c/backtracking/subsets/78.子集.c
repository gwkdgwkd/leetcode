/*
 * @lc app=leetcode.cn id=78 lang=c
 *
 * [78] 子集
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
// 组合问题和分割问题都是收集树的叶⼦节点，⽽⼦集问题是找树的所有节点！
int** result;
int resultSize;
int* path;
int pathSize;
void backtracking(int* nums, int numsSize, int startIndex,
                  int** returnColumnSizes) {
  // 收集⼦集，要放在终⽌添加的上⾯，否则会漏掉⾃⼰
  result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
  for (int i = 0; i < pathSize; ++i) {
    result[resultSize][i] = path[i];
  }
  (*returnColumnSizes)[resultSize] = pathSize;
  resultSize++;
  // 其实可以不需要加终⽌条件，因为startIndex >= numsSize，本层for循环本来也结束了。
  // if (startIndex >= numsSize) {
  //   return;
  // }

  // 求取⼦集问题，不需要任何剪枝！因为⼦集就是要遍历整棵树。
  for (int i = startIndex; i < numsSize; i++) {
    path[pathSize++] = nums[i];
    // 从i+1开始，元素不重复取
    backtracking(nums, numsSize, i + 1, returnColumnSizes);
    pathSize--;
  }

  return;
}
int** subsets(int* nums, int numsSize, int* returnSize,
              int** returnColumnSizes) {
  int maxSize = 1 << numsSize;  // 不重复子集的个数？
  result = (int**)malloc(sizeof(int*) * maxSize);
  path = (int*)malloc(sizeof(int) * numsSize);
  *returnColumnSizes = malloc(sizeof(int) * maxSize);
  resultSize = pathSize = 0;
  backtracking(nums, numsSize, 0, returnColumnSizes);
  *returnSize = resultSize;

  return result;
}
// @lc code=end
