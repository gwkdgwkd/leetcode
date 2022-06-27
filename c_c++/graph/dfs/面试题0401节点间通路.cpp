/*
节点间通路。给定有向图，设计一个算法，找出两个节点之间是否存在一条路径。

示例1:
输入：n = 3, graph = [[0, 1], [0, 2], [1, 2], [1, 2]],
start = 0, target = 2
输出：true

示例2:
输入：n = 5, graph = [[0, 1], [0, 2], [0, 4], [0, 4], [0, 1],
[1, 3], [1, 4], [1, 3], [2, 3], [3, 4]],
start = 0, target = 4
输出 true

提示：
节点数量n在[0, 1e5]范围内。
节点编号大于等于0小于n。
图中可能存在自环和平行边。
*/

// dfs + 邻接表
#define MAXN 10000
typedef struct _ListNode {
  int neigh;
  struct _ListNode *next;
} ListNode;

bool dfs(ListNode *AdjList, int *book, int n, int start, int target) {
  if (start == target) {
    return true;
  }
  book[start] = true;
  ListNode *p = AdjList[start].next;
  while (p != NULL) {
    if (book[p->neigh] != true && dfs(AdjList, book, n, p->neigh, target)) {
      return true;
    }
    p = p->next;
  }
  return false;
}

bool findWhetherExistsPath(int n, int **graph, int graphSize, int *graphColSize,
                           int start, int target) {
  bool flag;
  ListNode *p;

  //构造邻接表
  ListNode *AdjList = (ListNode *)malloc(sizeof(ListNode) * n);
  ListNode **LastNeigh = (ListNode **)malloc(sizeof(ListNode *) * n);
  int *book = (int *)malloc(sizeof(int) * n);
  memset(AdjList, 0, sizeof(ListNode) * n);
  memset(LastNeigh, 0, sizeof(ListNode *) * n);
  memset(book, 0, sizeof(int) * n);
  for (int i = 0; i < graphSize; i++) {
    p = (ListNode *)malloc(sizeof(ListNode));
    p->neigh = graph[i][1];
    p->next = NULL;
    if (LastNeigh[graph[i][0]] == NULL) {
      LastNeigh[graph[i][0]] = p;
      AdjList[graph[i][0]].next = p;
      continue;
    }
    LastNeigh[graph[i][0]]->next = p;
    LastNeigh[graph[i][0]] = p;
  }

  // 以start为起点dfs，直到搜索到target;
  flag = dfs(AdjList, book, n, start, target);
  for (int i = 0; i < n; i++) {
    while (AdjList[i].next != NULL) {
      p = AdjList[i].next;
      AdjList[i].next = p->next;
      free(p);
    }
  }
  free(AdjList);
  free(LastNeigh);
  free(book);
  return flag;
}

// DFS
class Solution {
 public:
  void dfs(vector<unordered_set<int>> &hash, vector<bool> &isVisited, int start,
           int target, bool &flag) {
    if (start == target) {
      flag = true;
    }

    isVisited[start] = true;  // 标记已经来过
    for (int next : hash[start]) {
      if (!isVisited[next]) {  // 若未访问过，则继续dfs
        dfs(hash, isVisited, next, target, flag);
      }
    }
    isVisited[start] = false;  // 还原现场
  }

  bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start,
                             int target) {
    vector<unordered_set<int>> hash(n);
    vector<bool> isVisited(n, false);
    bool flag = false;

    for (vector<int> &path : graph) {
      hash[path[0]].insert(path[1]);  // 构造图
    }

    dfs(hash, isVisited, start, target, flag);

    return flag;
  }
};

// BFS
class Solution {
 public:
  bool bfs(vector<unordered_set<int>> &hash, vector<bool> &isVisited, int start,
           int target) {
    queue<int> q;
    q.push(start);
    isVisited[start] = true;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int next : hash[cur]) {
        if (!isVisited[next]) {
          if (next == target) return true;
          q.push(next);
          isVisited[next] = true;
        }
      }
    }

    return false;
  }

  bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start,
                             int target) {
    vector<unordered_set<int>> hash(n);
    vector<bool> isVisited(n, false);

    for (vector<int> &path : graph) {
      hash[path[0]].insert(path[1]);
    }

    return bfs(hash, isVisited, start, target);
  }
};