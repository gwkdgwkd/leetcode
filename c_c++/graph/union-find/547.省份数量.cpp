/*
有n个城市，其中一些彼此相连，另一些没有相连。
如果城市a与城市b直接相连，且城市b与城市c直接相连，那么城市a与城市c间接相连。
省份是一组直接或间接相连的城市，组内不含其他没有相连的城市。
nxn的矩阵isConnected，其中isConnected[i][j]=1表示第i个城市和第j个城市直接相连，
而isConnected[i][j]=0表示二者不直接相连，返回矩阵中省份的数量。

示例1：
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
输出：2

示例2：
输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
输出：3

提示：
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j]为1或0
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]
*/

// 剑指OfferII116省份数量

// Union-Find算法
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

int findCircleNum(int** isConnected, int isConnectedSize,
                  int* isConnectedColSize) {
  UF(isConnectedSize);

  for (int i = 0; i < isConnectedSize; ++i) {
    for (int j = 0; j < isConnectedColSize[i]; ++j)
      if (isConnected[i][j] == 1) {
        Union(i, j);
      }
  }
  return count;
}

class Solution {
 private:
  class UF {
   public:
    UF(int n) {
      count = n;
      size.assign(n, 1);
      parent.resize(n);
      for (int i = 0; i < n; ++i) {
        parent[i] = i;
      }
    }
    // bool IsConnected(int p, int q) { return Find(p) == Find(q); }
    int Count() { return count; }
    void Union(int p, int q) {
      int rootP = Find(p);
      int rootQ = Find(q);
      if (rootP == rootQ) {
        return;
      }
      if (rootP > rootQ) {
        parent[rootQ] = rootP;
        size[rootP] += size[rootQ];
      } else {
        parent[rootP] = rootQ;
        size[rootQ] += size[rootP];
      }
      --count;
    }

   private:
    int Find(int x) {
      while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
      }
      return x;
    }

    vector<int> parent;
    vector<int> size;
    int count;
  };

 public:
  int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    UF uf(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        if (isConnected[i][j]) {
          uf.Union(i, j);
        }
    }

    return uf.Count();
  }
};