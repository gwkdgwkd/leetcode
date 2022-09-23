/*
给你两个整数数组nums1和nums2，请你以数组形式返回两数组的交集。
返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致，
如果出现次数不一致，则考虑取较小值，可以不考虑输出结果的顺序。

示例1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]

示例2:
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]

提示：
1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000

进阶：
如果给定的数组已经排好序呢？你将如何优化你的算法？
如果nums1的大小比nums2小，哪种方法更优？
如果nums2的元素存储在磁盘上，内存是有限的，
并且你不能一次加载所有的元素到内存中，你该怎么办？
*/

// 哈希表
struct hashTable {
  int key;
  int value;
  int nums;
  UT_hash_handle hh;
};
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size,
               int* returnSize) {
  struct hashTable* set = NULL;
  for (int i = 0; i < nums1Size; i++) {
    struct hashTable* tmp;
    HASH_FIND_INT(set, nums1 + i, tmp);
    if (tmp == NULL) {
      tmp = (struct hashTable*)calloc(1, sizeof(struct hashTable));
      tmp->key = nums1[i];
      tmp->value = nums1[i];
      tmp->nums = 1;
      HASH_ADD_INT(set, key, tmp);
    } else if (tmp != NULL && tmp->value == nums1[i]) {
      tmp->nums += 1;
    }
  }
  *returnSize = 0;

  int* res = (int*)calloc(10000, sizeof(int));
  for (int i = 0; i < nums2Size; i++) {
    struct hashTable* tmp;
    HASH_FIND_INT(set, nums2 + i, tmp);
    if (tmp != NULL && tmp->value == nums2[i] && tmp->nums != 0) {
      tmp->nums -= 1;
      res[(*returnSize)++] = nums2[i];
    }
  }
  return res;
}

// 排序+双指针
int cmp(const void* _a, const void* _b) {
  int *a = _a, *b = (int*)_b;
  return *a == *b ? 0 : *a > *b ? 1 : -1;
}
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size,
               int* returnSize) {
  qsort(nums1, nums1Size, sizeof(int), cmp);
  qsort(nums2, nums2Size, sizeof(int), cmp);
  *returnSize = 0;
  int* intersection = (int*)malloc(sizeof(int) * fmin(nums1Size, nums2Size));
  int index1 = 0, index2 = 0;
  while (index1 < nums1Size && index2 < nums2Size) {
    if (nums1[index1] < nums2[index2]) {
      index1++;
    } else if (nums1[index1] > nums2[index2]) {
      index2++;
    } else {
      intersection[(*returnSize)++] = nums1[index1];
      index1++;
      index2++;
    }
  }
  return intersection;
}

class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> hash;
    for (auto& i : nums1) {
      hash[i]++;
    }

    vector<int> res;
    for (auto& i : nums2) {
      if (hash[i]-- > 0) {
        res.emplace_back(i);
      }
    }
    return res;
  }
};