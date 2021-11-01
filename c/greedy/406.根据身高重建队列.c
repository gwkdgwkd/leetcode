// 贪心算法
typedef struct peopleStr {
  int height;
  int hCount;
} peopleStr;
int heighCmp(const void* hCount1, const void* hCount2) {
  const peopleStr* l1 = *(const peopleStr**)hCount1;
  const peopleStr* l2 = *(const peopleStr**)hCount2;
  if (l1->height == l2->height) {
    return ((l1->hCount) - (l2->hCount));
  }
  return ((l2->height) - (l1->height));
}
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize,
                       int* returnSize, int** returnColumnSizes) {
  int heightCount;
  int* colSize = NULL;
  colSize = (int*)malloc(sizeof(int) * peopleSize);

  int** res = NULL;
  res = (int**)malloc(sizeof(int*) * peopleSize);

  qsort(people, peopleSize, sizeof(int*), heighCmp);

  for (int i = 0; i < peopleSize; i++) {
    heightCount = people[i][1];
    memmove(&res[heightCount + 1], &res[heightCount],
            (i - heightCount) * sizeof(int*));
    res[heightCount] = (int*)malloc(sizeof(int) * 2);
    res[heightCount][0] = people[i][0];
    res[heightCount][1] = people[i][1];
  }
  *returnColumnSizes = peopleColSize;
  *returnSize = peopleSize;
  return res;
}