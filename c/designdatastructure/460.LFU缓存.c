/*
请你为最不经常使用（LFU）缓存算法设计并实现数据结构。
实现LFUCache 类：
LFUCache(int capacity) - 用数据结构的容量capacity初始化对象
int get(int key) - 如果键key存在于缓存中，则获取键的值，否则返回-1。
void put(int key, int value) - 如果键key已存在，则变更其值；
如果键不存在，请插入键值对。当缓存达到其容量capacity时，则应该在插入新项之前，移除最不经常使用的项。
在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除最近最久未使用的键。

为了确定最不常使用的键，可以为缓存中的每个键维护一个使用计数器。
使用计数最小的键是最久未使用的键。
当一个键首次插入到缓存中时，它的使用计数器被设置为1(由于put操作)。
对缓存中的键执行get或put操作，使用计数器的值将会递增。
函数get和put必须以O(1)的平均时间复杂度运行。

示例：
输入：
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get",
"get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
输出：
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

解释：
// cnt(x) = 键x的使用计数
// cache=[]将显示最后一次使用的顺序（最左边的元素是最近的）
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // 返回1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 去除键2 ，因为cnt(2)=1，使用计数最小
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // 返回-1（未找到）
lfu.get(3);      // 返回3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // 去除键1，1和3的cnt相同，但1最久未使用
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // 返回-1（未找到）
lfu.get(3);      // 返回3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // 返回4
                 // cache=[3,4], cnt(4)=2, cnt(3)=3

提示：
0 <= capacity <= 104
0 <= key <= 105
0 <= value <= 109
最多调用2 * 105次get和put方法
*/

struct LFUNode {
  int key;
  int value;
  int frequency;
  UT_hash_handle hh;
  struct LFUNode *prev;
  struct LFUNode *next;
};

struct FreDlist {
  int key;
  struct LFUNode *head;
  struct LFUNode *tail;
  UT_hash_handle hh;
};

// alloc free addtohead remove(from tail)
static inline void AllocFreDlist(struct FreDlist **list) {
  *list = (struct FreDlist *)malloc(sizeof(struct FreDlist));
  (*list)->head = (struct LFUNode *)malloc(sizeof(struct LFUNode));
  (*list)->tail = (struct LFUNode *)malloc(sizeof(struct LFUNode));
  (*list)->head->next = (*list)->tail;
  (*list)->tail->prev = (*list)->head;
}

static inline void FreeFreDlist(struct FreDlist *list) {
  free(list->head);
  free(list->tail);
  free(list);
}

static inline void AddNodeToHead(struct LFUNode *head, struct LFUNode *node) {
  node->next = head->next;
  node->prev = head;
  head->next->prev = node;
  head->next = node;
}

static inline void RemoveNode(struct LFUNode *node) {
  node->next->prev = node->prev;
  node->prev->next = node->next;
}

typedef struct {
  struct FreDlist *freMap;
  struct LFUNode *nodeMap;
  int cap;  // HASH_COUNT(nodeMap) <= cap
  int minFre;
} LFUCache;

LFUCache *lFUCacheCreate(int capacity) {
  LFUCache *obj = (LFUCache *)malloc(sizeof(LFUCache));
  obj->freMap = NULL;
  obj->nodeMap = NULL;
  obj->cap = capacity;
  obj->minFre = 0;
  return obj;
}

int lFUCacheGet(LFUCache *obj, int key) {
  if (obj->cap == 0) {
    return -1;
  }
  // printf("get %d\n", key);
  struct LFUNode *node = NULL;
  struct FreDlist *list = NULL;

  HASH_FIND_INT(obj->nodeMap, &key, node);
  if (node == NULL) {
    return -1;
  }

  if (obj->minFre == node->frequency) {
    HASH_FIND_INT(obj->freMap, &node->frequency, list);
    if (node->prev == list->head && node->next == list->tail) {
      obj->minFre++;
    }
  }
  RemoveNode(node);
  (node->frequency)++;

  HASH_FIND_INT(obj->freMap, &node->frequency, list);
  if (list == NULL) {
    AllocFreDlist(&list);
    list->key = node->frequency;
    HASH_ADD_INT(obj->freMap, key, list);
  }
  AddNodeToHead(list->head, node);

  return node->value;
}

void lFUCachePut(LFUCache *obj, int key, int value) {
  if (obj->cap == 0) {
    return;
  }
  // printf("put %d %d\n", key, value);
  struct LFUNode *node = NULL;
  struct FreDlist *list = NULL;

  HASH_FIND_INT(obj->nodeMap, &key, node);
  if (node != NULL) {
    node->value = value;
    HASH_FIND_INT(obj->freMap, &node->frequency, list);
    RemoveNode(node);
    AddNodeToHead(list->head, node);
    lFUCacheGet(obj, key);
    return;
  }

  node = (struct LFUNode *)malloc(sizeof(struct LFUNode));
  node->key = key;
  node->value = value;
  HASH_ADD_INT(obj->nodeMap, key, node);
  // add to fremap
  node->frequency = 1;
  HASH_FIND_INT(obj->freMap, &node->frequency, list);
  if (list == NULL) {
    AllocFreDlist(&list);
    list->key = node->frequency;
    HASH_ADD_INT(obj->freMap, key, list);
  }
  AddNodeToHead(list->head, node);

  if (HASH_COUNT(obj->nodeMap) > obj->cap) {
    HASH_FIND_INT(obj->freMap, &obj->minFre, list);
    // printf("%d %d %d", obj->minFre, HASH_COUNT(obj->nodeMap), obj->cap);
    node = list->tail->prev;
    RemoveNode(node);
    HASH_DEL(obj->nodeMap, node);
    free(node);
  }
  obj->minFre = 1;
}

void lFUCacheFree(LFUCache *obj) {
  struct LFUNode *lcurr, *ltmp;
  struct FreDlist *fcurr, *ftmp;
  HASH_ITER(hh, obj->nodeMap, lcurr, ltmp) {
    HASH_DEL(obj->nodeMap, lcurr);
    RemoveNode(lcurr);
    free(lcurr);
  }
  HASH_ITER(hh, obj->freMap, fcurr, ftmp) { FreeFreDlist(fcurr); }
}