/*
给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。
字母异位词是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。

示例1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

示例2:
输入: strs = [""]
输出: [[""]]

示例3:
输入: strs = ["a"]
输出: [["a"]]

提示：
1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i]仅包含小写字母
*/

// 剑指OfferII033变位词组

#define STR_SIZE 100
typedef struct Node {
  char str[STR_SIZE];  // key为字符串
  int row;             // value为结果所在的行
  struct Node *next;
} HashNode;

int hash(char *str, int size) {
  long h = 0;
  for (int i = 0; i < strlen(str); i++) {
    // 字符串的hashcode,权为26是因为小写字母，不限制时为128，
    // 这样能够让结点尽可能分布均匀，减少地址冲突取模是为了防止int型溢出
    h = (h * 26 % size + str[i] - 'a') % size;
  }
  return h % size;
}

bool contain(HashNode *hashtable, char *str, int size) {
  HashNode *head = &hashtable[hash(str, size)];
  HashNode *tail = head->next;
  while (tail) {
    if (strcmp(tail->str, str) == 0) return true;
    tail = tail->next;
  }
  return false;
}

void add(HashNode *hashtable, char *str, int size, int row) {
  if (contain(hashtable, str, size)) return;
  HashNode *head = &hashtable[hash(str, size)];
  // 头插建表
  HashNode *q = malloc(sizeof(HashNode));
  strcpy(q->str, str);
  q->row = row;
  q->next = head->next;
  head->next = q;
}

int getRows(HashNode *hashtable, char *str, int size) {
  HashNode *head = &hashtable[hash(str, size)];
  HashNode *tail = head->next;
  while (tail) {
    if (strcmp(tail->str, str) == 0) return tail->row;
    tail = tail->next;
  }
  return -1;
}

int cmp(const void *a, const void *b) { return *(char *)a - *(char *)b; }

char ***groupAnagrams(char **strs, int strsSize, int *retSize,
                      int **columnSizes) {
  if (strsSize == 0 || strs == NULL) {
    *retSize = 0;
    return NULL;
  }
  HashNode *hashtable = malloc(sizeof(HashNode) * strsSize);
  memset(hashtable, 0, sizeof(HashNode) * strsSize);
  char ***ans = malloc(sizeof(char **) * strsSize);

  *retSize = 0;
  *columnSizes = malloc(sizeof(int) * strsSize);

  for (int i = 0; i < strsSize; i++) {
    char curStr[STR_SIZE] = "";
    strcpy(curStr, strs[i]);
    int lenStr = strlen(curStr);
    qsort(curStr, lenStr, sizeof(char), cmp);  // 排序

    if (contain(hashtable, curStr, strsSize)) {  // key已经存在了
      int row =
          getRows(hashtable, curStr, strsSize);  // 获得之前key的结果所在行
      int col = (*columnSizes)[row];
      ans[row][col] = malloc(sizeof(char) * (lenStr + 1));
      strcpy(ans[row][col], strs[i]);
      (*columnSizes)[row]++;
    } else {                                              // key不存在
      add(hashtable, curStr, strsSize, *retSize);         // 插入表中
      ans[*retSize] = malloc(sizeof(char *) * strsSize);  // 申请一行
      ans[*retSize][0] = malloc(sizeof(char) * (lenStr + 1));
      strcpy(ans[*retSize][0], strs[i]);
      (*columnSizes)[*retSize] = 1;
      (*retSize)++;
    }
  }
  return ans;
}

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> hash;
    for (auto &str : strs) {
      string key = str;
      sort(key.begin(), key.end());  // 排序
      hash[key].emplace_back(str);   // 排序后的string当作key
    }
    vector<vector<string>> ans;
    for (auto it = hash.begin(); it != hash.end(); ++it) {
      ans.emplace_back(it->second);
    }
    return ans;
  }
};