/*
字典wordList中从单词beginWord和endWord的转换序列
是一个按下述规格形成的序列beginWord -> s1 -> s2 -> ... -> sk：
1.每一对相邻的单词只差一个字母。
2.对于1 <= i <= k时，每个si都在wordList中。
  注意，beginWord不需要在wordList中。
3.sk == endWord
给你两个单词beginWord和endWord和一个字典wordList，
返回从beginWord到endWord的最短转换序列中的单词数目。
如果不存在这样的转换序列，返回0 。

示例1：
输入：beginWord = "hit", endWord = "cog", wordList =
["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是"hit"->"hot"->"dot"->"dog"->"cog", 返回它的长度5。

示例2：
输入：beginWord = "hit", endWord = "cog", wordList =
["hot","dot","dog","lot","log"]
输出：0
解释：endWord "cog"不在字典中，所以无法进行转换。

提示：
1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord、endWord和wordList[i]由小写英文字母组成
beginWord != endWord
wordList中的所有字符串互不相同
*/

// 广度优先搜索 + 优化建图
struct Trie {
  int ch[27];
  int val;
} trie[50001];
int size, nodeNum;
void insert(char* s, int num) {
  int sSize = strlen(s), add = 0;
  for (int i = 0; i < sSize; ++i) {
    int x = s[i] - '`';
    if (trie[add].ch[x] == 0) {
      trie[add].ch[x] = ++size;
      memset(trie[size].ch, 0, sizeof(trie[size].ch));
      trie[size].val = -1;
    }
    add = trie[add].ch[x];
  }
  trie[add].val = num;
}
int find(char* s) {
  int sSize = strlen(s), add = 0;
  for (int i = 0; i < sSize; ++i) {
    int x = s[i] - '`';
    if (trie[add].ch[x] == 0) {
      return -1;
    }
    add = trie[add].ch[x];
  }
  return trie[add].val;
}
int addWord(char* word) {
  if (find(word) == -1) {
    insert(word, nodeNum++);
  }
  return find(word);
}

// 把每个单词都抽象为一个点，如果两个单词可以只改变一个字母进行转换，那么说明他们之间有一条双向边。
// 因此我们只需要把满足转换条件的点相连，就形成了一张图。
int edge[30001][26];
int edgeSize[30001];
void addEdge(char* word) {
  int wordSize = strlen(word), id1 = addWord(word);
  for (int i = 0; i < wordSize; ++i) {
    char tmp = word[i];
    word[i] = '`';
    int id2 = addWord(word);
    edge[id1][edgeSize[id1]++] = id2;
    edge[id2][edgeSize[id2]++] = id1;
    word[i] = tmp;
  }
}
int ladderLength(char* beginWord, char* endWord, char** wordList,
                 int wordListSize) {
  size = nodeNum = 0;
  memset(trie[size].ch, 0, sizeof(trie[size].ch));
  trie[size].val = -1;
  memset(edgeSize, 0, sizeof(edgeSize));
  for (int i = 0; i < wordListSize; ++i) {
    addEdge(wordList[i]);
  }
  addEdge(beginWord);
  int beginId = find(beginWord), endId = find(endWord);
  if (endId == -1) {
    return 0;
  }

  int dis[nodeNum];
  memset(dis, -1, sizeof(dis));
  dis[beginId] = 0;

  int que[nodeNum];
  int left = 0, right = 0;
  que[right++] = beginId;
  while (left < right) {
    int x = que[left++];
    for (int i = 0; i < edgeSize[x]; ++i) {
      if (dis[edge[x][i]] == -1) {
        dis[edge[x][i]] = dis[x] + 1;
        if (edge[x][i] == endId) {
          return dis[edge[x][i]] / 2 + 1;
        }
        que[right++] = edge[x][i];
      }
    }
  }
  return 0;
}