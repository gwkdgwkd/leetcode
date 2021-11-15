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
  if (cur_usr !=
      NULL) {  // get存在的key，则该key被使用了一次，因此需要先删后入，满足LRU
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