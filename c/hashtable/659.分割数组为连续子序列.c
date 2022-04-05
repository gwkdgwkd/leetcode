/*
给你一个按升序排序的整数数组num（可能包含重复数字），
请你将它们分割成一个或多个长度至少为3的子序列，其中每个子序列都由连续整数组成。
如果可以完成上述分割，则返回true；否则，返回false。

示例1：
输入: [1,2,3,3,4,5]
输出: True
解释:
你可以分割出这样两个连续子序列:
1, 2, 3
3, 4, 5

示例2：
输入: [1,2,3,3,4,4,5,5]
输出: True
解释:
你可以分割出这样两个连续子序列:
1, 2, 3, 4, 5
3, 4, 5

示例3：
输入: [1,2,3,4,4,5]
输出: False

提示：1 <= nums.length <= 10000
*/

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