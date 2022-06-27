/*
存在一个无向图，图中有n个节点。
其中每个节点都有一个介于0到n - 1之间的唯一编号。
给你一个二维数组graph，其中graph[u]是一个节点数组，由节点u的邻接节点组成。
形式上，对于graph[u]中的每个v，都存在一条位于节点u和节点v之间的无向边。
该无向图同时具有以下属性：
不存在自环（graph[u]不包含u）。
不存在平行边（graph[u]不包含重复值）。
如果v在graph[u]内，那么u也应该在graph[v]内（该图是无向图）
这个图可能不是连通图，也就是说两个节点u和v之间可能不存在一条连通彼此的路径。

二分图定义：如果能将一个图的节点集合分割成两个独立的子集A和B，
并使图中的每一条边的两个节点一个来自A集合，一个来自B集合，就将这个图称为二分图。
如果图是二分图，返回true；否则，返回false。

示例1：
输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
输出：false
解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。

示例2：
输入：graph = [[1,3],[0,2],[1,3],[0,2]]
输出：true
解释：可以将节点分成两组:{0, 2}和{1, 3}。

提示：
graph.length == n
1 <= n <= 100
0 <= graph[u].length < n
0 <= graph[u][i] <= n - 1
graph[u]不会包含u
graph[u]的所有值互不相同
如果graph[u]包含v，那么graph[v]也会包含u
*/

// 对于图中的任意两个节点u和v，如果它们之间有一条边直接相连，那么u和v必须属于不同的集合。
// 如果给定的无向图连通，那么我们就可以任选一个节点开始，给它染成红色。
// 随后我们对整个图进行遍历，将该节点直接相连的所有节点染成绿色，表示这些节点不能与起始节点属于同一个集合。
// 我们再将这些绿色节点直接相连的所有节点染成红色，以此类推，直到无向图中的每个节点均被染色。
// 如果我们能够成功染色，那么红色和绿色的节点各属于一个集合，这个无向图就是一个二分图；
// 如果我们未能成功染色，即在染色的过程中，某一时刻访问到了一个已经染色的节点，
// 并且它的颜色与我们将要给它染上的颜色不相同，也就说明这个无向图不是一个二分图。
// 算法的流程如下：
// 1.我们任选一个节点开始，将其染成红色，并从该节点开始对整个无向图进行遍历；
// 2.在遍历的过程中，如果我们通过节点u遍历到了节点v（即u和v在图中有一条边直接相连），那么会有两种情况：
//   如果v未被染色，那么我们将其染成与u不同的颜色，并对v直接相连的节点进行遍历；
//   如果v被染色，并且颜色与u相同，那么说明给定的无向图不是二分图。我们可以直接退出遍历并返回false作为答案。
// 3.当遍历结束时，说明给定的无向图是二分图，返回true作为答案。
// 我们可以使用深度优先搜索或广度优先搜索对无向图进行遍历。
// 注意：题目中给定的无向图不一定保证连通，因此我们需要进行多次遍历，
//      直到每一个节点都被染色，或确定答案为false为止。
// 每次遍历开始时，我们任选一个未被染色的节点，将所有与该节点直接或间接相连的节点进行染色。

// 深度优先搜索
bool dfs(int node, int c, int* color, int** graph, int* graphColSize) {
  color[node] = c;
  int cNei = (c == 1 ? 2 : 1);
  for (int i = 0; i < graphColSize[node]; ++i) {
    int neighbor = graph[node][i];
    if (color[neighbor] == 0) {
      if (!dfs(neighbor, cNei, color, graph, graphColSize)) {
        return false;
      }
    } else if (color[neighbor] != cNei) {
      return false;
    }
  }
  return true;
}
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
  int* color = (int*)malloc(sizeof(int) * graphSize);
  memset(color, 0, sizeof(int) * graphSize);
  for (int i = 0; i < graphSize; ++i) {
    if (color[i] == 0) {
      if (!dfs(i, 1, color, graph, graphColSize)) {
        free(color);
        return false;
      }
    }
  }
  free(color);
  return true;
}

// 广度优先搜索
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
  int* color = (int*)malloc(sizeof(int) * graphSize);
  memset(color, 0, sizeof(int) * graphSize);

  int* q = (int*)malloc(sizeof(int) * graphSize);
  for (int i = 0; i < graphSize; ++i) {
    if (color[i] == 0) {
      int l = 0, r = 0;
      q[0] = i;
      color[i] = 1;
      while (l <= r) {
        int node = q[l++];
        int cNei = (color[node] == 1 ? 2 : 1);
        for (int j = 0; j < graphColSize[node]; ++j) {
          int neighbor = graph[node][j];
          if (color[neighbor] == 0) {
            q[++r] = neighbor;
            color[neighbor] = cNei;
          } else if (color[neighbor] != cNei) {
            free(color);
            free(q);
            return false;
          }
        }
      }
    }
  }
  free(color);
  free(q);
  return true;
}

class Solution {
 public:
  bool dfs(vector<vector<int>>& graph, vector<int>& color, int c, int i) {
    color[i] = c;
    int cNei = (c == 1 ? 2 : 1);
    for (int j = 0; j < graph[i].size(); ++j) {
      int nei = graph[i][j];
      if (color[nei] == 0) {
        if (!dfs(graph, color, cNei, nei)) {
          return false;
        }
      } else if (color[nei] != cNei) {
        return false;
      }
    }
    return true;
  }
  bool isBipartite(vector<vector<int>>& graph) {
    int m = graph.size();
    vector<int> color(m, 0);

    for (int i = 0; i < m; ++i) {
      if (color[i] > 0) {
        continue;
      }
      if (!dfs(graph, color, 1, i)) {
        return false;
      }
    }

    return true;
  }
};