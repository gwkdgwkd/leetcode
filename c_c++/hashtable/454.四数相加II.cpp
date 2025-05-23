/*
给你四个整数数组nums1、nums2、nums3和nums4，数组长度都是n，
请你计算有多少个元组(i,j,k,l)能满足：
0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

示例1：
输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
输出：2
解释：
两个元组如下：
(0, 0, 0, 1)->nums1[0]+nums2[0]+nums3[0]+nums4[1] =
              1 + (-2) + (-1) + 2 = 0
(1, 1, 0, 0)->nums1[1]+nums2[1]+nums3[0]+nums4[0] =
              2 + (-1) + (-1) + 0 = 0

示例2：
输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
输出：1

提示：
n == nums1.length
n == nums2.length
n == nums3.length
n == nums4.length
1 <= n <= 200
-2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28
*/

// 哈希表
#define TB_LEN 256
typedef struct table_node {
  int val;
  int count;
  struct table_node *next;
} TABLE_NODE;
void my_hash_insert(TABLE_NODE *tb[], int val) {
  if (NULL == tb[abs(val % TB_LEN)]) {
    tb[abs(val % TB_LEN)] = (TABLE_NODE *)malloc(sizeof(TABLE_NODE));
    tb[abs(val % TB_LEN)]->val = val;
    tb[abs(val % TB_LEN)]->count = 1;
    tb[abs(val % TB_LEN)]->next = NULL;
  } else {
    TABLE_NODE *p = tb[abs(val % TB_LEN)];
    if (p->val == val) {
      p->count++;
      return;
    }
    while (p->next) {
      p = p->next;
      if (p->val == val) {
        p->count++;
        return;
      }
    }
    p->next = (TABLE_NODE *)malloc(sizeof(TABLE_NODE));
    p->next->val = val;
    p->next->count = 1;
    p->next->next = NULL;
  }
}
int my_hash_find(TABLE_NODE *tb[], int val) {
  TABLE_NODE *p = tb[abs(val % TB_LEN)];
  while (p) {
    if (p->val == val) {
      return p->count;
    }
    p = p->next;
  }
  return 0;
}
int fourSumCount(int *nums1, int nums1Size, int *nums2, int nums2Size,
                 int *nums3, int nums3Size, int *nums4, int nums4Size) {
  int i, j;
  int count = 0;
  TABLE_NODE *hash_table[TB_LEN] = {0};

  for (i = 0; i < nums1Size; i++) {
    for (j = 0; j < nums2Size; j++) {
      my_hash_insert(hash_table, nums1[i] + nums2[j]);
    }
  }
  for (i = 0; i < nums3Size; i++) {
    for (j = 0; j < nums4Size; j++) {
      count += my_hash_find(hash_table, -(nums3[i] + nums4[j]));
    }
  }
  return count;
}

// uthash
struct hashTable {
  int key;
  int val;
  UT_hash_handle hh;
};
int fourSumCount(int *A, int ASize, int *B, int BSize, int *C, int CSize,
                 int *D, int DSize) {
  struct hashTable *hashtable = NULL;
  for (int i = 0; i < ASize; ++i) {
    for (int j = 0; j < BSize; ++j) {
      int ikey = A[i] + B[j];
      struct hashTable *hash;
      HASH_FIND_INT(hashtable, &ikey, hash);
      if (hash == NULL) {
        struct hashTable *hash = malloc(sizeof(struct hashTable));
        hash->key = ikey;
        hash->val = 1;
        HASH_ADD_INT(hashtable, key, hash);
      } else {
        hash->val++;
      }
    }
  }
  int count = 0;
  for (int i = 0; i < CSize; ++i) {
    for (int j = 0; j < DSize; ++j) {
      int ikey = -C[i] - D[j];
      struct hashTable *hash;
      HASH_FIND_INT(hashtable, &ikey, hash);
      if (hash != NULL) {
        count += hash->val;
      }
    }
  }
  return count;
}

class Solution {
 public:
  int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                   vector<int> &nums4) {
    unordered_map<int, int> hash;
    for (int i = 0; i < nums1.size(); ++i) {
      for (int j = 0; j < nums2.size(); ++j) {
        hash[nums1[i] + nums2[j]]++;
      }
    }

    int count = 0;
    for (int i = 0; i < nums3.size(); ++i) {
      for (int j = 0; j < nums4.size(); ++j) {
        count += hash[(nums3[i] + nums4[j]) * -1];
      }
    }
    return count;
  }
};

class Solution {
 public:
  int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C,
                   vector<int> &D) {
    unordered_map<int, int> countAB;
    for (int u : A) {
      for (int v : B) {
        ++countAB[u + v];
      }
    }
    int ans = 0;
    for (int u : C) {
      for (int v : D) {
        if (countAB.count(-u - v)) {
          ans += countAB[-u - v];
        }
      }
    }
    return ans;
  }
};