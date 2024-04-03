/*
假设你有两个数组，一个长一个短，短的元素均不相同。
找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。
返回最短子数组的左端点和右端点，如有多个满足条件的子数组，
返回左端点最小的一个，若不存在，返回空数组。

示例1：
输入：
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
输出：[7,10]

示例2：
输入：
big = [1,2,3]
small = [4]
输出：[]

提示：
big.length <= 100000
1 <= small.length <= 100000
*/

// 哈希 + 滑动窗口
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
int* shortestSeq(int* big, int bigSize, int* small, int smallSize,
                 int* returnSize) {
  hashtable = NULL;
  for (int i = 0; i < smallSize; ++i) {
    insert(small[i], 0);
  }
  int len = 0;

  int left = 0;
  int right = 0;
  int minlen = INT_MAX;
  int start = 0;
  while (right < bigSize) {
    struct hashTable* it1 = find(big[right++]);
    if (it1 != NULL) {
      if (it1->val++ == 0) {
        ++len;
      }
    }
    while (len == smallSize) {
      if (right - left < minlen) {
        start = left;
        minlen = right - left;
      }
      struct hashTable* it2 = find(big[left++]);
      if (it2 != NULL) {
        if (it2->val-- == 1) {
          --len;
        }
      }
    }
  }

  if (minlen == INT_MAX) {
    *returnSize = 0;
    return NULL;
  }

  *returnSize = 2;
  int* res = (int*)malloc(sizeof(int) * 2);
  res[0] = start;
  res[1] = start + minlen - 1;

  return res;
}

class Solution {
 public:
  vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
    unordered_map<int, int> um;
    for (auto i : small) {
      um[i]++;
    }

    int lb = big.size();
    int ls = small.size();

    int right = 0;
    int left = 0;

    int minstart = 0;
    int minlen = INT_MAX;
    while (right < lb) {
      if (um[big[right++]]-- > 0) {
        --ls;
      }
      while (ls == 0) {
        if (right - left < minlen) {
          minstart = left;
          minlen = right - left;
        }
        if (++um[big[left++]] > 0) {
          ++ls;
        }
      }
    }

    if (minlen == INT_MAX) {
      return {};
    }
    return {minstart, minstart + minlen - 1};
  }
};