/*
给你一个有n个节点的有向无环图（DAG），请你找出所有从节点0到节点n-1的路径并输出（不要求按特定顺序）
graph[i]是一个从节点i可以访问的所有节点的列表（即从节点i到节点graph[i][j]存在一条有向边）。

示例1：
输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径0 -> 1 -> 3和0 -> 2 -> 3

示例2：
输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

提示：
n == graph.length
2 <= n <= 15
0 <= graph[i][j] < n
graph[i][j] != i（即不存在自环）
graph[i]中的所有元素互不相同
保证输入为有向无环图（DAG）
*/

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