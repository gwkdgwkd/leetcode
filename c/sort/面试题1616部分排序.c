/*
给定一个整数数组，编写一个函数，找出索引m和n，只要将索引区间[m,n]的元素排好序，整个数组就是有序的。
注意：n-m尽量最小，也就是说，找出符合条件的最短序列。
函数返回值为[m,n]，若不存在这样的m和n（例如整个数组是有序的），请返回[-1,-1]。

示例：
输入： [1,2,4,7,10,11,7,12,6,7,16,18,19]
输出： [3,9]

提示：0 <= len(array) <= 1000000
*/

// 先排序再比较
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int *subSort(int *array, int arraySize, int *returnSize) {
  int *tmp = (int *)malloc(sizeof(int) * arraySize);
  memcpy(tmp, array, sizeof(int) * arraySize);

  qsort(tmp, arraySize, sizeof(int), cmp);
  int *retAns = (int *)malloc(2 * sizeof(int));
  retAns[0] = -1;
  retAns[1] = -1;
  *returnSize = 2;

  for (int i = 0; i < arraySize; i++) {
    if (array[i] != tmp[i] && retAns[0] == -1) {
      retAns[0] = i;
    }

    if (array[i] != tmp[i]) {
      retAns[1] = i;
    }
  }

  return retAns;
}