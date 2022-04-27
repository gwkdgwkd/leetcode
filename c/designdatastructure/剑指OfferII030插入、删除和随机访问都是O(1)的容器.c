/*
设计一个支持在平均时间复杂度O(1)下，执行以下操作的数据结构：
insert(val)：当元素val不存在时返回true，并向集合中插入该项，否则返回false。
remove(val)：当元素val存在时返回true，并从集合中移除该项，否则返回false。
getRandom：随机返回现有集合中的一项。每个元素应该有相同的概率被返回。

示例:
输入: inputs = ["RandomizedSet", "insert", "remove", 
"insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出: [null, true, false, true, 2, true, false, 2]
解释:
RandomizedSet randomSet = new RandomizedSet();  // 初始化一个空的集合
randomSet.insert(1); // 向集合中插入1，返回true表示1被成功地插入
randomSet.remove(2); // 返回false，表示集合中不存在2 
randomSet.insert(2); // 向集合中插入2返回true，集合现在包含[1,2] 
randomSet.getRandom(); // getRandom应随机返回1或2 
randomSet.remove(1); // 从集合中移除1返回true。集合现在包含[2] 
randomSet.insert(2); // 2已在集合中，所以返回false 
randomSet.getRandom(); // 由于2是集合中唯一的数字，getRandom总是返回2 

提示：
-2^31 <= val <= 2^31 - 1
最多进行2*10^5次insert，remove和getRandom方法调用
当调用getRandom方法时，集合中至少有一个元素

注意：本题与380题相同
*/

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