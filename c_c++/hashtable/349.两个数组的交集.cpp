/*
给定两个数组nums1和nums2，返回它们的交集。
输出结果中的每个元素一定是唯一的，可以不考虑输出结果的顺序。

示例1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]

示例2：
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9]也是可通过的

提示：
1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
*/

// 哈希表
// 使用数组来做哈希的题目，是因为题目都限制了数值的大小。
// 而这道题目没有限制数值的大小，就无法使用数组来做哈希表了。
// 而且如果哈希值比较少、特别分散、跨度非常大，
// 使用数组就造成空间的极大浪费。
#include "uthash.h"
struct unordered_set {
  int key;
  UT_hash_handle hh;
};
struct unordered_set* find(struct unordered_set** hashtable, int ikey) {
  struct unordered_set* tmp;
  HASH_FIND_INT(*hashtable, &ikey, tmp);
  return tmp;
}
void insert(struct unordered_set** hashtable, int ikey) {
  struct unordered_set* tmp = find(hashtable, ikey);
  if (tmp != NULL) return;
  tmp = malloc(sizeof(struct unordered_set));
  tmp->key = ikey;
  HASH_ADD_INT(*hashtable, key, tmp);
}
int* getIntersection(struct unordered_set** set1, struct unordered_set** set2,
                     int* returnSize) {
  if (HASH_COUNT(*set1) > HASH_COUNT(*set2)) {
    return getIntersection(set2, set1, returnSize);
  }
  int* intersection =
      malloc(sizeof(int) * (HASH_COUNT(*set1) + HASH_COUNT(*set2)));
  struct unordered_set *s, *tmp;
  HASH_ITER(hh, *set1, s, tmp) {
    if (find(set2, s->key)) {
      intersection[(*returnSize)++] = s->key;
    }
  }
  return intersection;
}
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size,
                  int* returnSize) {
  *returnSize = 0;
  struct unordered_set *set1 = NULL, *set2 = NULL;
  for (int i = 0; i < nums1Size; i++) {
    insert(&set1, nums1[i]);
  }
  for (int i = 0; i < nums2Size; i++) {
    insert(&set2, nums2[i]);
  }

  return getIntersection(&set1, &set2, returnSize);
}

// 排序+双指针
int cmp(void* a, void* b) { return *(int*)a - *(int*)b; }
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size,
                  int* returnSize) {
  qsort(nums1, nums1Size, sizeof(int), cmp);
  qsort(nums2, nums2Size, sizeof(int), cmp);
  *returnSize = 0;
  int index1 = 0, index2 = 0;
  int* intersection = malloc(sizeof(int) * (nums1Size + nums2Size));
  while (index1 < nums1Size && index2 < nums2Size) {
    int num1 = nums1[index1], num2 = nums2[index2];
    if (num1 == num2) {
      if (!(*returnSize) || num1 != intersection[(*returnSize) - 1]) {
        intersection[(*returnSize)++] = num1;
      }
      index1++;
      index2++;
    } else if (num1 < num2) {
      index1++;
    } else {
      index2++;
    }
  }
  return intersection;
}

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> hash;
    for (auto& i : nums1) {
      hash.insert(i);
    }

    vector<int> res;
    for (auto& i : nums2) {
      if (hash.count(i)) {
        hash.erase(i);
        res.emplace_back(i);
      }
    }
    return res;
  }
};