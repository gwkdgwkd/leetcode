/*
给你一个按升序排序的整数数组num（可能包含重复数字），
请你将它们分割成一个或多个长度至少为3的子序列，其中每个子序列都由连续整数组成。
如果可以完成上述分割，则返回true；否则，返回false。

示例1：
输入：[1,2,3,3,4,5]
输出：True
解释：
你可以分割出这样两个连续子序列：
1, 2, 3
3, 4, 5

示例2：
输入：[1,2,3,3,4,4,5,5]
输出：True
解释：
你可以分割出这样两个连续子序列：
1, 2, 3, 4, 5
3, 4, 5

示例3：
输入：[1,2,3,4,4,5]
输出：False

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

// 由于需要将数组分割成一个或多个由连续整数组成的子序列，
// 因此只要知道子序列的最后一个数字和子序列的长度，就能确定子序列。
// 当x在数组中时，如果存在一个子序列以x−1结尾，长度为k，
// 则可以将x加入该子序列中，得到长度为k+1的子序列。
// 如果不存在以x−1结尾的子序列，则必须新建一个只包含x的子序列，长度为1。
// 当x在数组中时，如果存在多个子序列以x−1结尾，应该将x加入其中的哪一个子序列？
// 由于题目要求每个子序列的长度至少为3，显然应该让最短的子序列尽可能长，
// 因此应该将x加入其中最短的子序列。

// 哈希表 + 最小堆
class Solution {
 public:
  bool isPossible(vector<int>& nums) {
    // 哈希表的键为子序列的最后一个数字，值为最小堆，用于存储所有的子序列长度，
    // 最小堆满足堆顶的元素是最小的，因此堆顶的元素即为最小的子序列长度：
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> mp;
    for (auto& x : nums) {
      if (mp.find(x) == mp.end()) {
        mp[x] = priority_queue<int, vector<int>, greater<int>>();
      }
      if (mp.find(x - 1) != mp.end()) {
        int prevLength = mp[x - 1].top();
        mp[x - 1].pop();
        if (mp[x - 1].empty()) {
          mp.erase(x - 1);
        }
        mp[x].push(prevLength + 1);
      } else {
        mp[x].push(1);
      }
    }
    for (auto it = mp.begin(); it != mp.end(); ++it) {
      if (it->second.top() < 3) {
        return false;
      }
    }
    return true;
  }
};