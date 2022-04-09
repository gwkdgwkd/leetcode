/*
给出非负整数数组A，返回两个非重叠（连续）子数组中元素的最大和，子数组的长度分别为L和M。
这里需要澄清的是，长为L的子数组可以出现在长为M的子数组之前或之后。
从形式上看，返回最大的V，而V=(A[i]+A[i+1]+...+A[i+L-1])+(A[j]+A[j+1]+...+A[j+M-1])
并满足下列条件之一：
0 <= i < i + L - 1 < j < j + M - 1 < A.length,或
0 <= j < j + M - 1 < i < i + L - 1 < A.length.

示例1：
输入：A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
输出：20
解释：子数组的一种选择中，[9]长度为1，[6,5]长度为2。

示例2：
输入：A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
输出：29
解释：子数组的一种选择中，[3,8,1]长度为3，[8,9]长度为2。

示例3：
输入：A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
输出：31
解释：子数组的一种选择中，[5,6,0,9]长度为4，[0,3,8]长度为3。

提示：
L >= 1
M >= 1
L + M <= A.length <= 1000
0 <= A[i] <= 1000
*/

// 前缀和 + 动态规划
#define max(a, b) ((a) > (b) ? (a) : (b))
int maxSumTwoNoOverlap(int* A, int ASize, int L, int M) {
  int* s;
  int prevMaxSum, sum, i, t;

  s = malloc((ASize + 1) * sizeof(int));
  s[0] = sum = 0;
  for (i = 1; i <= ASize; i++) s[i] = s[i - 1] + A[i - 1];

  // L、M前后关系的两种情况
  for (t = 0; t < 2; t++) {
    prevMaxSum = 0;
    for (i = L; i + M <= ASize; i++) {
      prevMaxSum = max(prevMaxSum, s[i] - s[i - L]);
      sum = max(sum, prevMaxSum + s[i + M] - s[i]);
    }
    // 借用prevMaxSum来交换一下L和M
    prevMaxSum = L;
    L = M;
    M = prevMaxSum;
  }

  free(s);
  return sum;
}
