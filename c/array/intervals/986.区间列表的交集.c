int** intervalIntersection(int** firstList, int firstListSize,
                           int* firstListColSize, int** secondList,
                           int secondListSize, int* secondListColSize,
                           int* returnSize, int** returnColumnSizes) {
  if (firstListSize == 0 || secondList == 0) {
    return NULL;
  }

  int resMaxLen = firstListSize + secondListSize;
  int** res = (int**)malloc(sizeof(int*) * resMaxLen);
  *returnSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * resMaxLen);

  int f = 0;
  int s = 0;
  while (f < firstListSize && s < secondListSize) {
    // printf("first:%d %d, second:%d %d\n",firstList[f][0],firstList[f][1],secondList[s][0],secondList[s][1]);
    // if (firstList[f][0] > secondList[s][1] ||
    //     firstList[f][1] < secondList[s][0]) {
    //   firstList[f][1] < secondList[s][1] ? f++ : s++;
    //   continue;
    // }
    // res[*returnSize] = (int*)malloc(sizeof(int) * 2);
    // res[*returnSize][0] = fmax(firstList[f][0], secondList[s][0]);
    // res[*returnSize][1] = fmin(firstList[f][1], secondList[s][1]);
    // (*returnSize)++;
    // firstList[f][1] < secondList[s][1] ? f++ : s++;
    int start = fmax(firstList[f][0], secondList[s][0]);
    int end = fmin(firstList[f][1], secondList[s][1]);
    if (start <= end) {
      res[*returnSize] = (int*)malloc(sizeof(int) * 2);
      res[*returnSize][0] = start;
      res[*returnSize][1] = end;
      (*returnSize)++;
    }
    firstList[f][1] < secondList[s][1] ? f++ : s++;
  }

  for (int i = 0; i < *returnSize; ++i) {
    (*returnColumnSizes)[i] = 2;
  }

  return res;
}