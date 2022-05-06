/*
请你设计并实现一个满足LRU(最近最少使用)缓存约束的数据结构。
实现LRUCache类：
LRUCache(int capacity)以正整数作为容量capacity初始化LRU缓存
int get(int key)如果关键字key存在于缓存中，则返回关键字的值，否则返回-1。
void put(int key, int value)如果关键字key已经存在，则变更其数据值value；
如果不存在，则向缓存中插入该组key-value。
如果插入操作导致关键字数量超过capacity，则应该逐出最久未使用的关键字。
函数get和put必须以O(1)的平均时间复杂度运行。

示例：
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4

提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 10^5
最多调用2*10^5次get和put
*/

// 面试题1625LRU缓存

// 题目要求O(1)完成查询和插入，需要使用hash链表。
// 而C语言优秀库uthash底层本身就是用双向链表实现的hash
typedef struct {
  int key;
  int val;
  UT_hash_handle hh;
} LRUCache;

LRUCache *g_usr = NULL;
int g_size;

LRUCache *lRUCacheCreate(int capacity) {
  g_size = capacity;
  return g_usr;
}

int lRUCacheGet(LRUCache *obj, int key) {
  LRUCache *cur_usr = NULL;
  HASH_FIND_INT(g_usr, &key, cur_usr);
  // get存在的key，则该key被使用了一次，因此需要先删后入，满足LRU
  if (cur_usr != NULL) {
    HASH_DEL(g_usr, cur_usr);
    HASH_ADD_INT(g_usr, key, cur_usr);
    return cur_usr->val;
  }
  return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
  LRUCache *cur_usr = NULL, *next_usr = NULL;
  HASH_FIND_INT(g_usr, &key, cur_usr);
  if (cur_usr != NULL) {
    HASH_DEL(g_usr, cur_usr);
    cur_usr->key = key;
    cur_usr->val = value;
    HASH_ADD_INT(g_usr, key, cur_usr);
  } else {  // 新插入
    int cnt = HASH_COUNT(g_usr);
    if (cnt == g_size) {
      HASH_ITER(hh, g_usr, cur_usr, next_usr) {
        HASH_DEL(g_usr, cur_usr);
        free(cur_usr);
        break;
      }
    }
    LRUCache *new_usr = (LRUCache *)malloc(sizeof(LRUCache));
    new_usr->key = key;
    new_usr->val = value;
    HASH_ADD_INT(g_usr, key, new_usr);
  }
  return;
}

void lRUCacheFree(LRUCache *obj) {
  LRUCache *cur_usr = NULL, *next_usr = NULL;
  HASH_ITER(hh, g_usr, cur_usr, next_usr) {
    HASH_DEL(g_usr, cur_usr);
    free(cur_usr);
  }
}