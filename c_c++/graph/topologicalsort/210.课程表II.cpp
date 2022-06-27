/*
现在你总共有numCourses门课需要选，记为0到numCourses - 1。
给你一个数组prerequisites，其中prerequisites[i]=[ai,bi]，表示在选修课程ai前必须先选修bi。
例如，想要学习课程0，你需要先完成课程1，我们用一个匹配来表示：[0,1]。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，
你只要返回任意一种就可以了。如果不可能完成所有课程，返回一个空数组。

示例1：
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有2门课程。要学习课程1，你需要先完成课程0。因此，正确的课程顺序为[0,1]。

示例2：
输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有4门课程。要学习课程3，你应该先完成课程1和课程2。并且课程1和课程2都应该排在课程0之后。
因此，一个正确的课程顺序是[0,1,2,3]。另一个正确的排序是[0,2,1,3]。

示例3：
输入：numCourses = 1, prerequisites = []
输出：[0]

提示：
1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
所有[ai, bi]互不相同
*/

// 剑指OfferII113课程顺序

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

// 深度优先搜索
class Solution {
 private:
  vector<vector<int>> edges;  // 存储有向图
  vector<int> visited;  // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
  vector<int> result;  // 用数组来模拟栈，下标0为栈底，n-1为栈顶
  bool valid = true;   // 判断有向图中是否有环

 public:
  void dfs(int u) {
    visited[u] = 1;  // 将节点标记为搜索中
    for (int v : edges[u]) {  // 搜索其相邻节点，只要发现有环，立刻停止搜索
      if (visited[v] == 0) {  // 如果是未搜索，那么搜索相邻节点
        dfs(v);
        if (!valid) {
          return;
        }
      } else if (visited[v] == 1) {  // 如果是搜索中，说明找到了环
        valid = false;
        return;
      }
    }
    visited[u] = 2;       // 将节点标记为已完成
    result.push_back(u);  // 将节点入栈
  }

  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    edges.resize(numCourses);
    visited.resize(numCourses);
    for (const auto &info : prerequisites) {
      edges[info[1]].push_back(info[0]);
    }

    for (int i = 0; i < numCourses && valid; ++i) {
      if (!visited[i]) {  // 每次挑选一个未搜索的节点，开始进行深度优先搜索
        dfs(i);
      }
    }
    if (!valid) {
      return {};
    }

    // 如果没有环，那么就有拓扑排序
    // 注意下标0为栈底，因此需要将数组反序输出
    reverse(result.begin(), result.end());
    return result;
  }
};

// 广度优先搜索
class Solution {
 private:
  vector<vector<int>> edges;  // 存储有向图
  vector<int> indeg;          // 存储每个节点的入度
  vector<int> result;         // 存储答案

 public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    edges.resize(numCourses);
    indeg.resize(numCourses);
    for (const auto &info : prerequisites) {
      edges[info[1]].push_back(info[0]);
      ++indeg[info[0]];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {  // 将所有入度为0的节点放入队列中
      if (indeg[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      int u = q.front();  // 从队首取出一个节点
      q.pop();
      result.push_back(u);  // 放入答案中
      for (int v : edges[u]) {
        --indeg[v];
        if (indeg[v] == 0) {  // 如果相邻节点v的入度为0，就可以选v对应的课程了
          q.push(v);
        }
      }
    }

    if (result.size() != numCourses) {
      return {};
    }
    return result;
  }
};
