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