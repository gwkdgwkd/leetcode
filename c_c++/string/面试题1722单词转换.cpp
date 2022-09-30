/*
给定字典中的两个词，长度相等。
写一个方法，把一个词转换成另一个词，
但是一次只能改变一个字符。
每一步得到的新词都必须能在字典中找到。
编写一个程序，返回一个可能的转换序列。
如有多个可能的转换序列，你可以返回任何一个。

示例1：
输入：beginWord = "hit",
     endWord = "cog",
     wordList = ["hot","dot","dog","lot","log","cog"]
输出：["hit","hot","dot","lot","log","cog"]

示例2：
输入：beginWord = "hit"
     endWord = "cog"
     wordList = ["hot","dot","dog","lot","log"]
输出：[]
解释：endWord "cog"不在字典中，所以不存在符合要求的转换序列。
*/

bool isOneDiff(char *curWord, char *cmpWord) {
  int len1 = strlen(curWord);
  int sum = 0;
  for (int i = 0; i < len1; i++) {
    if (curWord[i] != cmpWord[i]) {
      sum++;
    }
  }
  if (sum == 1) {
    return true;
  }
  return false;
}
// 深度优先搜索
bool DFS(char *curWord, char *tarWord, char **retArr, int *arrLen,
         char **wordList, int wordListSize, int *avail) {
  // 如果与目标字符串相同了，说明找到了，返回true
  if (strcmp(curWord, tarWord) == 0) {
    return true;
  }
  // 为当前层次的字符串申请空间
  retArr[(*arrLen)] = (char *)malloc(sizeof(char) * (strlen(curWord) + 1));
  for (int i = 0; i < wordListSize; i++) {
    // 如果遍历到的字符串被遍历过或者不是相差一个字符就跳过
    if (avail[i] == -1 || !isOneDiff(curWord, wordList[i])) {
      continue;
    }
    // 如果只相差一个字符并且没有被遍历过就记录下来
    strcpy(retArr[(*arrLen)], wordList[i]);
    (*arrLen)++;
    // 并标记对应的位置
    avail[i] = -1;
    // 继续深度优先搜索
    bool isRight = DFS(wordList[i], tarWord, retArr, arrLen, wordList,
                       wordListSize, avail);
    if (isRight) {
      // 如果能找到对应的字符串就返回true
      return true;
    }
    // 否则就不记录该字符串，但是注意，字符串本身依旧是被标记过的
    (*arrLen)--;
  }
  // 都不满足就返回false
  return false;
}
char **findLadders(char *beginWord, char *endWord, char **wordList,
                   int wordListSize, int *returnSize) {
  // 用于标记的数组
  int *avail = (int *)malloc(sizeof(int) * wordListSize);
  for (int i = 0; i < wordListSize; i++) {
    avail[i] = i;
  }
  // 记录初始字符串
  char **retArr = (char **)malloc(sizeof(char *) * (wordListSize + 2));
  int retLen = 0;
  retArr[retLen] = (char *)malloc(sizeof(char) * (strlen(beginWord) + 1));
  strcpy(retArr[retLen], beginWord);
  retLen++;
  retArr[retLen] = (char *)malloc(sizeof(char) * (strlen(beginWord) + 1));
  // 开始遍历
  for (int i = 0; i < wordListSize; i++) {
    if (isOneDiff(beginWord, wordList[i])) {
      strcpy(retArr[retLen], wordList[i]);
      avail[i] = -1;
      retLen++;
      bool isRight = DFS(wordList[i], endWord, retArr, &retLen, wordList,
                         wordListSize, avail);
      if (isRight) {
        *returnSize = retLen;
        return retArr;
      }
      retLen--;
    }
  }
  // 如果不满足条件就返回空
  *returnSize = 0;
  return NULL;
}

class Solution {
 public:
  vector<string> findLadders(string beginWord, string endWord,
                             vector<string> &wordList) {
    us.clear();
    res.clear();
    res.push_back(beginWord);
    for (auto &e : wordList) {
      us.insert(e);
    }
    us.erase(beginWord);
    if (us.count(endWord)) {
      if (dfs(beginWord, endWord, endWord.size())) {
        return res;
      }
    }
    return {};
  }

  bool dfs(string &s, string &ew, int n) {
    if (s == ew) return true;
    for (int i = 0; i < n; ++i) {
      char c1 = s[i];
      for (char c = 'a'; c <= 'z'; ++c) {
        s[i] = c;
        if (us.count(s)) {
          us.erase(s);
          res.push_back(s);
          if (dfs(s, ew, n)) return true;
          res.pop_back();
        }
      }
      s[i] = c1;
    }
    return false;
  }

  vector<string> res;
  unordered_set<string> us;
};