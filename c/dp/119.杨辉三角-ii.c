/*
给定一个非负索引rowIndex，返回「杨辉三角」的第rowIndex行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。

示例1:
输入: rowIndex = 3
输出: [1,3,3,1]

示例2:
输入: rowIndex = 0
输出: [1]

示例3:
输入: rowIndex = 1
输出: [1,1]

提示: 0 <= rowIndex <= 33
*/

int* getRow(int rowIndex, int* returnSize) {
  *returnSize = rowIndex + 1;
  int* ret = (int*)malloc(*returnSize * sizeof(int));
  memset(ret, 0, sizeof(int) * (*returnSize));

  ret[0] = 1;
  for (int i = 1; i <= rowIndex; ++i) {
    for (int j = i; j > 0; --j) {
      ret[j] += ret[j - 1];
    }
  }

  return ret;
}
