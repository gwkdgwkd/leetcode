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
lRUCache.put(1, 1); // 缓存是{1=1}
lRUCache.put(2, 2); // 缓存是{1=1, 2=2}
lRUCache.get(1);    // 返回1
lRUCache.put(3, 3); // 该操作会使得关键字2作废，缓存是{1=1, 3=3}
lRUCache.get(2);    // 返回-1(未找到)
lRUCache.put(4, 4); // 该操作会使得关键字1作废，缓存是{4=4, 3=3}
lRUCache.get(1);    // 返回-1(未找到)
lRUCache.get(3);    // 返回3
lRUCache.get(4);    // 返回4

提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 10^5
最多调用2*10^5次get和put
*/

// 剑指OfferII031最近最少使用缓存
// 面试题1625LRU缓存

// 哈希表 + 双向链表
// LRU缓存机制可以通过哈希表辅以双向链表实现，我们用一个哈希表和一个双向链表维护所有在缓存中的键值对。
// 双向链表按照被使用的顺序存储了这些键值对，靠近头部的键值对是最近使用的，而靠近尾部的键值对是最久未使用的。
// 哈希表即为普通的哈希映射（HashMap），通过缓存数据的键映射到其在双向链表中的位置。
// 这样以来，我们首先使用哈希表进行定位，找出缓存项在双向链表中的位置，随后将其移动到双向链表的头部，
// 即可在O(1)的时间内完成get或者put操作。具体的方法如下：
// 对于get操作，首先判断key是否存在：
//  如果key不存在，则返回-1；
//  如果key存在，则key对应的节点是最近被使用的节点。
//  通过哈希表定位到该节点在双向链表中的位置，并将其移动到双向链表的头部，最后返回该节点的值。
// 对于put操作，首先判断key是否存在：
//  如果key不存在，使用key和value创建一个新的节点，在双向链表的头部添加该节点，
//  并将key和该节点添加进哈希表中。
//  然后判断双向链表的节点数是否超出容量，如果超出容量，则删除双向链表的尾部节点，并删除哈希表中对应的项；
//  如果key存在，则与get操作类似，先通过哈希表定位，再将对应的节点的值更新为value，并将该节点移到双向链表的头部。
// 上述各项操作中，访问哈希表的时间复杂度为O(1)，
// 在双向链表的头部添加节点、在双向链表的尾部删除节点的复杂度也为O(1)。
// 而将一个节点移到双向链表的头部，可以分成删除该节点和在双向链表的头部添加节点两步操作，都可以在O(1)时间内完成。

// 题目要求O(1)完成查询和插入，需要使用hash链表。
// 而C语言优秀库uthash底层本身就是用双向链表实现的hash
typedef struct {
  int key;
  int val;
  UT_hash_handle hh;
} LRUCache;
LRUCache* g_usr = NULL;
int g_size;
LRUCache* lRUCacheCreate(int capacity) {
  g_size = capacity;
  return g_usr;
}
int lRUCacheGet(LRUCache* obj, int key) {
  LRUCache* cur_usr = NULL;
  HASH_FIND_INT(g_usr, &key, cur_usr);
  // get存在的key，则该key被使用了一次，因此需要先删后入，满足LRU
  if (cur_usr != NULL) {
    HASH_DEL(g_usr, cur_usr);
    HASH_ADD_INT(g_usr, key, cur_usr);
    return cur_usr->val;
  }
  return -1;
}
void lRUCachePut(LRUCache* obj, int key, int value) {
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
    LRUCache* new_usr = (LRUCache*)malloc(sizeof(LRUCache));
    new_usr->key = key;
    new_usr->val = value;
    HASH_ADD_INT(g_usr, key, new_usr);
  }
  return;
}
void lRUCacheFree(LRUCache* obj) {
  LRUCache *cur_usr = NULL, *next_usr = NULL;
  HASH_ITER(hh, g_usr, cur_usr, next_usr) {
    HASH_DEL(g_usr, cur_usr);
    free(cur_usr);
  }
}

struct DLinkedNode {
  int key, value;
  DLinkedNode* prev;
  DLinkedNode* next;
  DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
  DLinkedNode(int _key, int _value)
      : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
 private:
  unordered_map<int, DLinkedNode*> cache;
  DLinkedNode* head;
  DLinkedNode* tail;
  int size;
  int capacity;

 public:
  LRUCache(int _capacity) : capacity(_capacity), size(0) {
    // 使用伪头部和伪尾部节点
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (!cache.count(key)) {
      return -1;
    }
    // 如果key存在，先通过哈希表定位，再移到头部
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void put(int key, int value) {
    if (!cache.count(key)) {
      // 如果key不存在，创建一个新的节点
      DLinkedNode* node = new DLinkedNode(key, value);
      // 添加进哈希表
      cache[key] = node;
      // 添加至双向链表的头部
      addToHead(node);
      ++size;
      if (size > capacity) {
        // 如果超出容量，删除双向链表的尾部节点
        DLinkedNode* removed = removeTail();
        // 删除哈希表中对应的项
        cache.erase(removed->key);
        // 防止内存泄漏
        delete removed;
        --size;
      }
    } else {
      // 如果key存在，先通过哈希表定位，再修改value，并移到头部
      DLinkedNode* node = cache[key];
      node->value = value;
      moveToHead(node);
    }
  }

  void addToHead(DLinkedNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(DLinkedNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void moveToHead(DLinkedNode* node) {
    removeNode(node);
    addToHead(node);
  }

  DLinkedNode* removeTail() {
    DLinkedNode* node = tail->prev;
    removeNode(node);
    return node;
  }
};