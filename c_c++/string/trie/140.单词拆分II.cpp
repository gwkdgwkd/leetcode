/*
给定一个字符串s和一个字符串字典wordDict，在字符串s中增加空格来构建一个句子，
使得句子中所有的单词都在词典中。以任意顺序返回所有这些可能的句子。
注意：词典中的同一个单词可能在分段中被重复使用多次。

示例1：
输入:s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
输出:["cats and dog","cat sand dog"]

示例2：
输入:s = "pineapplepenapple", wordDict =
["apple","pen","applepen","pine","pineapple"] 输出:["pine apple pen
apple","pineapple pen apple","pine applepen apple"] 解释:
注意你可以重复使用字典中的单词。

示例3：
输入:s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
输出:[]

提示：
1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s和wordDict[i]仅有小写英文字母组成
wordDict中所有字符串都不同
*/

// 记忆化搜索，官方题解
// 字典树 + 回溯
struct Trie {
  int ch[26];
  bool flag;
} trie[10001];
int size;
void insert(char* s, int sSize) {
  int add = 0;
  for (int i = 0; i < sSize; i++) {
    int x = s[i] - 'a';
    if (trie[add].ch[x] == 0) {
      trie[add].ch[x] = ++size;
      memset(trie[size].ch, 0, sizeof(trie[size].ch));
      trie[size].flag = false;
    }
    add = trie[add].ch[x];
  }
  trie[add].flag = true;
}
bool find(char* s, int sSize) {
  int add = 0;
  for (int i = 0; i < sSize; i++) {
    int x = s[i] - 'a';
    if (trie[add].ch[x] == 0) {
      return false;
    }
    add = trie[add].ch[x];
  }
  return trie[add].flag;
}

char** ans[1001];
int ansSize[1001];
void backtrack(char* s, int sSize, int index) {
  if (ans[index] == NULL) {
    ans[index] = malloc(sizeof(char**));
    if (index == sSize) {
      ansSize[index] = 1;
      char* tmp = malloc(sizeof(char));
      tmp[0] = '\0';
      ans[index][0] = tmp;
      return;
    }
    ansSize[index] = 0;
    for (int i = index + 1; i <= sSize; ++i) {
      int len = i - index;
      char* word = malloc(sizeof(char) * (len + 1));
      for (int j = 0; j < len; ++j) word[j] = s[index + j];
      word[len] = '\0';
      if (find(word, len)) {
        backtrack(s, sSize, i);
        ans[index] =
            realloc(ans[index], sizeof(char**) * (ansSize[index] + ansSize[i]));
        for (int j = 0; j < ansSize[i]; ++j) {
          int len1 = len, len2 = strlen(ans[i][j]);
          char* tmp = malloc(sizeof(char) * (len1 + len2 + 2));
          strcpy(tmp, word);
          if (len2 > 0) {
            tmp[len1] = ' ';
          }
          strcpy(tmp + len1 + 1, ans[i][j]);
          ans[index][ansSize[index]++] = tmp;
        }
      }
    }
  }
}

char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {
  memset(ans, 0, sizeof(ans));
  size = 0;
  memset(trie[0].ch, 0, sizeof(trie[0].ch));
  trie[0].flag = false;
  for (int i = 0; i < wordDictSize; i++) {
    insert(wordDict[i], strlen(wordDict[i]));
  }
  backtrack(s, strlen(s), 0);
  *returnSize = ansSize[0];
  return ans[0];
}

class Trie {
 private:
  bool isend;
  Trie* next[26];

 public:
  Trie() {
    isend = false;
    memset(next, 0, sizeof(next));
  }
  void insert(const string& s) {
    Trie* node = this;
    for (const char& c : s) {
      if (!node->next[c - 'a']) node->next[c - 'a'] = new Trie();
      node = node->next[c - 'a'];
    }
    node->isend = true;
  }
  void dfs(string& s, int pos, vector<bool>& visited, vector<string>& res) {
    if (pos == s.size()) {
      string tmp;
      for (int i = 0; i < s.size(); ++i) {
        tmp += s[i];
        if (visited[i] && i != s.size() - 1) {
          tmp += ' ';
        }
      }
      res.push_back(tmp);
      return;
    }
    Trie* node = this;
    for (int i = pos; i < s.size(); ++i) {
      if (node->next[s[i] - 'a']) {
        node = node->next[s[i] - 'a'];
        if (node->isend) {
          visited[i] = true;
          dfs(s, i + 1, visited, res);
          visited[i] = false;
        }
      } else
        return;
    }
  }
};
class Solution {
 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    Trie* root = new Trie();
    vector<bool> visited(s.size(), false);
    for (const string& word : wordDict) {
      root->insert(word);
    }
    vector<string> res;
    root->dfs(s, 0, visited, res);
    return res;
  }
};