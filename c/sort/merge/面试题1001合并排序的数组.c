/*
给定两个排序后的数组A和B，其中A的末端有足够的缓冲空间容纳B。
编写一个方法，将B合并入A并排序。
初始化A和B的元素数量分别为m和n。

示例:
输入:
A = [1,2,3,0,0,0], m = 3
B = [2,5,6],       n = 3
输出:[1,2,2,3,5,6]

说明: A.length == n + m
*/

void merge(int* A, int ASize, int m, int* B, int BSize, int n) {
  int ia = m - 1;
  int ib = n - 1;
  int i = ASize - 1;

  while (ia >= 0 || ib >= 0) {
    if (ia < 0) {
      A[i--] = B[ib--];
    } else if (ib < 0) {
      A[i--] = A[ia--];
    } else {
      if (A[ia] >= B[ib]) {
        A[i--] = A[ia--];
      } else {
        A[i--] = B[ib--];
      }
    }
  }
}

int cmp(int* a, int* b) { return *a - *b; }
void merge(int* A, int ASize, int m, int* B, int BSize, int n) {
  memcpy(A + m, B, sizeof(int) * n);
  qsort(A, ASize, sizeof(int), cmp);
}