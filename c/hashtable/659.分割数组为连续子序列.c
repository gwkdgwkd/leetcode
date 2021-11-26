struct hashTable {
  int key;
  int val;
  UT_hash_handle hh;
};

struct hashTable* find(struct hashTable** hashtable, int ikey) {
  struct hashTable* tmp;
  HASH_FIND_INT(*hashtable, &ikey, tmp);
  return tmp;
}

void insert(struct hashTable** hashtable, int ikey, int ival) {
  struct hashTable* tmp = malloc(sizeof(struct hashTable));
  tmp->key = ikey, tmp->val = ival;
  HASH_ADD_INT(*hashtable, key, tmp);
}

int query(struct hashTable** hashtable, int ikey) {
  struct hashTable* tmp;
  HASH_FIND_INT(*hashtable, &ikey, tmp);
  if (tmp == NULL) {
    return 0;
  }
  return tmp->val;
}

void modify(struct hashTable** hashtable, int ikey, int ival) {
  struct hashTable* tmp = find(hashtable, ikey);
  if (tmp == NULL) {
    insert(hashtable, ikey, ival);
  } else {
    tmp->val = ival;
  }
}

void inc(struct hashTable** hashtable, int ikey) {
  struct hashTable* tmp = find(hashtable, ikey);
  if (tmp == NULL) {
    insert(hashtable, ikey, 1);
  } else {
    tmp->val++;
  }
}

bool isPossible(int* nums, int numsSize) {
  struct hashTable* countMap = NULL;
  struct hashTable* endMap = NULL;
  for (int i = 0; i < numsSize; i++) {
    inc(&countMap, nums[i]);
  }
  for (int i = 0; i < numsSize; i++) {
    int count = query(&countMap, nums[i]);
    if (count > 0) {
      int prevEndCount = query(&endMap, nums[i] - 1);
      if (prevEndCount > 0) {
        modify(&countMap, nums[i], count - 1);
        modify(&endMap, nums[i] - 1, prevEndCount - 1);
        inc(&endMap, nums[i]);
      } else {
        int count1 = query(&countMap, nums[i] + 1);
        int count2 = query(&countMap, nums[i] + 2);
        if (count1 > 0 && count2 > 0) {
          modify(&countMap, nums[i], count - 1);
          modify(&countMap, nums[i] + 1, count1 - 1);
          modify(&countMap, nums[i] + 2, count2 - 1);
          inc(&endMap, nums[i] + 2);
        } else {
          return false;
        }
      }
    }
  }
  return true;
}