/*
设计一个map，满足以下几点：
字符串表示键，整数表示值，返回具有前缀等于给定字符串的键的值的总和。
实现一个MapSum类：
MapSum()
初始化MapSum对象
void insert(String key, int val)
插入key-val键值对，字符串表示键key，整数表示值val。
如果键key已经存在，那么原来的键值对key-value将被替代成新的键值对。
int sum(string prefix)
返回所有以该前缀prefix开头的键key的值的总和。

示例1：
输入：["MapSum", "insert", "sum", "insert", "sum"]
     [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
输出：[null, null, 3, null, 5]
解释：MapSum mapSum = new MapSum();
     mapSum.insert("apple", 3);
     mapSum.sum("ap"); // 返回3 (apple = 3)
     mapSum.insert("app", 2);
     mapSum.sum("ap"); // 返回5 (apple + app = 3 + 2 = 5)

提示：
1 <= key.length, prefix.length <= 50
key和prefix仅由小写英文字母组成
1 <= val <= 1000
最多调用50次insert和sum
*/

// 剑指OfferII066单词之和

#define LEN 26
typedef struct {
  struct MapSum* children[LEN];
  int val;
} MapSum;
MapSum* mapSumCreate() { return (MapSum*)calloc(1, sizeof(MapSum)); }
void mapSumInsert(MapSum* obj, char* key, int val) {
  int len = strlen(key);
  for (int i = 0; i < len; ++i) {
    int c = key[i] - 'a';
    if (obj->children[c] == NULL) {
      obj->children[c] = mapSumCreate();
    }
    obj = obj->children[c];
  }
  obj->val = val;
}
void dfs(MapSum* tire, int* sum) {
  if (tire == 0) {
    return;
  }
  if (tire->val > 0) {
    (*sum) += tire->val;
  }
  for (int i = 0; i < 26; i++) {
    if (tire->children[i] != 0) {
      dfs(tire->children[i], sum);
    }
  }
  return;
}
int mapSumSum(MapSum* obj, char* prefix) {
  int res = 0;
  int len = strlen(prefix);
  for (int i = 0; i < len; ++i) {
    int c = prefix[i] - 'a';
    if (obj->children[c] == NULL) {
      return res;
    }
    obj = obj->children[c];
  }
  dfs(obj, &res);
  return res;
}
void mapSumFree(MapSum* obj) {
  for (int i = 0; i < LEN; ++i) {
    if (obj->children[i]) {
      mapSumFree(obj->children[i]);
    }
  }
  free(obj);
}

struct TrieNode {
  int val;
  TrieNode* next[26];
  TrieNode() {
    this->val = 0;
    for (int i = 0; i < 26; ++i) {
      this->next[i] = nullptr;
    }
  }
};

class MapSum {
 public:
  MapSum() { this->root = new TrieNode(); }
  void insert(string key, int val) {
    int delta = val;
    if (cnt.count(key)) {
      delta -= cnt[key];
    }
    cnt[key] = val;
    TrieNode* node = root;
    for (auto c : key) {
      if (node->next[c - 'a'] == nullptr) {
        node->next[c - 'a'] = new TrieNode();
      }
      node = node->next[c - 'a'];
      node->val += delta;
    }
  }
  int sum(string prefix) {
    TrieNode* node = root;
    for (auto c : prefix) {
      if (node->next[c - 'a'] == nullptr) {
        return 0;
      } else {
        node = node->next[c - 'a'];
      }
    }
    return node->val;
  }

 private:
  TrieNode* root;
  unordered_map<string, int> cnt;
};
