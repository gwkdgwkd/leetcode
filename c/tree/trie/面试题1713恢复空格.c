/*
哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。
像句子"I reset the computer. It still didn’t boot!"
已经变成了"iresetthecomputeritstilldidntboot"。
在处理标点符号和大小写之前，你得先把它断成词语。
当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。
假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。
注意：本题相对原题稍作改动，只需返回未识别的字符数

示例：
输入：
dictionary = ["looked","just","like","her","brother"]
sentence = "jesslookedjustliketimherbrother"
输出： 7
解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。

提示：
0 <= len(sentence) <= 1000
dictionary中总字符数不超过150000。
你可以认为dictionary和sentence中只包含小写字母。
*/

// 字典树
typedef struct Trie {
  struct Trie* next[26];
  bool isEnd;
} Trie;
void init(Trie** p) {
  *p = (Trie*)malloc(sizeof(Trie));
  (*p)->isEnd = false;
  memset((*p)->next, NULL, sizeof((*p)->next));
}
void insert(Trie* curPos, char* s) {
  int len = strlen(s);
  for (int i = len - 1; i >= 0; --i) {
    int t = s[i] - 'a';
    if (curPos->next[t] == NULL) {
      init(&curPos->next[t]);
    }
    curPos = curPos->next[t];
  }
  curPos->isEnd = true;
}
int respace(char** dictionary, int dictionarySize, char* sentence) {
  int n = strlen(sentence), inf = 0x3f3f3f3f;

  Trie* root;
  init(&root);
  for (int i = 0; i < dictionarySize; i++) {
    insert(root, dictionary[i]);
  }

  // dp[i]表示字符串的前i个字符的最少未匹配数。
  int dp[n + 1];
  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    // 假设当前我们已经考虑完了前i个字符了，对于前i+1个字符对应的最少未匹配数：
    // 第i + 1个字符未匹配，则dp[i + 1] = dp[i] + 1，即不匹配数加1;
    // 遍历前i个字符，若以其中某一个下标idx为开头、以第i+1个字符为结尾的字符串正好在词典里，
    // 则dp[i] = min(dp[i], dp[idx])更新dp[i]。
    dp[i] = dp[i - 1] + 1;

    Trie* curPos = root;
    for (int j = i; j >= 1; --j) {
      int t = sentence[j - 1] - 'a';
      if (curPos->next[t] == NULL) {
        break;
      } else if (curPos->next[t]->isEnd) {
        dp[i] = fmin(dp[i], dp[j - 1]);
      }
      if (dp[i] == 0) {
        break;
      }
      curPos = curPos->next[t];
    }
  }
  return dp[n];
}