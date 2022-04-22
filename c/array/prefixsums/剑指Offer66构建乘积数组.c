/*
给定一个数组A[0,1,…,n-1]，请构建一个数组B[0,1,…,n-1]，
其中B[i]的值是数组A中除了下标i以外的元素的积, 
即B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。
不能使用除法。

示例:
输入: [1,2,3,4,5]
输出: [120,60,40,30,24]

提示：
所有元素乘积之和不会溢出32位整数
a.length <= 100000
*/

int* constructArr(int* a, int aSize, int* returnSize) {
  *returnSize = aSize;
  if (aSize == 0) {
    return NULL;
  }

  int left[aSize];
  int right[aSize];
  left[0] = right[aSize - 1] = 1;
  for (int i = 1; i < aSize; ++i) {
    left[i] = left[i - 1] * a[i - 1];
  }
  for (int i = aSize - 2; i >= 0; --i) {
    right[i] = right[i + 1] * a[i + 1];
  }

  int* res = (int*)malloc(sizeof(int) * aSize);
  for (int i = 0; i < aSize; ++i) {
    res[i] = left[i] * right[i];
  }

  return res;
}
