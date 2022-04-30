/*
单词数组words的有效编码由任意助记字符串s和下标数组indices组成，且满足：
words.length == indices.length
助记字符串s以'#'字符结尾
对于每个下标indices[i]，
s的一个从indices[i]开始、到下一个'#'字符结束（但不包括'#'）的子字符串恰好与words[i]相等
给你一个单词数组words，返回成功对words进行编码的最小助记字符串s的长度。

示例1：
输入：words = ["time", "me", "bell"]
输出：10
解释：一组有效编码为s = "time#bell#"和indices = [0, 2, 5]。
words[0] = "time"，s开始于indices[0] = 0到下一个'#'结束的子字符串，
如加粗部分所示 "time#bell#"
words[1] = "me"，s开始于indices[1] = 2到下一个'#'结束的子字符串，
如加粗部分所示 "time#bell#"
words[2] = "bell"，s开始于indices[2] = 5到下一个'#'结束的子字符串，
如加粗部分所示 "time#bell#"

示例2：
输入：words = ["t"]
输出：2
解释：一组有效编码为s = "t#"和indices = [0]。

提示：
1 <= words.length <= 2000
1 <= words[i].length <= 7
words[i]仅由小写字母组成
*/

// 剑指OfferII065最短的单词编码

#define LEN 26
typedef struct Trie {
  struct Trie* children[LEN];
  bool isEnd;
} Trie;
Trie* trieCreate() { return (Trie*)calloc(1, sizeof(Trie)); }
void trieInsert(Trie* obj, char* word) {
  int len = strlen(word);
  for (int i = 0; i < len; ++i) {
    int c = word[i] - 'a';
    if (obj->children[c] == NULL) {
      obj->children[c] = trieCreate();
    }
    obj = obj->children[c];
  }
  obj->isEnd = true;
}
bool trieSearch(Trie* obj, char* word) {
  int len = strlen(word);
  for (int i = 0; i < len; ++i) {
    int c = word[i] - 'a';
    if (obj->children[c] == NULL) {
      return false;
    }
    obj = obj->children[c];
  }

  return obj->isEnd;
}
bool trieStartsWith(Trie* obj, char* prefix) {
  int len = strlen(prefix);
  for (int i = 0; i < len; ++i) {
    int c = prefix[i] - 'a';
    if (obj->children[c] == NULL) {
      return false;
    }
    obj = obj->children[c];
  }

  return true;
}
void trieFree(Trie* obj) {
  for (int i = 0; i < LEN; ++i) {
    if (obj->children[i]) {
      trieFree(obj->children[i]);
    }
  }
  free(obj);
}
int cmp(char** a, char** b) {
  char* x = *a;
  char* y = *b;
  return strcmp(y, x);
}
void reverse(char* str) {
  int left = 0;
  int right = strlen(str) - 1;
  while (left < right) {
    char tmp = str[left];
    str[left] = str[right];
    str[right] = tmp;
    ++left;
    --right;
  }
}
int minimumLengthEncoding(char** words, int wordsSize) {
  for (int i = 0; i < wordsSize; ++i) {
    reverse(words[i]);
  }
  // 倒序排序，排在后面的元素可能是前面元素的前缀，可以不统计了
  qsort(words, wordsSize, sizeof(char*), cmp);
  Trie* obj = trieCreate();
  int res = 0;
  for (int i = 0; i < wordsSize; ++i) {
    if (trieStartsWith(obj, words[i]) == false) {
      res += strlen(words[i]) + 1;
    }
    // if(trieSearch(obj,words[i]) == false) {
    trieInsert(obj, words[i]);
    // }
  }

  return res;
}