/*
给定一个mxn二维字符网格board和一个单词列表words，返回所有二维网格上的单词。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中相邻单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。

示例1：
输入：board = [["o","a","a","n"],
              ["e","t","a","e"],
              ["i","h","k","r"],
              ["i","f","l","v"]]，
     words = ["oath","pea","eat","rain"]
输出：["eat","oath"]

示例2：
输入：board = [["a","b"],["c","d"]]，
     words = ["abcb"]
输出：[]

提示：
m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j]是一个小写英文字母
1 <= words.length <= 3 * 10^4
1 <= words[i].length <= 10
words[i]由小写英文字母组成
words中的所有字符串互不相同
*/

// 字典树 + 回溯
struct Trie {
  bool isEnd;
  struct Trie* children[26];
};
struct Trie* trie;
struct Trie* trieCreate(void) {
  struct Trie* root = (struct Trie*)malloc(sizeof(struct Trie));
  memset(root, 0, sizeof(struct Trie));
  return root;
}
void trieInsert(char* word) {
  int len = strlen(word);
  struct Trie* cur = trie;
  for (int i = 0; i < len; i++) {
    int pos = word[i] - 'a';
    if (!cur->children[pos]) {
      cur->children[pos] = trieCreate();
    }
    cur = cur->children[pos];
  }
  cur->isEnd = true;
}
bool trieFind(char* word) {
  int len = strlen(word);
  struct Trie* cur = trie;
  for (int i = 0; i < len; i++) {
    int pos = word[i] - 'a';
    if (!cur->children[pos]) {
      return false;
    }
    cur = cur->children[pos];
  }
  if (cur->isEnd) {
    cur->isEnd = false;
    return true;
  }
  return false;
}
bool triePre(char* word) {
  int len = strlen(word);
  struct Trie* cur = trie;
  for (int i = 0; i < len; i++) {
    int pos = word[i] - 'a';
    if (!cur->children[pos]) {
      return false;
    }
    cur = cur->children[pos];
  }
  return true;
}
void trieFree(struct Trie* root) {
  if (!root) {
    return;
  }
  for (int i = 0; i < 26; i++) {
    if (root->children[i]) {
      trieFree(root->children[i]);
    }
  }
  free(root);
}
void dfs(char** board, int m, int n, int i, int j, char* path, int pos,
         bool visited[][n], char** ret, int* returnSize) {
  if (trieFind(path)) {
    ret[*returnSize] = (char*)malloc(sizeof(char) * (pos + 1));
    ret[*returnSize][0] = '\0';
    strcpy(ret[(*returnSize)++], path);
  }
  visited[i][j] = true;
  int dr[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
  for (int k = 0; k < 4; k++) {
    int x = i + dr[k][0];
    int y = j + dr[k][1];
    if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y]) {
      path[pos] = board[x][y];
      if (triePre(path)) {
        dfs(board, m, n, x, y, path, pos + 1, visited, ret, returnSize);
      }
    }
  }
  visited[i][j] = false;
  path[pos] = '\0';
}
char** findWords(char** board, int boardSize, int* boardColSize, char** words,
                 int wordsSize, int* returnSize) {
  trie = trieCreate();
  for (int i = 0; i < wordsSize; i++) {
    trieInsert(words[i]);
  }

  char** ret = (char**)malloc(sizeof(char*) * wordsSize);
  *returnSize = 0;

  int m = boardSize, n = *boardColSize;

  bool visited[m][n];
  memset(visited, false, sizeof(visited));

  char path[m * n + 1];
  memset(path, 0, sizeof(path));
  int pos = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      path[pos] = board[i][j];
      if (triePre(path)) {
        dfs(board, m, n, i, j, path, pos + 1, visited, ret, returnSize);
      }
    }
  }

  trieFree(trie);
  return ret;
}

struct TrieNode {
  string word;
  unordered_map<char, TrieNode*> children;
  TrieNode() { this->word = ""; }
};

void insertTrie(TrieNode* root, const string& word) {
  TrieNode* node = root;
  for (auto c : word) {
    if (!node->children.count(c)) {
      node->children[c] = new TrieNode();
    }
    node = node->children[c];
  }
  node->word = word;
}

class Solution {
 public:
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  bool dfs(vector<vector<char>>& board, int x, int y, TrieNode* root,
           set<string>& res) {
    char ch = board[x][y];
    if (!root->children.count(ch)) {
      return false;
    }
    root = root->children[ch];
    if (root->word.size() > 0) {
      res.insert(root->word);
    }

    board[x][y] = '#';
    for (int i = 0; i < 4; ++i) {
      int nx = x + dirs[i][0];
      int ny = y + dirs[i][1];
      if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
        if (board[nx][ny] != '#') {
          dfs(board, nx, ny, root, res);
        }
      }
    }
    board[x][y] = ch;

    return true;
  }

  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    TrieNode* root = new TrieNode();
    set<string> res;
    vector<string> ans;

    for (auto& word : words) {
      insertTrie(root, word);
    }
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
        dfs(board, i, j, root, res);
      }
    }
    for (auto& word : res) {
      ans.emplace_back(word);
    }
    return ans;
  }
};