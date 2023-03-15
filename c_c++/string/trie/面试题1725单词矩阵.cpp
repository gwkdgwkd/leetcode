/*
给定一份单词的清单，设计一个算法，创建由字母组成的面积最大的矩形，
其中每一行组成一个单词(自左向右)，每一列也组成一个单词(自上而下)。
不要求这些单词在清单里连续出现，但要求所有行等长，所有列等高。
如果有多个面积最大的矩形，输出任意一个均可，一个单词可以重复使用。

示例1：
输入：["this", "real", "hard", "trh", "hea", "iar", "sld"]
输出：["this",
      "real",
      "hard"]

示例2：
输入：["aa"]
输出：["aa","aa"]

说明：
words.length <= 1000
words[i].length <= 100
数据保证单词足够随机
*/

#define NUM (26)
#define GETIDX(a) ((a) - 'a')
#define INVALID (1)
#define AGAIN (2)
#define OK (0)
typedef struct Node_ {
  int count;
  int len;
  char *w;
  struct Node_ *next[NUM];
} Node;
typedef struct Dic_ {
  Node node;
} Dic;
Dic g_root = {0};
int g_maxLen = 0;
int g_h = 0;
char **g_ret = NULL;
int *g_len = NULL;
void BuildDic(char **words, int wordsSize) {
  Node *node;
  int i;
  int j;
  char *w;
  int len;
  Node *tmp;

  for (i = 0; i < wordsSize; i++) {
    w = words[i];
    len = strlen(w);
    if (len > g_maxLen) {
      g_maxLen = len;
    }
    g_len[i] = len;
    node = &g_root.node;

    for (j = 0; j < len; j++) {
      if (node->next[GETIDX(w[j])] == NULL) {
        tmp = malloc(sizeof(Node));
        memset(tmp, 0, sizeof(Node));
        node->next[GETIDX(w[j])] = tmp;
        node = tmp;
      } else {
        node = node->next[GETIDX(w[j])];
      }
    }
    // printf("\r\n %s,%d", w, len);
    node->count++;
    node->len = len;
    node->w = w;
  }
}
Node *FindDic(char *w) {
  Node *node;
  int i;
  int len = strlen(w);

  node = &g_root.node;
  for (i = 0; i < len; i++) {
    if (node->next[GETIDX(w[i])] == NULL) {
      break;
    }

    node = node->next[GETIDX(w[i])];
  }

  if (i == len && node != NULL && node->count > 0) {
    return node;
  }

  return NULL;
}
bool IsExist(char *w, int len) {
  int i;
  Node *node;

  node = &g_root.node;
  for (i = 0; i < len; i++) {
    if (node->next[GETIDX(w[i])] == NULL) {
      return false;
    }

    node = node->next[GETIDX(w[i])];
  }

  return true;
}
int cmp(const void *a, const void *b) {
  char *aa = *(char **)a;
  char *bb = *(char **)b;
  int lenA;
  int lenB;

  lenA = strlen(aa);
  lenB = strlen(bb);

  if (lenA > lenB) {
    return -1;
  }

  if (lenA < lenB) {
    return 1;
  }

  return strcmp(aa, bb);
}
int Dfs(char **words, int size, char *w, int idx, int len) {
  int i;
  int j;
  char *word;
  int lenw;
  int ret;
  Node *node;
  int cnt = 0;
  int h;
  int start;
  int end;
  bool isok;

  if (idx == len) {
    // printf("\r\nidx == len,%d", g_h);
    for (i = 1; i < g_h; i++) {
      g_ret[i][len] = 0;
      node = FindDic(g_ret[i]);
      // if (node != NULL)
      // printf("%s,", node->w);
      if (node == NULL) {
        return AGAIN;
      }
    }

    return OK;
  }

  // printf("\r\n%d,%d", start, end);
  for (i = 0; i < size; i++) {
    word = words[i];
    if (word[0] != w[idx]) {
      continue;
    }
    // printf("<%s,%d>", word, idx);
    lenw = g_len[i];

    if (idx == 0) {
      // 搜寻最大长度，没有这个会导致横的能保证最长，但是竖的不是最优长度
      if (lenw < len) {
        break;
      }
      g_h = lenw;
    } else {
      if (lenw > g_h) {
        continue;
      } else if (lenw < g_h) {
        return AGAIN;
      }
    }

    for (j = 1; j < lenw; j++) {
      g_ret[j][idx] = word[j];
      // 每步都要查找字典树横向时候合法，这个可以剪枝很多，没有这个剪枝会超时
      isok = IsExist(g_ret[j], idx + 1);
      if (isok == false) {
        break;
      }
    }

    if (isok == false) {
      continue;
    }

    ret = Dfs(words, size, w, idx + 1, len);
    if (ret == OK) {
      return ret;
    }
  }

  return AGAIN;
}
char **maxRectangle(char **words, int wordsSize, int *returnSize) {
  int i;
  int len;
  int n;
  char ret;
  int rn = 0;

  g_h = 0;
  g_maxLen = 0;
  memset(&g_root, 0, sizeof(Dic));
  qsort(words, wordsSize, sizeof(char **), cmp);
  g_len = malloc(sizeof(int) * wordsSize);
  BuildDic(words, wordsSize);

  g_ret = malloc(sizeof(char *) * g_maxLen);

  for (i = 0; i < g_maxLen; i++) {
    g_ret[i] = malloc(sizeof(char) * (g_maxLen + 1));
  }

  for (i = 0; i < wordsSize; i++) {
    // printf("[%s]", words[i]);
    strcpy(g_ret[0], words[i]);
    g_h = strlen(words[i]);
    ret = Dfs(words, wordsSize, words[i], 0, g_h);
    if (ret == OK) {
      break;
    }
  }

  *returnSize = g_h;
  return g_ret;
}

class trie {
 public:
  bool isEnd = false;
  trie *next[26] = {NULL};
  void insert(string &s) {
    trie *cur = this;
    for (int i = 0; i < s.size(); ++i) {
      if (!cur->next[s[i] - 'a']) cur->next[s[i] - 'a'] = new trie();
      cur = cur->next[s[i] - 'a'];
    }
    cur->isEnd = true;
  }
};
class Solution {
  trie *t;
  vector<string> ans;
  vector<string> temp;

 public:
  vector<string> maxRectangle(vector<string> &words) {
    t = new trie();
    map<int, vector<string>> m;
    int maxlen = 0, maxarea = 0, area;
    for (auto &w : words) {
      t->insert(w);                         // 单词插入trie
      m[w.size()].push_back(w);             // 单词按长度分组
      maxlen = max(maxlen, int(w.size()));  // 最大单词长度
    }
    // 反向遍历，从长度大的开始
    for (auto it = m.rbegin(); it != m.rend(); ++it) {
      if (maxarea / (it->first) >= maxlen)
        break;  // 最长的单词*宽度 都不够大，这组不用找了
      temp.clear();
      area = 0;
      dfs(it->second, maxarea, maxlen, area);
    }
    return ans;
  }

  void dfs(vector<string> &wd, int &maxarea, int maxlen, int area) {
    if (wd[0].size() * maxlen <= maxarea)  // 找到的面积到极限了，退出吧
      return;  // 这个优化必须有，没有会超时
    vector<bool> res;
    for (int i = 0; i < wd.size(); ++i) {
      temp.push_back(wd[i]);
      res = isgood(temp);  // 是否合法
      if (res[0]) {        // 可以往下加单词
        area = temp.size() * temp[0].size();
        if (res[1] && area > maxarea) {  // 都是结束单词
          // 更新最大值
          maxarea = area;
          ans = temp;
        }
        dfs(wd, maxarea, maxlen, area);
      }
      // else//不能有else，有的话if内的dfs出来，没有回溯
      temp.pop_back();
    }
  }

  vector<bool> isgood(vector<string> &tp) {
    trie *cur;
    bool allend = true;
    int i, j, n = tp[0].size();
    for (j = 0; j < n; ++j)  // 按列在trie中检查
    {
      cur = t;
      for (i = 0; i < tp.size(); ++i) {
        if (!cur->next[tp[i][j] - 'a']) return {false, false};
        cur = cur->next[tp[i][j] - 'a'];
      }
      allend &= cur->isEnd;
    }
    // 可以继续插入、每个列向单词都在字典中
    return {true, allend};
  }
};