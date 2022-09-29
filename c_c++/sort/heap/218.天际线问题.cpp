/*
城市的天际线是从远处观看该城市中所有建筑物形成的轮廓的外部轮廓。
给你所有建筑物的位置和高度，请返回由这些建筑物形成的天际线。
每个建筑物的几何信息由数组buildings表示，
其中三元组buildings[i] = [lefti, righti, heighti]表示：
lefti是第i座建筑物左边缘的x坐标。
righti是第i座建筑物右边缘的x坐标。
heighti是第i座建筑物的高度。
你可以假设所有的建筑都是完美的长方形，在高度为0的绝对平坦的表面上。
天际线应该表示为由关键点组成的列表，
格式[[x1,y1],[x2,y2],...]，并按x坐标进行排序。
关键点是水平线段的左端点。
列表中最后一个点是最右侧建筑物的终点，
y坐标始终为0，仅用于标记天际线的终点。
此外，任何两个相邻建筑物之间的地面都应被视为天际线轮廓的一部分。
注意：输出天际线中不得有连续的相同高度的水平线。
例如[...[2 3],[4 5],[7 5],[11 5],[12 7]...]是不正确的答案；
三条高度为5的线应该在最终输出中合并为一个：
[...[2 3], [4 5], [12 7], ...]

示例1：
输入：buildings = [[2,9,10],[3,7,15],[5,12,12],
                  [15,20,10],[19,24,8]]
输出：[[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
解释：

示例2：
输入：buildings = [[0,2,3],[2,5,3]]
输出：[[0,3],[5,0]]

提示：
1 <= buildings.length <= 10^4
0 <= lefti < righti <= 2^31 - 1
1 <= heighti <= 2^31 - 1
buildings按lefti非递减排序
*/

// 扫描线 + 优先队列
struct pair {
  int first, second;
};
struct Heap {
  struct pair* heap;
  int heapSize;
  bool (*cmp)(struct pair*, struct pair*);
};
void init(struct Heap* obj, int n, bool (*cmp)(struct pair*, struct pair*)) {
  obj->heap = malloc(sizeof(struct pair) * (n + 1));
  obj->heapSize = 0;
  obj->cmp = cmp;
}
bool cmp1(struct pair* a, struct pair* b) { return a->second < b->second; }
void swap(struct pair* a, struct pair* b) {
  struct pair tmp = *a;
  *a = *b, *b = tmp;
}
void push(struct Heap* obj, int x, int y) {
  int p = ++(obj->heapSize), q = p >> 1;
  obj->heap[p] = (struct pair){x, y};
  while (q) {
    if (!obj->cmp(&(obj->heap[q]), &(obj->heap[p]))) {
      break;
    }
    swap(&(obj->heap[q]), &(obj->heap[p]));
    p = q, q = p >> 1;
  }
}
void pop(struct Heap* obj) {
  swap(&(obj->heap[1]), &(obj->heap[(obj->heapSize)--]));
  int p = 1, q = p << 1;
  while (q <= obj->heapSize) {
    if (q + 1 <= obj->heapSize) {
      if (obj->cmp(&(obj->heap[q]), &(obj->heap[q + 1]))) {
        q++;
      }
    }
    if (!obj->cmp(&(obj->heap[p]), &(obj->heap[q]))) {
      break;
    }
    swap(&(obj->heap[q]), &(obj->heap[p]));
    p = q, q = p << 1;
  }
}
struct pair top(struct Heap* obj) {
  return obj->heap[1];
}
bool empty(struct Heap* obj) { return obj->heapSize == 0; }
int cmp(int* a, int* b) { return *a - *b; }
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize,
                 int* returnSize, int** returnColumnSizes) {
  int n = buildingsSize;
  struct Heap* heap = malloc(sizeof(struct Heap));
  init(heap, n << 1, cmp1);

  int boundaries[n << 1];
  for (int i = 0; i < n; i++) {
    boundaries[i << 1] = buildings[i][0];
    boundaries[i << 1 | 1] = buildings[i][1];
  }
  qsort(boundaries, n << 1, sizeof(int), cmp);

  int** ret = malloc(sizeof(int*) * (n << 1));
  *returnColumnSizes = malloc(sizeof(int) * (n << 1));
  *returnSize = 0;
  int idx = 0;
  for (int i = 0; i < (n << 1); i++) {
    int boundary = boundaries[i];
    while (idx < n && buildings[idx][0] <= boundary) {
      push(heap, buildings[idx][1], buildings[idx][2]);
      idx++;
    }
    while (!empty(heap) && top(heap).first <= boundary) {
      pop(heap);
    }

    int maxn = empty(heap) ? 0 : top(heap).second;
    if ((*returnSize) == 0 || maxn != ret[(*returnSize) - 1][1]) {
      int* tmp = malloc(sizeof(int) * 2);
      tmp[0] = boundary, tmp[1] = maxn;
      (*returnColumnSizes)[*returnSize] = 2;
      ret[(*returnSize)++] = tmp;
    }
  }
  return ret;
}

class Solution {
 public:
  vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
      return a.second < b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(
        cmp);

    vector<int> boundaries;
    for (auto& building : buildings) {
      boundaries.emplace_back(building[0]);
      boundaries.emplace_back(building[1]);
    }
    sort(boundaries.begin(), boundaries.end());

    vector<vector<int>> ret;
    int n = buildings.size(), idx = 0;
    for (auto& boundary : boundaries) {
      while (idx < n && buildings[idx][0] <= boundary) {
        que.emplace(buildings[idx][1], buildings[idx][2]);
        idx++;
      }
      while (!que.empty() && que.top().first <= boundary) {
        que.pop();
      }

      int maxn = que.empty() ? 0 : que.top().second;
      if (ret.size() == 0 || maxn != ret.back()[1]) {
        ret.push_back({boundary, maxn});
      }
    }
    return ret;
  }
};