/*
给定一个较长字符串big和一个包含较短字符串的数组smalls，
设计一个方法根据smalls中的每一个较短字符串，对big进行搜索。
输出smalls中的字符串在big里出现的所有位置positions，
其中positions[i]为smalls[i]出现的所有位置。

示例：
输入：big = "mississippi"
     smalls = ["is","ppi","hi","sis","i","ssippi"]
输出：[[1,4],[8],[],[3],[1,4,7,10],[5]]

提示：
0 <= len(big) <= 1000
0 <= len(smalls[i]) <= 1000
smalls的总字符数不会超过100000。
你可以认为smalls中没有重复字符串。
所有出现的字符均为英文小写字母。
*/

typedef struct listnode {
  bool isend;
  int id;
  int num;
  struct listnode* node[26];
} Tire;
Tire* creat() {
  Tire* obj = (Tire*)malloc(sizeof(Tire));
  memset(obj, 0, sizeof(Tire));
  return obj;
}
void insertword(Tire* obj, char* word, int start) {
  Tire* tmp = obj;
  for (int i = 0; i < strlen(word); i++) {
    if (tmp->node[word[i] - 'a'] == NULL) {
      tmp->node[word[i] - 'a'] = creat();
    }
    tmp = tmp->node[word[i] - 'a'];
  }
  tmp->isend = true;
  tmp->id = start;
  tmp->num = 0;
}
void find(Tire* obj, char* word, int** arry, int* size, int start) {
  for (int i = start; i < strlen(word); i++) {
    if (obj->node[word[i] - 'a'] == NULL) {
      return;
    }
    obj = obj->node[word[i] - 'a'];
    if (obj->isend == true) {
      arry[obj->id][obj->num] = start;
      obj->num++;
      size[obj->id] = obj->num;
    }
  }
}

int** multiSearch(char* big, char** smalls, int smallsSize, int* returnSize,
                  int** returnColumnSizes) {
  Tire* obj = creat();
  for (int i = 0; i < smallsSize; i++) {
    insertword(obj, smalls[i], i);
  }
  int** res = (int**)malloc(sizeof(int*) * smallsSize);
  for (int i = 0; i < smallsSize; i++) {
    res[i] = (int*)malloc(sizeof(int) * strlen(big));
  }
  *returnColumnSizes = (int*)malloc(sizeof(int) * smallsSize);
  memset(*returnColumnSizes, 0, sizeof(int) * smallsSize);
  for (int i = 0; i < strlen(big); i++) {
    find(obj, big, res, *returnColumnSizes, i);
  }
  *returnSize = smallsSize;
  return res;
}

struct TrieNode {
  int sid;
  TrieNode* child[26];
  TrieNode() {
    sid = -1;
    for (int i = 0; i < 26; ++i) child[i] = NULL;
  }
};
class Solution {
 private:
  TrieNode* root = new TrieNode();

 public:
  void insert(string word, int s) {
    int n = word.size();
    TrieNode* cur = root;
    for (int i = 0; i < n; ++i) {
      int cid = word.at(i) - 'a';
      if (cur->child[cid] == NULL) cur->child[cid] = new TrieNode();
      cur = cur->child[cid];
    }
    cur->sid = s;
  }
  void search(string word, vector<vector<int>>& ans, int bid) {
    int n = word.size();
    TrieNode* cur = root;
    for (int i = 0; i < n; ++i) {
      int cid = word.at(i) - 'a';
      if (cur->sid != -1) ans[cur->sid].push_back(bid);
      if (cur->child[cid] == NULL) return;
      cur = cur->child[cid];
    }
    if (cur->sid != -1) ans[cur->sid].push_back(bid);
  }
  vector<vector<int>> multiSearch(string big, vector<string>& smalls) {
    int n = smalls.size(), m = big.size();
    vector<vector<int>> ans(n, vector<int>{});
    for (int i = 0; i < n; ++i) {
      if (smalls[i].size() == 0) continue;
      insert(smalls[i], i);
    }
    for (int i = 0; i < m; ++i) {
      string word = big.substr(i, m - i);
      search(word, ans, i);
    }
    return ans;
  }
};
