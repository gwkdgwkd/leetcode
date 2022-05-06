/*
你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的值代表对应地点的海拔高度。
若值为0则表示水域。
由垂直、水平或对角连接的水域为池塘。
池塘的大小是指相连接的水域的个数。
编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。

示例：
输入：
[
  [0,2,1,0],
  [0,1,0,1],
  [1,1,0,1],
  [0,1,0,1]
]
输出： [1,2,4]

提示：
0 < len(land) <= 1000
0 < len(land[i]) <= 1000
*/

// 并查集
// 求池塘个数很适合用并查集，但还求池塘大小，就需要特殊处理
int count;
int *parent;
int *size;
void UF(int n) {
  count = n;
  parent = (int *)malloc(sizeof(int) * n);
  size = (int *)malloc(sizeof(int) * n);
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
int cmp(int *a, int *b) { return *a - *b; }
int *pondSizes(int **land, int landSize, int *landColSize, int *returnSize) {
  int m = landSize;
  int n = landColSize[0];

  // 向8个方向移动
  int dir[8][2] = {{0, 1},  {0, -1},  {-1, 0}, {1, 0},
                   {-1, 1}, {-1, -1}, {1, 1},  {1, -1}};

  UF(m * n);
  int num = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (land[i][j] == 0) {
        for (int k = 0; k < 8; ++k) {
          int newi = i + dir[k][0];
          int newj = j + dir[k][1];
          if (newi >= 0 && newi < m && newj >= 0 && newj < n &&
              land[newi][newj] == 0) {
            Union(i * n + j, newi * n + newj);
          }
        }
      } else {
        ++num;  // 统计不是池塘的个数
        size[i * n + j] = 0;  // 把不是池塘的size设为0，与大小为1的池塘来区分
      }
    }
  }

  // 所有联通分量个数 - 非池塘的个数 = 池塘个数
  *returnSize = count - num;
  int *res = (int *)malloc(sizeof(int) * (*returnSize));
  memset(res, 0, sizeof(int) * (*returnSize));

  int index = 0;
  for (int i = 0; i < m * n; ++i) {
    // 父节点并且size大于0，表示一个池塘，size就是池塘大小
    if (parent[i] == i && size[i] > 0) {
      res[index++] = size[i];
    }
  }

  qsort(res, *returnSize, sizeof(int), cmp);
  return res;
}

// dfs
int g_size;
int cmp(const void *_a, const void *_b) {
  int *a = (int *)_a;
  int *b = (int *)_b;
  return *a - *b;
}
void dfs(int **land, int m, int n, int i, int j) {
  if (i < 0 || j < 0 || i >= m || j >= n || land[i][j]) {
    return;
  }
  land[i][j] = 1;
  g_size++;
  dfs(land, m, n, i, j - 1);      //左
  dfs(land, m, n, i - 1, j - 1);  //左上
  dfs(land, m, n, i - 1, j);      //上
  dfs(land, m, n, i - 1, j + 1);  //右上
  dfs(land, m, n, i, j + 1);      //右
  dfs(land, m, n, i + 1, j + 1);  //右下
  dfs(land, m, n, i + 1, j);      //下
  dfs(land, m, n, i + 1, j - 1);  //左下
}
int *pondSizes(int **land, int landSize, int *landColSize, int *returnSize) {
  int size = 0;
  int m = landSize;
  int n = landColSize[0];
  int *poolSize = (int *)malloc(sizeof(int) * m * n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      g_size = 0;
      if (land[i][j] == 0) {
        dfs(land, m, n, i, j);
        poolSize[size++] = g_size;
      }
    }
  }
  *returnSize = size;
  qsort(poolSize, size, sizeof(int), cmp);
  return poolSize;
}