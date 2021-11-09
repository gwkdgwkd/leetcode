#define QUE_MAX 100000

typedef struct Node {
  int val;
  struct Node *next;
} * GraghNode;  // 节点

typedef struct gNode {
  int size;
  GraghNode *Lists;  // 保存每个节点的邻接节点数组
} * Gragh;           // 邻接表

int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
  // 构建邻接表
  Gragh G = (Gragh)malloc(sizeof(struct gNode));
  G->size = numCourses;
  G->Lists = (GraghNode *)malloc(sizeof(GraghNode) * G->size);
  for (int i = 0; i < G->size; i++) {
    G->Lists[i] = (GraghNode)malloc(sizeof(struct Node));
    G->Lists[i]->next = NULL;
  }

  // 初始化入度数组并赋值
  int *Indegree = (int *)malloc(sizeof(int) * numCourses);
  memset(Indegree, 0, sizeof(int) * numCourses);
  for (int i = 0; i < prerequisitesSize; i++) {
    Indegree[prerequisites[i][0]]++;
    GraghNode node = (GraghNode)malloc(sizeof(struct Node));
    node->val = prerequisites[i][0];
    node->next = G->Lists[prerequisites[i][1]]->next;
    G->Lists[prerequisites[i][1]]->next = node;
  }

  // que保存入度为0的节点
  int que[QUE_MAX];
  int head = 0, tail = 0;
  for (int i = 0; i < numCourses; i++) {
    if (Indegree[i] == 0) {
      que[tail++] = i;
    }
  }

  // 保存拓扑排序的数组
  int *topSortNumber = (int *)malloc(sizeof(int) * numCourses);
  int count = 0;

  // 入度为0的节点出队并将相邻节点入度减一，若减为0则入队
  while (head < tail) {
    int V = que[head];
    topSortNumber[count++] = V;
    // 与V相邻的节点入度减一
    GraghNode node = G->Lists[V]->next;
    while (node) {
      Indegree[node->val]--;
      if (Indegree[node->val] == 0) {
        que[tail++] = node->val;
      }
      node = node->next;
    }
    head++;
  }

  // 若所有节点最终都能入队并出队，则说明有向图无环，能够修完所有课程
  if (count == numCourses) {
    *returnSize = count;
  } else {
    *returnSize = 0;
  }

  return topSortNumber;
}

// 递归遍历
typedef struct Node {
  int val;
  struct Node *next;
} * GraghNode;  // 节点
typedef struct gNode {
  int size;
  GraghNode *Lists;  // 保存每个节点的邻接节点数组
} * Gragh;           // 邻接表
Gragh buildGragh(int numCourses, int **prerequisites, int prerequisitesSize) {
  // 构建邻接表
  Gragh G = (Gragh)malloc(sizeof(struct gNode));
  G->size = numCourses;
  G->Lists = (GraghNode *)malloc(sizeof(GraghNode) * G->size);
  for (int i = 0; i < G->size; i++) {
    G->Lists[i] = (GraghNode)malloc(sizeof(struct Node));
    G->Lists[i]->next = NULL;
  }

  for (int i = 0; i < prerequisitesSize; i++) {
    GraghNode node = (GraghNode)malloc(sizeof(struct Node));
    node->val = prerequisites[i][0];
    node->next = G->Lists[prerequisites[i][1]]->next;
    G->Lists[prerequisites[i][1]]->next = node;
  }

  return G;
}
bool *onPath;
bool hasCycle;
// 防止重复遍历同一个节点
bool *visited;
// 从节点s开始BFS遍历，将遍历过的节点标记为true
int *postorder;
int postSize;
void traverse(Gragh graph, int s) {
  if (onPath[s]) {
    hasCycle = true;  // 出现环
  }

  if (visited[s] || hasCycle) {
    return;  // 如果已经找到了环，也不用再遍历了
  }
  // 前序遍历代码位置
  visited[s] = true;
  onPath[s] = true;
  GraghNode n = graph->Lists[s]->next;
  while (n) {
    traverse(graph, n->val);
    n = n->next;
  }
  // 后序遍历代码位置
  onPath[s] = false;
  postorder[postSize++] = s;  // 后序遍历
}
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
  if (numCourses == 0) {
    *returnSize = numCourses;
    return NULL;
  }
  postorder = (int *)malloc(sizeof(int) * numCourses);
  if (numCourses == 1) {
    *returnSize = numCourses;
    postorder[0] = 0;
    return postorder;
  }

  Gragh G = buildGragh(numCourses, prerequisites, prerequisitesSize);

  hasCycle = false;
  visited = (bool *)malloc(sizeof(bool) * numCourses);
  onPath = (bool *)malloc(sizeof(bool) * numCourses);
  for (int i = 0; i < numCourses; i++) {
    visited[i] = onPath[i] = false;
  }

  postSize = 0;
  for (int i = 0; i < numCourses; i++) {
    traverse(G, i);
  }

  if (!hasCycle) {  // 没有环
    // 将后序遍历的结果进行反转，就是拓扑排序的结果。
    for (int l = 0, r = postSize - 1; l < r; ++l, --r) {
      int tmp = postorder[l];
      postorder[l] = postorder[r];
      postorder[r] = tmp;
    }
    *returnSize = postSize;
  } else {  // 有环
    *returnSize = 0;
  }
  return postorder;
}

// 官方题解，深度优先搜素
int **edges;
int *edgeColSize;
int *visited;
int *result;
int resultSize;
bool valid;
void dfs(int u) {
  visited[u] = 1;
  for (int i = 0; i < edgeColSize[u]; ++i) {
    if (visited[edges[u][i]] == 0) {
      dfs(edges[u][i]);
      if (!valid) {
        return;
      }
    } else if (visited[edges[u][i]] == 1) {
      valid = false;
      return;
    }
  }
  visited[u] = 2;
  result[resultSize++] = u;
}
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
  valid = true;
  edges = (int **)malloc(sizeof(int *) * numCourses);
  for (int i = 0; i < numCourses; i++) {
    edges[i] = (int *)malloc(0);
  }
  edgeColSize = (int *)malloc(sizeof(int) * numCourses);
  memset(edgeColSize, 0, sizeof(int) * numCourses);
  visited = (int *)malloc(sizeof(int) * numCourses);
  memset(visited, 0, sizeof(int) * numCourses);
  for (int i = 0; i < prerequisitesSize; ++i) {
    int a = prerequisites[i][1], b = prerequisites[i][0];
    edgeColSize[a]++;
    edges[a] = (int *)realloc(edges[a], sizeof(int) * edgeColSize[a]);
    edges[a][edgeColSize[a] - 1] = b;
  }
  result = (int *)malloc(sizeof(int) * numCourses);
  resultSize = 0;
  for (int i = 0; i < numCourses && valid; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  for (int i = 0; i < numCourses; i++) {
    free(edges[i]);
  }
  free(edges);
  free(edgeColSize);
  free(visited);
  if (!valid) {
    *returnSize = 0;
  } else
    *returnSize = numCourses;
  for (int i = 0; i < numCourses / 2; i++) {
    int t = result[i];
    result[i] = result[numCourses - i - 1], result[numCourses - i - 1] = t;
  }
  return result;
}

// 官方题解，广度优先搜索
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
  int **edges = (int **)malloc(sizeof(int *) * numCourses);
  for (int i = 0; i < numCourses; i++) {
    edges[i] = (int *)malloc(0);
  }
  int edgeColSize[numCourses];
  memset(edgeColSize, 0, sizeof(edgeColSize));
  int indeg[numCourses];
  memset(indeg, 0, sizeof(indeg));
  for (int i = 0; i < prerequisitesSize; ++i) {
    int a = prerequisites[i][1], b = prerequisites[i][0];
    edgeColSize[a]++;
    edges[a] = (int *)realloc(edges[a], sizeof(int) * edgeColSize[a]);
    edges[a][edgeColSize[a] - 1] = b;
    ++indeg[b];
  }

  int q[numCourses];
  int l = 0, r = -1;
  for (int i = 0; i < numCourses; ++i) {
    if (indeg[i] == 0) {
      q[++r] = i;
    }
  }

  int *result = (int *)malloc(sizeof(int) * numCourses);
  int resultSize = 0;

  int visited = 0;
  while (l <= r) {
    ++visited;
    int u = q[l++];
    result[resultSize++] = u;
    for (int i = 0; i < edgeColSize[u]; ++i) {
      --indeg[edges[u][i]];
      if (indeg[edges[u][i]] == 0) {
        q[++r] = edges[u][i];
      }
    }
  }
  for (int i = 0; i < numCourses; i++) {
    free(edges[i]);
  }
  free(edges);
  if (visited == numCourses) {
    *returnSize = numCourses;
  } else {
    *returnSize = 0;
  }
  return result;
}