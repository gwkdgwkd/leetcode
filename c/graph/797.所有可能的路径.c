#define MAXSIZE 7000
int** res;
int* path;
int resSize;
int pathSize;
// 图的遍历
void traverse(int** graph, int graphSize, int* graphColSize,
              int** returnColumnSizes, int item) {
  path[pathSize++] = item;
  // printf("%d,%d\n",index,pathSize);

  if (item == graphSize - 1) {
    res[resSize] = (int*)malloc(sizeof(int) * graphSize);
    (*returnColumnSizes)[resSize] = pathSize;
    for (int i = 0; i < pathSize; ++i) {
      res[resSize][i] = path[i];
      // printf("%d ",path[i]);
    }
    // printf("\n");
    pathSize--;
    resSize++;
    return;
  }
  for (int i = 0; i < graphColSize[item]; ++i) {
    traverse(graph, graphSize, graphColSize, returnColumnSizes, graph[item][i]);
  }
  pathSize--;
}
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize,
                           int* returnSize, int** returnColumnSizes) {
  // printf("graphSize %d\n",graphSize);
  res = (int**)malloc(sizeof(int*) * MAXSIZE);
  path = (int*)malloc(sizeof(int) * (graphSize));
  resSize = pathSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * MAXSIZE);
  traverse(graph, graphSize, graphColSize, returnColumnSizes, 0);

  *returnSize = resSize;
  return res;
}

// 官方题解
int** ans;
int stk[15];
int stkSize;
void dfs(int x, int n, int** graph, int* graphColSize, int* returnSize,
         int** returnColumnSizes) {
  if (x == n) {
    int* tmp = malloc(sizeof(int) * stkSize);
    memcpy(tmp, stk, sizeof(int) * stkSize);
    ans[*returnSize] = tmp;
    (*returnColumnSizes)[(*returnSize)++] = stkSize;
    return;
  }
  for (int i = 0; i < graphColSize[x]; i++) {
    int y = graph[x][i];
    stk[stkSize++] = y;
    dfs(y, n, graph, graphColSize, returnSize, returnColumnSizes);
    stkSize--;
  }
}
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize,
                           int* returnSize, int** returnColumnSizes) {
  stkSize = 0;
  stk[stkSize++] = 0;
  ans = malloc(sizeof(int*) * 16384);
  *returnSize = 0;
  *returnColumnSizes = malloc(sizeof(int) * 16384);
  dfs(0, graphSize - 1, graph, graphColSize, returnSize, returnColumnSizes);
  return ans;
}