/*
节点间通路，给定有向图，设计一个算法，找出两个节点之间是否存在一条路径。

示例1：
输入：n = 3, graph = [[0, 1], [0, 2], [1, 2], [1, 2]],
     start = 0, target = 2
输出：true

示例2：
输入：n = 5, graph = [[0, 1], [0, 2], [0, 4], [0, 4], [0, 1],
     [1, 3], [1, 4], [1, 3], [2, 3], [3, 4]],
     start = 0, target = 4
输出：true

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
  vector<vector<int>> graph;
  vector<bool> isVisited;
  bool ans;

 public:
  void dfs(int start, int target) {
    if (start == target) {
      ans = true;
      return;
    }

    isVisited[start] = true;  // 标记已经来过
    for (int next : graph[start]) {
      if (!isVisited[next]) {  // 若未访问过，则继续dfs
        dfs(next, target);
      }
    }
    isVisited[start] = false;  // 还原现场
  }

  bool findWhetherExistsPath(int n, vector<vector<int>> &paths, int start,
                             int target) {
    graph.resize(n);
    isVisited.assign(n, false);
    ans = false;
    for (vector<int> &path : paths) {  // 构造图的邻接表
      graph[path[0]].emplace_back(path[1]);
    }

    dfs(start, target);

    return ans;
  }
};

class Solution {
  vector<vector<int>> graph;
  vector<bool> isVisited;

 public:
  bool dfs(int start, int target) {  // dfs返回bool
    if (start == target) {
      return true;
    }

    isVisited[start] = true;
    for (int next : graph[start]) {
      if (!isVisited[next]) {
        if (dfs(next, target)) {
          return true;
        }
      }
    }
    isVisited[start] = false;
    return false;
  }

  bool findWhetherExistsPath(int n, vector<vector<int>> &paths, int start,
                             int target) {
    graph.resize(n);
    isVisited.assign(n, false);
    for (vector<int> &path : paths) {
      graph[path[0]].emplace_back(path[1]);
    }

    return dfs(start, target);
  }
};

// BFS
class Solution {
  vector<vector<int>> graph;
  vector<bool> isVisited;

 public:
  bool bfs(int start, int target) {
    queue<int> q;
    q.push(start);
    isVisited[start] = true;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int next : graph[cur]) {
        if (!isVisited[next]) {
          if (next == target) return true;
          q.push(next);
          isVisited[next] = true;
        }
      }
    }

    return false;
  }

  bool findWhetherExistsPath(int n, vector<vector<int>> &paths, int start,
                             int target) {
    graph.resize(n);
    isVisited.assign(n, false);
    for (vector<int> &path : paths) {
      graph[path[0]].emplace_back(path[1]);  // 构造图的邻接表
    }

    return bfs(start, target);
  }
};