/*
给定一组单词words，编写一个程序，找出其中的最长单词，
且该单词由这组单词中的其他单词组合而成。
若有多个长度相同的结果，返回其中字典序最小的一项，
若没有符合要求的单词则返回空字符串。

示例：
输入：["cat","banana","dog","nana",
      "walk","walker","dogwalker"]
输出："dogwalker"
解释："dogwalker"可由"dog"和"walker"组成。

提示：
0 <= len(words) <= 200
1 <= len(words[i]) <= 100
*/

// 字典树
typedef struct TrieNode {
  bool isEnd;
  struct TrieNode *next[26];
} Trie;
void TrieInsert(Trie *obj, char *word) {
  while (*word) {
    if (obj->next[word[0] - 'a'] == NULL) {
      obj->next[word[0] - 'a'] = (Trie *)calloc(1, sizeof(Trie));
    }
    obj = obj->next[word[0] - 'a'];
    word++;
  }
  obj->isEnd = true;
}
bool TrieSearch(Trie *obj, Trie *tree, char *word, int word_cnt) {
  // 1.回溯出口1，单词结束
  if (!word[0]) {
    return word_cnt >= 1 && obj->isEnd;
  }
  // 2.若当前是单词节点，可能没有子节点，因此先判断但此节点再判断后序字符是否存在
  return (obj->isEnd && TrieSearch(tree, tree, word,
                                   word_cnt + 1)) ||  // 死循环：root->isEnd成立
         (obj->next[word[0] - 'a'] &&
          TrieSearch(obj->next[word[0] - 'a'], tree, word + 1, word_cnt));
}
char **longestWord(char **words, int wordsSize) {
  Trie *tree = (Trie *)calloc(1, sizeof(Trie));
  for (int i = 0; i < wordsSize; i++) {
    if (words[i][0])
      TrieInsert(tree, words[i]);  // 请注意这里问题！就是Tire根节点isEnd=true
  }
  // 不加上面的if判断，这里就更新根节点的isEnd=false
  // tree->isEnd = false;
  int maxLen = 0;
  char *res = "";
  for (int i = 0; i < wordsSize; i++) {
    if (TrieSearch(tree, tree, words[i], 0)) {
      int len = strlen(words[i]);
      if (len > maxLen || len == maxLen && strcmp(words[i], res) < 0) {
        maxLen = len;
        res = words[i];
      }
    }
  }
  return res;
}

class Solution {
 public:
  struct TrieNode {
    bool isWord;
    unordered_map<char, TrieNode *> nodes;

    TrieNode() { isWord = false; }
  };

  int fin = 0;  // 代表已经找到结果，深度递归停止
  int flag1 = 0;  // 递归字典树过程中，未至终点已经发现其它单词
  TrieNode *root;

  // r代表当前字典树节点的指针
  void dfs(int index, string &word, TrieNode *r) {
    if (index >= word.size()) return;  // 防止字符越界
    if (fin == 1) return;

    if (r->nodes.find(word[index]) == r->nodes.end()) return;
    // 遍历到长单词下一个字母对应的字典树的指针
    r = r->nodes[word[index]];

    if (index == word.size() - 1) {
      if (r->isWord && flag1) {
        fin = 1;
      }
      return;
    } else if (r->isWord) {  // 还没有到当前单词的最后一个字母
      int flag1Ori = flag1;

      // 代表从这里对长单词截断
      flag1 = 1;
      dfs(index + 1, word, root);
      if (fin == 1) return;

      flag1 = flag1Ori;
    }

    dfs(index + 1, word, r);
  }

  string longestWord(vector<string> &words) {
    root = new TrieNode();

    sort(words.begin(), words.end(), [](string &a, string &b) {
      return a.size() == b.size() ? a < b : a.size() > b.size();
    });

    // 建立字典树
    for (auto &w : words) {
      TrieNode *cur = root;
      for (int i = 0; i < w.size(); i++) {
        if (cur->nodes.find(w[i]) == cur->nodes.end()) {
          cur->nodes[w[i]] = new TrieNode();
        }
        cur = cur->nodes[w[i]];
      }
      cur->isWord = true;
    }

    for (int i = 0; i < words.size() - 1; i++) {
      flag1 = 0;
      dfs(0, words[i], root);
      if (fin == 1) return words[i];
    }

    return "";
  }
};