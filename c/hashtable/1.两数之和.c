// 哈希表
struct hashTable {
  int key;
  int val;
  UT_hash_handle hh;
};
struct hashTable* hashtable;
struct hashTable* find(int ikey) {
  struct hashTable* tmp;
  HASH_FIND_INT(hashtable, &ikey, tmp);
  return tmp;
}
void insert(int ikey, int ival) {
  struct hashTable* it = find(ikey);
  if (it == NULL) {
    struct hashTable* tmp = malloc(sizeof(struct hashTable));
    tmp->key = ikey, tmp->val = ival;
    HASH_ADD_INT(hashtable, key, tmp);
  } else {
    it->val = ival;
  }
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  hashtable = NULL;
  for (int i = 0; i < numsSize; i++) {
    struct hashTable* it = find(target - nums[i]);
    if (it != NULL) {
      int* ret = malloc(sizeof(int) * 2);
      ret[0] = it->val, ret[1] = i;
      *returnSize = 2;
      return ret;
    }
    insert(nums[i], i);
  }
  *returnSize = 0;
  return NULL;
}

// 暴力法
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int i, j;

  for (i = 0; i < numsSize - 1; i++) {
    for (j = i + 1; j < numsSize; j++) {
      if (nums[i] + nums[j] == target) {
        int* p = (int*)malloc(sizeof(int) * 2);
        p[0] = i;
        p[1] = j;
        *returnSize = 2;
        return p;
      }
    }
  }
  return NULL;
}
