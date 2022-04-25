/*
给你一个整数n，对于0 <= i <= n中的每个i，
计算其二进制表示中1的个数，返回一个长度为n+1的数组ans作为答案。

示例1：
输入：n = 2
输出：[0,1,1]
解释：
0 --> 0
1 --> 1
2 --> 10

示例2：
输入：n = 5
输出：[0,1,1,2,1,2]
解释：
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

提示：0 <= n <= 105

进阶：
很容易就能实现时间复杂度为O(nlogn)的解决方案，你可以在线性时间复杂度O(n)内用一趟扫描解决此问题吗？
你能不使用任何内置函数解决此问题吗？
*/

// Brian Kernighan算法
int countOnes(int x) {
  int ones = 0;
  while (x > 0) {
    x &= (x - 1);
    ones++;
  }
  return ones;
}
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  for (int i = 0; i <= n; i++) {
    // 需要对每个整数使用O(log⁡n)的时间计算比特数
    bits[i] = countOnes(i);
  }
  return bits;
}

int* countBits(int num, int* returnSize) {
  int* ret = (int*)malloc((num + 1) * sizeof(int));
  *returnSize = num + 1;
  ret[0] = 0;
  for (int i = 1; i <= num; ++i) {
    if (i % 2 == 0) {
      ret[i] = ret[i / 2];
    } else {
      ret[i] = ret[i / 2] + 1;
    }
  }

  return ret;
}

// 动态规划——最高有效位
int* countBits(int n, int* returnSize) {
  int* ret = (int*)malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  ret[0] = 0;
  int high = 0;
  for (int i = 1; i <= n; ++i) {
    // i & (i - 1) : 把二进制最低位的1变成0
    // (n > 0 && ((n & (n - 1)) == 0)是判断n是不是2的次幂
    if ((i & (i - 1)) == 0) {
      high = i;
    }
    ret[i] = ret[i - high] + 1;
  }

  // 8
  // [0,1,1,2,1,2,2,3,1]
  // high:1,ret[1] = ret[0] + 1, 1
  // high:2,ret[2] = ret[0] + 1, 1
  // high:2,ret[3] = ret[1] + 1, 2
  // high:4,ret[4] = ret[0] + 1, 1
  // high:4,ret[5] = ret[1] + 1, 2
  // high:4,ret[6] = ret[2] + 1, 2
  // high:4,ret[7] = ret[3] + 1, 3
  // high:8,ret[8] = ret[0] + 1, 1

  return ret;
}

// 动态规划——最低有效位
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  bits[0] = 0;
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i >> 1] + (i & 1);
  }
  return bits;
}

// 动态规划——最低设置位
// 定义正整数x的「最低设置位」为x的二进制表示中的最低的1所在位。
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  bits[0] = 0;
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i & (i - 1)] + 1;
  }
  return bits;
}