/*
给定两个以升序排列的整数数组nums1和nums2, 以及一个整数k。
定义一对值(u,v)，其中第一个元素来自nums1，第二个元素来自nums2。
请找到和最小的k个数对(u1,v1), (u2,v2) ... (uk,vk)。

示例1：
输入：nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出：[1,2],[1,4],[1,6]
解释：返回序列中的前3对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

示例2：
输入：nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出：[1,1],[1,1]
解释：返回序列中的前2对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

示例3：
输入：nums1 = [1,2], nums2 = [3], k = 3
输出：[1,3],[2,3]
解释：也可能序列中所有的数对都被返回：[1,3],[2,3]

提示：
1 <= nums1.length, nums2.length <= 10^5
-10^9 <= nums1[i], nums2[i] <= 10^9
nums1和nums2均为升序排列
1 <= k <= 1000
*/

// 剑指OfferII061和最小的k个数对

// 小顶堆 + 暴力，超时
typedef struct node {
  int x;
  int y;
} Node;
void HeapAdjust(Node *heap, int top, int size) {
  Node temp = heap[top];
  for (int i = top * 2 + 1; i < size; i = 2 * i + 1) {
    if (i + 1 < size && heap[i].x + heap[i].y > heap[i + 1].x + heap[i + 1].y) {
      ++i;
    }
    if (temp.x + temp.y < heap[i].x + heap[i].y) {
      break;
    }
    heap[top] = heap[i];
    top = i;
  }
  heap[top] = temp;
}
int **kSmallestPairs(int *nums1, int nums1Size, int *nums2, int nums2Size,
                     int k, int *returnSize, int **returnColumnSizes) {
  int size = nums1Size * nums2Size;
  Node *all = (Node *)malloc(sizeof(Node) * size);
  int idx = 0;
  for (int i = 0; i < nums1Size; ++i) {
    for (int j = 0; j < nums2Size; ++j) {
      all[idx].x = nums1[i];
      all[idx].y = nums2[j];
      ++idx;
    }
  }

  for (int i = size / 2 - 1; i >= 0; --i) {
    HeapAdjust(all, i, size);
  }

  int **res = (int *)malloc(sizeof(int *) * k);
  *returnSize = 0;
  *returnColumnSizes = (int *)malloc(sizeof(int) * k);
  for (int i = idx - 1; i >= 0 && i >= idx - k; --i) {
    res[(*returnSize)] = (int *)malloc(sizeof(int) * 2);
    (*returnColumnSizes)[(*returnSize)] = 2;
    res[(*returnSize)][0] = all[0].x;
    res[(*returnSize)][1] = all[0].y;
    (*returnSize)++;
    all[0] = all[i];

    HeapAdjust(all, 0, i);
  }
  return res;
}

class Solution {
 public:
  vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
                                     int k) {
    auto cmp = [&nums1, &nums2](const pair<int, int> &a,
                                const pair<int, int> &b) {
      return nums1[a.first] + nums2[a.second] >
             nums1[b.first] + nums2[b.second];
    };

    int m = nums1.size();
    int n = nums2.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
        cmp);
    for (int i = 0; i < min(k, m); i++) {
      pq.emplace(i, 0);
    }
    vector<vector<int>> ans;
    while (k-- > 0 && !pq.empty()) {
      auto [x, y] = pq.top();
      pq.pop();
      ans.emplace_back(initializer_list<int>{nums1[x], nums2[y]});
      if (y + 1 < n) {
        pq.emplace(x, y + 1);
      }
    }

    return ans;
  }
};

// 二分查找，官方题解，比堆效率高
#define MIN(a, b) ((a) > (b) ? (b) : (a))
int **kSmallestPairs(int *nums1, int nums1Size, int *nums2, int nums2Size,
                     int k, int *returnSize, int **returnColumnSizes) {
  if (nums1Size == 0 || nums2Size == 0 || k <= 0) {
    *returnSize = 0;
    return NULL;
  }

  // 二分查找第k小的数对和的大小
  int left = nums1[0] + nums2[0];
  int right = nums1[nums1Size - 1] + nums2[nums2Size - 1];
  int pairSum = right;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    long long cnt = 0;
    int start = 0;
    int end = nums2Size - 1;
    while (start < nums1Size && end >= 0) {
      if (nums1[start] + nums2[end] > mid) {
        end--;
      } else {
        cnt += end + 1;
        start++;
      }
    }
    if (cnt < k) {
      left = mid + 1;
    } else {
      pairSum = mid;
      right = mid - 1;
    }
  }

  int **ans = (int **)malloc(sizeof(int *) * k);
  *returnColumnSizes = (int *)malloc(sizeof(int) * k);
  int currSize = 0;
  int pos = nums2Size - 1;
  // 找到小于目标值pairSum的数对
  for (int i = 0; i < nums1Size; i++) {
    while (pos >= 0 && nums1[i] + nums2[pos] >= pairSum) {
      pos--;
    }
    for (int j = 0; j <= pos && k > 0; j++, k--) {
      ans[currSize] = (int *)malloc(sizeof(int) * 2);
      ans[currSize][0] = nums1[i];
      ans[currSize][1] = nums2[j];
      (*returnColumnSizes)[currSize] = 2;
      currSize++;
    }
  }

  // 找到等于目标值pairSum的数对
  pos = nums2Size - 1;
  for (int i = 0; i < nums1Size && k > 0; i++) {
    int start1 = i;
    while (i < nums1Size - 1 && nums1[i] == nums1[i + 1]) {
      i++;
    }
    while (pos >= 0 && nums1[i] + nums2[pos] > pairSum) {
      pos--;
    }
    int start2 = pos;
    while (pos > 0 && nums2[pos] == nums2[pos - 1]) {
      pos--;
    }
    if (nums1[i] + nums2[pos] != pairSum) {
      continue;
    }
    int count = (int)MIN(k, (long)(i - start1 + 1) * (start2 - pos + 1));
    for (int j = 0; j < count && k > 0; j++, k--) {
      ans[currSize] = (int *)malloc(sizeof(int) * 2);
      ans[currSize][0] = nums1[i];
      ans[currSize][1] = nums2[pos];
      (*returnColumnSizes)[currSize] = 2;
      currSize++;
    }
  }
  *returnSize = currSize;
  return ans;
}