/*
请你为最不经常使用（LFU）缓存算法设计并实现数据结构。
实现LFUCache类：
LFUCache(int capacity)
用数据结构的容量capacity初始化对象。
int get(int key)
如果键key存在于缓存中，则获取键的值，否则返回-1。
void put(int key, int value)
如果键key已存在，则变更其值；
如果键不存在，请插入键值对。
当缓存达到其容量capacity时，则应该在插入新项之前，移除最不经常使用的项。
在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，
应该去除最近最久未使用的键。

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
cnt(x) = 键x的使用计数
cache=[]将显示最后一次使用的顺序（最左边的元素是最近的）
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // 返回1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 去除键2，因为cnt(2)=1，使用计数最小
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
0 <= capacity <= 10^4
0 <= key <= 10^5
0 <= value <= 10^9
最多调用2 * 10^5次get和put方法
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

// 哈希表 + 平衡二叉树
struct Node {
  int cnt, time, key, value;
  Node(int _cnt, int _time, int _key, int _value)
      : cnt(_cnt), time(_time), key(_key), value(_value) {}
  bool operator<(const Node &rhs) const {
    return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
  }
};
// 其中cnt表示缓存使用的频率，time表示缓存的使用时间，
// key和value表示缓存的键值。
// 比较直观的想法就是用哈希表key_table以键key为索引存储缓存，
// 建立一个平衡二叉树S来保持缓存根据(cnttime)双关键字。
// 在C++中，可以使用STL提供的std::set类，set背后的实现是红黑树：
// 对于get(key)操作，只要查看一下哈希表key_table是否有key这个键即可，
// 有的话需要同时更新哈希表和集合中该缓存的使用频率以及使用时间，否则返回-1。
// 对于put(key,value)操作，首先需要查看key_table中是否已有对应的键值。
// 如果有的话操作基本等同于get(key)，不同的是需要更新缓存的value值。
// 如果没有的话相当于是新插入一个缓存，
// 这时候需要先查看是否达到缓存容量capacity，
// 如果达到了的话，需要删除最近最少使用的缓存，
// 即平衡二叉树中最左边的结点，同时删除key_table中对应的索引，
// 最后向key_table和S插入新的缓存信息即可。
class LFUCache {
  // 缓存容量，时间戳
  int capacity, time;
  unordered_map<int, Node> key_table;
  set<Node> S;

 public:
  LFUCache(int _capacity) {
    capacity = _capacity;
    time = 0;
    key_table.clear();
    S.clear();
  }

  int get(int key) {
    if (capacity == 0) return -1;
    auto it = key_table.find(key);
    // 如果哈希表中没有键key，返回-1
    if (it == key_table.end()) return -1;
    // 从哈希表中得到旧的缓存
    Node cache = it->second;
    // 从平衡二叉树中删除旧的缓存
    S.erase(cache);
    // 将旧缓存更新
    cache.cnt += 1;
    cache.time = ++time;
    // 将新缓存重新放入哈希表和平衡二叉树中
    S.insert(cache);
    it->second = cache;
    return cache.value;
  }

  void put(int key, int value) {
    if (capacity == 0) return;
    auto it = key_table.find(key);
    if (it == key_table.end()) {
      // 如果到达缓存容量上限
      if (key_table.size() == capacity) {
        // 从哈希表和平衡二叉树中删除最近最少使用的缓存
        key_table.erase(S.begin()->key);
        S.erase(S.begin());
      }
      // 创建新的缓存
      Node cache = Node(1, ++time, key, value);
      // 将新缓存放入哈希表和平衡二叉树中
      key_table.insert(make_pair(key, cache));
      S.insert(cache);
    } else {
      // 这里和get()函数类似
      Node cache = it->second;
      S.erase(cache);
      cache.cnt += 1;
      cache.time = ++time;
      cache.value = value;
      S.insert(cache);
      it->second = cache;
    }
  }
};

// 双哈希表
struct Node {
  int key, val, freq;
  Node(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
};
class LFUCache {
  // 记录一个当前缓存最少使用的频率minFreq，这是为了删除操作服务的。
  int minfreq, capacity;

  // 以键值key为索引，每个索引存放对应缓存在freq_table中链表里的内存地址，
  // 这样就能利用两个哈希表来使得两个操作的时间复杂度均为O(1)：
  unordered_map<int, list<Node>::iterator> key_table;

  // 以频率freq为索引，每个索引存放一个双向链表，
  // 这个链表里存放所有使用频率为freq的缓存，缓存里存放三个信息，
  // 分别为键key，值value，以及使用频率freq：
  unordered_map<int, list<Node>> freq_table;

 public:
  LFUCache(int _capacity) {
    minfreq = 0;
    capacity = _capacity;
    key_table.clear();
    freq_table.clear();
  }

  // 能通过索引key在key_table中找到缓存在freq_table中的链表的内存地址，
  // 如果不存在直接返回-1，否则我们能获取到对应缓存的相关信息，
  // 这样我们就能知道缓存的键值还有使用频率，直接返回key对应的值即可。
  // get操作后这个缓存的使用频率加一了，
  // 所以需要更新缓存在哈希表freq_table中的位置。
  // 已知这个缓存的键key，值value，以及使用频率freq，
  // 那么该缓存应该存放到freq_table中freq + 1索引下的链表中。
  // 所以在当前链表中O(1)删除该缓存对应的节点，根据情况更新minFreq值，
  // 然后将其O(1)插入到freq+1索引下的链表头完成更新。
  // 这其中的操作复杂度均为O(1)。
  // 你可能会疑惑更新的时候为什么是插入到链表头，
  // 这其实是为了保证缓存在当前链表中从链表头到链表尾的插入时间是有序的，
  // 为下面的删除操作服务。
  int get(int key) {
    if (capacity == 0) return -1;
    auto it = key_table.find(key);
    if (it == key_table.end()) return -1;
    list<Node>::iterator node = it->second;
    int val = node->val, freq = node->freq;
    freq_table[freq].erase(node);
    // 如果当前链表为空，需要在哈希表中删除，且更新minFreq
    if (freq_table[freq].size() == 0) {
      freq_table.erase(freq);
      if (minfreq == freq) minfreq += 1;
    }
    // 插入到freq+1中
    freq_table[freq + 1].push_front(Node(key, val, freq + 1));
    key_table[key] = freq_table[freq + 1].begin();
    return val;
  }

  // 对于put(key, value)操作，
  // 先通过索引key在 key_table中查看是否有对应的缓存，
  // 如果有的话，其实操作等价于get(key)操作，
  // 唯一的区别就是需要将当前的缓存里的值更新为value。
  // 如果没有的话，相当于是新加入的缓存，如果缓存已经到达容量，
  // 需要先删除最近最少使用的缓存，再进行插入。
  // 先考虑插入，由于是新插入的，所以缓存的使用频率一定是1，
  // 所以将缓存的信息插入到freq_table中1索引下的列表头即可，
  // 同时更新key_table[key]的信息，以及更新minFreq=1。
  // 那么剩下的就是删除操作了，由于实时维护了minFreq，
  // 所以我们能够知道freq_table里目前最少使用频率的索引，
  // 同时因为保证了链表中从链表头到链表尾的插入时间是有序的，
  // 所以freq_table[minFreq]的链表中链表尾的节点，
  // 即为使用频率最小且插入时间最早的节点，
  // 删除它同时根据情况更新minFreq，整个时间复杂度均为O(1)。
  void put(int key, int value) {
    if (capacity == 0) return;
    auto it = key_table.find(key);
    if (it == key_table.end()) {
      // 缓存已满，需要进行删除操作
      if (key_table.size() == capacity) {
        // 通过minFreq拿到freq_table[minFreq]链表的末尾节点
        auto it2 = freq_table[minfreq].back();
        key_table.erase(it2.key);
        freq_table[minfreq].pop_back();
        if (freq_table[minfreq].size() == 0) {
          freq_table.erase(minfreq);
        }
      }
      freq_table[1].push_front(Node(key, value, 1));
      key_table[key] = freq_table[1].begin();
      minfreq = 1;
    } else {
      // 与get操作基本一致，除了需要更新缓存的值
      list<Node>::iterator node = it->second;
      int freq = node->freq;
      freq_table[freq].erase(node);
      if (freq_table[freq].size() == 0) {
        freq_table.erase(freq);
        if (minfreq == freq) minfreq += 1;
      }
      freq_table[freq + 1].push_front(Node(key, value, freq + 1));
      key_table[key] = freq_table[freq + 1].begin();
    }
  }
};