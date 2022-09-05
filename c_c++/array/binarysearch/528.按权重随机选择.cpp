/*
给你一个下标从0开始的正整数数组w，其中w[i]代表第i个下标的权重。
请你实现一个函数pickIndex，
它可以随机地从范围[0,w.length-1]内选出并返回一个下标。
选取下标i的概率为w[i]/sum(w)。
例如，对于w=[1,3]，挑选下标0的概率为1/(1+3)= 0.25（即，25%），
而选取下标1的概率为3/(1+3)=0.75（即，75%）。

示例1：
输入：
["Solution","pickIndex"]
[[[1]],[]]
输出：
[null,0]
解释：
Solution solution = new Solution([1]);
solution.pickIndex();
返回0，因为数组中只有一个元素，所以唯一的选择是返回下标0。

示例2：
输入：
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
输出：
[null,1,1,1,1,0]
解释：
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // 返回1，返回下标1，返回该下标概率为3/4。
solution.pickIndex(); // 返回1
solution.pickIndex(); // 返回1
solution.pickIndex(); // 返回1
solution.pickIndex(); // 返回0，返回下标0，返回该下标概率为1/4。

由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......诸若此类。

提示：
1 <= w.length <= 10^4
1 <= w[i] <= 10^5
pickIndex将被调用不超过10^4次
*/

// 剑指OfferII071按权重生成随机数

typedef struct {
  int* pre;  // 前缀和
  int preSize;
  int total;
} Solution;
Solution* solutionCreate(int* w, int wSize) {
  Solution* obj = malloc(sizeof(Solution));
  obj->pre = malloc(sizeof(int) * wSize);
  obj->preSize = wSize;
  obj->total = 0;
  for (int i = 0; i < wSize; i++) {
    obj->total += w[i];
    if (i > 0) {
      obj->pre[i] = obj->pre[i - 1] + w[i];
    } else {
      obj->pre[i] = w[i];
    }
  }
  return obj;
}
int binarySearch(Solution* obj, int x) {
  int low = 0, high = obj->preSize - 1;
  while (low < high) {
    int mid = (high - low) / 2 + low;
    if (obj->pre[mid] < x) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}
int solutionPickIndex(Solution* obj) {
  int x = rand() % obj->total + 1;
  return binarySearch(obj, x);
}
void solutionFree(Solution* obj) {
  free(obj->pre);
  free(obj);
}

class Solution {
  int total = 0;
  vector<int> pre;

 public:
  Solution(vector<int>& w) {
    pre.resize(w.size());
    for (int i = 0; i < w.size(); ++i) {
      total += w[i];
      if (i == 0) {
        pre[i] = w[i];
      } else {
        pre[i] = w[i] + pre[i - 1];
      }
    }
  }
  int pickIndex() {
    int x = rand() % total + 1;
    int left = 0;
    int right = pre.size() - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (pre[mid] < x) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }
};

// 下面的解法超时：
typedef struct {
  int* index;
  int total
} Solution;
Solution* solutionCreate(int* w, int wSize) {
  Solution* obj = malloc(sizeof(Solution));
  obj->total = 0;
  for (int i = 0; i < wSize; i++) {
    obj->total += w[i];
  }
  obj->index = malloc(sizeof(int) * obj->total);

  int j = 0;
  for (int i = 0; i < wSize; i++) {  // O(m*n)，用c++的区间赋值可以么？
    int len = j + w[i];
    for (; j < len; ++j) {
      obj->index[j] = i;
    }
  }

  return obj;
}
int solutionPickIndex(Solution* obj) {
  int x = rand() % obj->total;
  return obj->index[x];
}
void solutionFree(Solution* obj) {
  free(obj->index);
  free(obj);
}