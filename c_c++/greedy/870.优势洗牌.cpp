/*
给定两个大小相等的数组A和B，A相对于B的优势可以用满足A[i]>B[i]的索引i的数目来描述。
返回A的任意排列，使其相对于B的优势最大化。

示例1：
输入：A = [2,7,11,15], B = [1,10,4,11]
输出：[2,11,7,15]

示例2：
输入：A = [12,24,8,32], B = [13,25,32,11]
输出：[24,32,8,12]

提示：
1 <= A.length = B.length <= 10000
0 <= A[i] <= 10^9
0 <= B[i] <= 10^9
*/

// 贪心 + 快排
struct side {  // 这个结构体的目的是用来存B数组的值和索引
  int val;
  int tige;
};
int cmp(const void *a, const void *b) {  // 这个是结构体的比较器
  struct side *c, *d;
  c = (struct side *)a;
  d = (struct side *)b;
  return c->val - d->val;
}
// A数组的比较器
int cmp1(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int *advantageCount(int *A, int ASize, int *B, int BSize, int *returnSize) {
  int i, l = 0, r = BSize - 1;  // r作用是记录排好序B数组最大的值的位置
  // 是用来返回的数组
  int *list = (int *)malloc(sizeof(int) * (ASize + 2));
  struct side *head = (struct side *)malloc(sizeof(struct side) * (BSize + 2));

  for (i = 0; i < BSize; i++) {
    // 把B数组的值赋给结构体
    head[i].val = B[i];
    head[i].tige = i;
  }
  qsort(A, ASize, sizeof(int), cmp1);  // 进行排列
  qsort(head, BSize, sizeof(struct side), cmp);
  for (i = 0; i < ASize; i++) {
    if (A[i] > head[l].val) {
      // 如果A数组的值大于B数组的值则把A[i]的值赋给list数组中的B数组的索引
      list[head[l].tige] = A[i];
      l++;
    } else {
      // 如果是小于等于则把A[i]的值放在list数组中B数组最大的索引位置
      list[head[r].tige] = A[i];
      r--;
    }
  }
  *returnSize = ASize;
  return list;
}

class Solution {
 public:
  vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2) {
    sort(nums1.begin(), nums1.end(), greater<int>());
    vector<pair<int, int>> pairs;

    int n = nums2.size();
    for (int i = 0; i < n; i++) {
      pairs.push_back({i, nums2[i]});
    }
    sort(pairs.begin(), pairs.end(),
         [](auto x, auto y) { return x.second > y.second; });

    int curr = 0;
    int min = n - 1;
    vector<int> result(nums1.size(), 0);
    for (int i = 0; i < n; ++i) {
      int ide = pairs[i].first;
      int val = pairs[i].second;
      if (nums1[curr] > val) {
        result[ide] = nums1[curr];
        curr++;
      } else {
        result[ide] = nums1[min];
        min--;
      }
    }

    return result;
  }
};