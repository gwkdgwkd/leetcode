/*
n位格雷码序列是一个由2^n个整数组成的序列，其中：
每个整数都在范围[0, 2^n - 1]内（含0和2^n - 1），第一个整数是0，
一个整数在序列中出现不超过一次每对相邻整数的二进制表示恰好一位不同，
且第一个和最后一个整数的二进制表示恰好一位不同。
给你一个整数n，返回任一有效的n位格雷码序列。

示例1：
输入：n = 2
输出：[0,1,3,2]
解释：
[0,1,3,2]的二进制表示是[00,01,11,10]。
- 00和01有一位不同
- 01和11有一位不同
- 11和10有一位不同
- 10和00有一位不同
[0,2,3,1] 也是一个有效的格雷码序列，其二进制表示是[00,10,11,01]。
- 00和10有一位不同
- 10和11有一位不同
- 11和01有一位不同
- 01和00有一位不同

示例2：
输入：n = 1
输出：[0,1]

提示：1 <= n <= 16
*/

// 对称生成
int* grayCode(int n, int* returnSize) {
  int* ret = (int*)malloc((1 << n) * sizeof(int));
  ret[0] = 0;
  int ret_size = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = ret_size - 1; j >= 0; j--) {
      ret[2 * ret_size - 1 - j] = ret[j] | (1 << (i - 1));
    }
    ret_size <<= 1;
  }
  *returnSize = ret_size;
  return ret;
}

// 二进制数转格雷码
int* grayCode(int n, int* returnSize) {
  int ret_size = 1 << n;
  int* ret = (int*)malloc(ret_size * sizeof(int));
  for (int i = 0; i < ret_size; i++) {
    ret[i] = (i >> 1) ^ i;
  }
  *returnSize = ret_size;
  return ret;
}