/*
给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。
最高位数字存放在数组的首位，数组中每个元素只存储单个数字。
你可以假设除了整数0之外，这个整数不会以零开头。

示例1：
输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字123。

示例2：
输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字4321。

示例3：
输入：digits = [0]
输出：[1]

提示：
1 <= digits.length <= 100
0 <= digits[i] <= 9
*/

int* plusOne(int* digits, int digitsSize, int* returnSize) {
  int flag = 1;
  for (int i = digitsSize - 1; i >= 0; --i) {
    if (digits[i] == 9 && flag == 1) {
      digits[i] = 0;
      flag = 1;
    } else {
      digits[i] += flag;
      flag = 0;
    }
  }

  *returnSize = digitsSize + flag;
  int* result = (int*)malloc(sizeof(int) * (*returnSize));
  int index = 0;
  if (flag) {
    result[index++] = 1;
  }

  for (int i = 0; i < digitsSize; ++i) {
    result[index++] = digits[i];
  }
  return result;
}