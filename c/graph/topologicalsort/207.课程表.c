/*
你这个学期必须选修numCourses门课程，记为0到numCourses - 1。
在选修某些课程之前需要一些先修课程。
先修课程按数组prerequisites给出，其中prerequisites[i] = [ai, bi]，
表示如果要学习课程ai则必须先学习课程bi。
例如，先修课程对[0, 1]表示：想要学习课程0，你需要先完成课程1。
请你判断是否可能完成所有课程的学习？如果可以，返回true；否则，返回false。

示例1：
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有2门课程。学习课程1之前，你需要完成课程0。这是可能的。

示例2：
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有2门课程。学习课程1之前，你需要先完成​课程0；
     并且学习课程0之前，你还应先完成课程1。这是不可能的。
*/

// 拓扑排序就是由某个集合上的一个偏序得到该集合上的一个全序。
// 某个集合的偏序就是指集合中仅有部分成员之间可比较，而全序是集合中全部成员都可以进行比较。
// 可以进行拓扑排序的需要是一个有向无环图。
// 对一个图进行拓扑排序，就要进行以下几个步骤：
// 1.在有向图中选一个没有前驱的顶点并输入之；
// 2.从图中删除该顶点和所有以它为尾的弧；
// 重复这两个步骤，直到所有顶点均以输出（拓扑排序成功），
// 或者当前图中不存在无前驱的顶点为止（说明图中存在环，无法进行排序）。

// 拓扑排序 + 图的邻接表存储 + bfs
#define QUE_MAX 100000
typedef struct Node {
  int val;
  struct Node *next;
} * GraghNode;  // 节点
typedef struct gNode {
  int size;
  GraghNode *Lists;  // 保存每个节点的邻接节点数组
} * Gragh;           // 邻接表
bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize) {
  if (numCourses == 0 || numCourses == 1) {
    return true;
  }

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

  // 确保存入度为0的节点
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
  return count == numCourses;
}

// 递归遍历
#define QUE_MAX 100000
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
}
bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize) {
  if (numCourses == 0 || numCourses == 1) {
    return true;
  }
  Gragh G = buildGragh(numCourses, prerequisites, prerequisitesSize);

  hasCycle = false;
  visited = (bool *)malloc(sizeof(bool) * numCourses);
  onPath = (bool *)malloc(sizeof(bool) * numCourses);
  for (int i = 0; i < numCourses; i++) {
    visited[i] = onPath[i] = false;
  }
  for (int i = 0; i < numCourses; i++) {
    traverse(G, i);
  }

  return !hasCycle;
}