/*
请判断原始的序列org是否可以从序列集seqs中唯一地重建。
序列org是1到n整数的排列，其中1 ≤ n ≤ 10^4。
重建是指在序列集seqs中构建最短的公共超序列，
即seqs中的任意序列都是该最短序列的子序列。

示例1：
输入：org = [1,2,3], seqs = [[1,2],[1,3]]
输出：false
解释：[1,2,3]不是可以被重建的唯一的序列，
     因为[1,3,2]也是一个合法的序列。

示例2：
输入：org = [1,2,3]， seqs = [[1,2]]
输出：false
解释：可以重建的序列只有[1,2]。

示例3：
输入：org = [1,2,3]， seqs = [[1,2],[1,3],[2,3]]
输出：true
解释：序列[1,2]，[1,3]和[2,3]可以被唯一地重建为原始的序列[1,2,3]。

示例4：
输入：org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
输出：true

提示：
1 <= n <= 10^4
org是数字1到n的一个排列
1 <= segs[i].length <= 10^5
seqs[i][j]是32位有符号整数

注意：本题与444题相同
*/

// 构建一个map记录org中每个值对应的下标, 记录在map[i][0]
// map[i][1]记录seq中某个值及其前值在org中的最小间隔, 举例如下：
// org = [1,2,3], seqs = [[1,2],[1,3]]
// 则map[1][1]=0,
// map[2][1]=map[2][0]-map[1][0]=1,
// map[3][0]=map[3][0]，
// map[1][0] = 2若有map[i][1] != 1 && i != org[0], 则不满足条件
// 若有seq中某个值大于orgSize, 也不满足条件
#define MIN(a, b) (a < b ? a : b)
bool sequenceReconstruction(int *org, int orgSize, int **seqs, int seqsSize,
                            int *seqsColSize) {
  if (orgSize == 0 || seqsSize == 0) return false;
  int map[orgSize + 1][2];  // 比orgSize多一位，免除记录时需要做-1处理
  memset(map, 0, 2 * (orgSize + 1) * sizeof(int));
  int tmp = 0;

  // 将org中每个值的位置记录进map
  for (int i = 0; i < orgSize; i++) map[org[i]][0] = i;

  // 将seqs中每个值及其在所有seqs[n]中的前驱值中在org中的位置差最小的一个记录入map
  // 解释：在seqs中，每个值可能有多个前驱值，
  // 选择其中在orgs中最靠后的一个，记录与该前驱值的位置差，可能为负数
  for (int i = 0; i < seqsSize; i++) {
    if (seqs[i][0] > orgSize) return false;
    for (int j = 1; j < seqsColSize[i]; j++) {
      // seqs[i][j]必须在1 - orgSize的范围内
      if (seqs[i][j] > orgSize || seqs[i][j] < 1) return false;
      tmp = map[seqs[i][j]][0] - map[seqs[i][j - 1]][0];
      if (tmp == 0) return false;
      map[seqs[i][j]][1] =
          map[seqs[i][j]][1] == 0 ? tmp : MIN(map[seqs[i][j]][1], tmp);
    }
  }

  // org[0]不应有前驱值
  if (map[org[0]][1] != 0) return false;

  // 除org[0]外每个值都应当有符合org中排序的前驱值，也即map[i][1] == 1
  for (int i = 1; i <= orgSize; i++) {
    if (map[i][1] != 1 && i != org[0]) return false;
  }

  return true;
}

// 拓扑排序
typedef struct Node {
  int val;
  struct Node *next;
} * GraghNode;  // 节点
typedef struct gNode {
  int size;
  GraghNode *Lists;  // 保存每个节点的邻接节点数组
} * Gragh;           // 邻接表
bool sequenceReconstruction(int *org, int orgSize, int **seqs, int seqsSize,
                            int *seqsColSize) {
  if (orgSize == 1 && seqsSize == 0) return false;

  // 构建邻接表
  Gragh G = (Gragh)malloc(sizeof(struct gNode));
  G->size = orgSize;
  G->Lists = (GraghNode *)malloc(sizeof(GraghNode) * G->size);
  for (int i = 0; i < G->size; i++) {
    G->Lists[i] = (GraghNode)malloc(sizeof(struct Node));
    G->Lists[i]->next = NULL;
  }

  // 初始化入度数组并赋值
  int *Indegree = (int *)malloc(sizeof(int) * orgSize);
  memset(Indegree, 0, sizeof(int) * orgSize);
  for (int i = 0; i < seqsSize; i++) {
    // 异常情况
    if (seqsColSize[i] == 1 && (seqs[i][0] < 1 || seqs[i][0] > orgSize)) {
      return false;
    }
    for (int j = 0; j < seqsColSize[i] - 1; ++j) {  // 把j和j+1的关系保存到图中
      // 异常情况
      if (seqs[i][j] < 1 || seqs[i][j] > orgSize || seqs[i][j + 1] < 1 ||
          seqs[i][j + 1] > orgSize) {
        return false;
      }
      Indegree[seqs[i][j + 1] - 1]++;
      GraghNode node = (GraghNode)malloc(sizeof(struct Node));
      node->val = seqs[i][j + 1] - 1;
      node->next = G->Lists[seqs[i][j] - 1]->next;
      G->Lists[seqs[i][j] - 1]->next = node;
    }
  }

  int que[orgSize];
  int head = 0, tail = 0;
  int index = 0;
  for (int i = 0; i < orgSize; i++) {
    // 入度为0并且值与org中的第一个元素相等则入队列
    if (Indegree[i] == 0 && org[index++] == i + 1) {
      que[tail++] = i;
    }
  }

  // 保存拓扑排序的数组
  int *topSortNumber = (int *)malloc(sizeof(int) * orgSize);
  int count = 0;

  // 入度为0的节点出队并将相邻节点入度减一，若减为0则入队
  while (tail == head + 1) {  // 队列中同时只能有一个入度为0的结点
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

  // 若所有节点最终都能入队并出队，则说明有向图无环，能够重建序列
  return count == orgSize;
}

class Solution {
 public:
  bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
    if (seqs.size() == 0) return false;

    int n = org.size();

    vector<vector<int>> edges(n);
    vector<int> indeg(n, 0);

    int i, j, u, v;
    for (auto &seq : seqs) {
      if (seq[0] - 1 >= n || seq[0] - 1 < 0) return false;

      for (i = 0; i < seq.size() - 1; ++i) {
        u = seq[i] - 1;
        v = seq[i + 1] - 1;
        if (u >= n || v >= n || u < 0 || v < 0) return false;
        edges[u].push_back(v);
        ++indeg[v];
      }
    }

    queue<int> q;
    for (i = 0; i < n; ++i) {
      if (!indeg[i]) {
        q.push(i);
      }
    }

    vector<int> ans;
    while (!q.empty()) {
      if (q.size() != 1) return false;
      u = q.front();
      q.pop();
      ans.push_back(u + 1);

      for (i = 0; i < edges[u].size(); ++i) {
        v = edges[u][i];
        if (--indeg[v] == 0) {
          q.push(v);
        }
      }
    }

    return ans == org;
  }
};
