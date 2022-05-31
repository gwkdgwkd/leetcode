/*
编写一个函数，不用临时变量，直接交换numbers = [a, b]中a与b的值。

示例：
输入: numbers = [1,2]
输出: [2,1]

提示：
numbers.length == 2
-2147483647 <= numbers[i] <= 2147483647
*/

// 位运算
int* swapNumbers(int* numbers, int numbersSize, int* returnSize) {
  *returnSize = numbersSize;

  numbers[0] ^= numbers[1];
  numbers[1] ^= numbers[0];
  numbers[0] ^= numbers[1];
  return numbers;
}

// 溢出
int* swapNumbers(int* numbers, int numbersSize, int* returnSize) {
  *returnSize = numbersSize;

  numbers[0] = numbers[0] + numbers[1];
  numbers[1] = numbers[0] - numbers[1];
  numbers[0] = numbers[0] - numbers[1];

  return numbers;
}

// 使用来临时变量
int* swapNumbers(int* numbers, int numbersSize, int* returnSize) {
  *returnSize = numbersSize;

  int tmp = numbers[0];
  numbers[0] = numbers[1];
  numbers[1] = tmp;
  return numbers;
}