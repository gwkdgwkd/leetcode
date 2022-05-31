/*
树可以看成是一个连通且无环的无向图。
给定往一棵n个节点(节点值1～n)的树中添加一条边后的图。
添加的边的两个顶点包含在1到n中间，且这条附加的边不属于树中已存在的边。
图的信息记录于长度为n的二维数组edges，edges[i]=[ai,bi]表示图中在ai和bi之间存在一条边。
请找出一条可以删去的边，删除后可使得剩余部分是一个有着n个节点的树。
如果有多个答案，则返回数组edges中最后出现的边。

示例1：
输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]

示例2：
输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]

提示:
n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges中无重复元素
给定的图是连通的
*/

// 剑指OfferII118多余的边

// 并查集
int count;
int* parent;
int* size;
void UF(int n) {
  count = n;
  parent = (int*)malloc(sizeof(int) * n);
  size = (int*)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}
int Find(int x) {
  while (parent[x] != x) {
    parent[x] = parent[parent[x]];
    x = parent[x];
  }
  return x;
}
void Union(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  if (rootP == rootQ) return;

  if (size[rootP] > size[rootQ]) {
    parent[rootQ] = rootP;
    size[rootP] += size[rootQ];
  } else {
    parent[rootP] = rootQ;
    size[rootQ] += size[rootP];
  }
  count--;
}
bool Connected(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  return rootP == rootQ;
}
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize,
                             int* returnSize) {
  int m = edgesSize;
  int n = edgesColSize[0];

  UF(m);
  int i;
  for (i = 0; i < m; ++i) {
    // 减1的原因：顶点的范围是[1-n]，集合的范围是[0-n)
    if (Connected(edges[i][0] - 1, edges[i][1] - 1)) {
      // 如果边已经是连接的，那么就是要返回的结果
      int* ans = (int*)malloc(sizeof(int) * 2);
      ans[0] = edges[i][0];
      ans[1] = edges[i][1];
      *returnSize = 2;
      return ans;
    } else {
      // 如果边不是连接的，那么连接两个顶点
      Union(edges[i][0] - 1, edges[i][1] - 1);
    }
  }

  *returnSize = 0;
  return NULL;
}