/*
实现RandomizedSet类：
RandomizedSet()
初始化RandomizedSet对象。
bool insert(intval)
当元素val不存在时，向集合中插入该项，并返回true，否则，返回false。
bool remove(intval)
当元素val存在时，从集合中移除该项，并返回true，否则，返回false。
int getRandom()
随机返回现有集合中的一项，测试用例保证调用此方法时集合中至少存在一个元素。
每个元素应该有相同的概率被返回。
你必须实现类的所有函数，并满足每个函数的平均时间复杂度为O(1)。

示例：
输入
["RandomizedSet", "insert", "remove", "insert",
 "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出
[null, true, false, true, 2, true, false, 2]

解释
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // 向集合中插入1。返回true表示1被成功地插入。
randomizedSet.remove(2); // 返回false，表示集合中不存在2。
randomizedSet.insert(2); // 向集合中插入2。返回true。集合现在包含[1,2]。
randomizedSet.getRandom(); // getRandom应随机返回1或2。
randomizedSet.remove(1); // 从集合中移除1，返回true。集合现在包含[2]。
randomizedSet.insert(2); // 2已在集合中，所以返回false。
randomizedSet.getRandom(); // 由于2是集合中唯一的数字，getRandom总是返回2。

提示：
-2^31 <= val <= 2^31-1
最多调用insert、remove和getRandom函数2*10^5次
在调用getRandom方法时，数据结构中至少存在一个元素。
*/

// 剑指OfferII030插入、删除和随机访问都是O(1)的容器

typedef struct {
  int val;
  UT_hash_handle hh;
} RandomizedSet;
RandomizedSet* set = NULL;
RandomizedSet* randomizedSetCreate() {
  return (RandomizedSet*)calloc(1, sizeof(RandomizedSet));
}
bool randomizedSetInsert(RandomizedSet* obj, int val) {
  RandomizedSet* tmp;
  HASH_FIND_INT(set, &val, tmp);
  if (tmp == NULL) {
    tmp = (RandomizedSet*)calloc(1, sizeof(RandomizedSet));
    tmp->val = val;
    HASH_ADD_INT(set, val, tmp);
    return true;
  }
  return false;
}
bool randomizedSetRemove(RandomizedSet* obj, int val) {
  RandomizedSet* tmp;
  HASH_FIND_INT(set, &val, tmp);
  if (tmp != NULL) {
    HASH_DEL(set, tmp);
    free(tmp);
    return true;
  }
  return false;
}
int randomizedSetGetRandom(RandomizedSet* obj) {
  int cnt = 0;
  cnt = HASH_COUNT(set);
  int loop = rand() % cnt;
  RandomizedSet *current_user, *tmp;
  cnt = 0;
  HASH_ITER(hh, set, current_user, tmp) {
    if (cnt++ >= loop) {
      break;
    }
  }
  return current_user->val;
}
void randomizedSetFree(RandomizedSet* obj) {
  RandomizedSet *current_user, *tmp;
  HASH_ITER(hh, set, current_user, tmp) {
    HASH_DEL(set, current_user);
    free(current_user);
  }
  return;
}

class RandomizedSet {
 public:
  RandomizedSet() { srand((unsigned)time(NULL)); }

  bool insert(int val) {
    if (indices.count(val)) {
      return false;
    }
    int index = nums.size();
    // vector从尾端添加元素，O(1)
    nums.emplace_back(val);
    // 哈希map添加元素，O(1)
    indices[val] = index;
    return true;
  }
  bool remove(int val) {
    if (!indices.count(val)) {
      return false;
    }
    int index = indices[val];
    // vector删除元素不是O(1)；
    // 但是把要删除的元素交互到尾端，然后在删除尾端元素，是O(1)
    int last = nums.back();
    nums[index] = last;
    indices[last] = index;
    nums.pop_back();
    // 哈希map删除元素，O(1)
    indices.erase(val);
    return true;
  }
  int getRandom() {
    int randomIndex = rand() % nums.size();
    return nums[randomIndex];
  }

 private:
  // 保存集合元素，使得随机操作可以O(1)
  vector<int> nums;
  // key为集合元素，value为集合元素在nums中的下标
  unordered_map<int, int> indices;
};