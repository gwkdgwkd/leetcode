/*
在英语中，我们有一个叫做词根(root)的概念，
可以词根后面添加其他一些词组成另一个较长的单词——我们称这个词为继承词(successor)。
例如，词根an，跟随着单词other(其他)，可以形成新的单词another(另一个)。
现在，给定一个由许多词根组成的词典dictionary和一个用空格分隔单词形成的句子sentence。
你需要将句子中的所有继承词用词根替换掉。
如果继承词有许多可以形成它的词根，则用最短的词根替换它。
你需要输出替换之后的句子。

示例1：
输入：dictionary = ["cat","bat","rat"],
sentence = "the cattle was rattled by the battery"
输出："the cat was rat by the bat"

示例2：
输入：dictionary = ["a","b","c"],
sentence = "aadsfasf absbs bbab cadsfafs"
输出："a a b c"

提示：
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
dictionary[i]仅由小写字母组成。
1 <= sentence.length <= 10^6
sentence仅由小写字母和空格组成。
sentence中单词的总量在范围[1, 1000]内。
sentence中每个单词的长度在范围[1, 1000]内。
sentence中单词之间由一个空格隔开。
sentence没有前导或尾随空格。
*/

// 剑指OfferII063替换单词

#define MAXSIZE 26
typedef struct TrieTree {
  bool isEnd;
  struct TrieTree *next[MAXSIZE];
} Trie;
Trie *trieCreate() {
  Trie *obj = (Trie *)malloc(sizeof(Trie));
  memset(obj->next, 0, sizeof(obj->next));
  obj->isEnd = false;
  return obj;
}
void trieInsert(Trie *obj, char *word) {
  Trie *node = obj;
  int wordLen = strlen(word);
  for (int i = 0; i < wordLen; i++) {
    int index = word[i] - 'a';
    if (node->next[index] == NULL) {
      node->next[index] = trieCreate();
    }
    node = node->next[index];
  }
  node->isEnd = true;
}
bool trieSearch(Trie *obj, char *word) {
  Trie *node = obj;
  int wordLen = strlen(word);
  for (int i = 0; i < wordLen; i++) {
    int index = word[i] - 'a';
    if (node->next[index] == NULL) {
      return node->isEnd;
    }
    node = node->next[index];
  }
  return true;
}
bool trieStartsWith(Trie *obj, char *prefix) {
  Trie *node = obj;
  int wordLen = strlen(prefix);
  for (int i = 0; i < wordLen; i++) {
    int index = prefix[i] - 'a';
    if (node->next[index] == NULL) {
      return false;
    }
    node = node->next[index];
  }

  return true;
}
void trieFree(Trie *obj) {
  for (int i = 0; i < 26; i++) {
    if (obj->next[i]) {
      trieFree(obj->next[i]);
    }
  }
  free(obj);
}
void trieSearchAndGet(Trie *obj, char *word, char *tmpChar) {
  Trie *node = obj;
  int wordLen = strlen(word);
  for (int i = 0; i < wordLen; i++) {
    int index = word[i] - 'a';
    if (node->next[index] == NULL) {
      if (node->isEnd == true) {  // 找到前缀
        strncpy(tmpChar, word, i);
        tmpChar[i] = '\0';
      } else {  // 没找到前缀
        strcpy(tmpChar, word);
        tmpChar[wordLen] = '\0';
      }
      return;
    }
    node = node->next[index];
  }
  strcpy(tmpChar, word);
  tmpChar[wordLen] = '\0';
}
int cmp(const void *_a, const void *_b) {
  const char *a = *(const char **)_a;
  const char *b = *(const char **)_b;
  return strlen(a) - strlen(b);
}
char *replaceWords(char **dictionary, int dictionarySize, char *sentence) {
  Trie *dicTree = trieCreate();
  char blank[2] = " ";
  qsort(dictionary, dictionarySize, sizeof(char *), cmp);
  for (int i = 0; i < dictionarySize; i++) {
    if (trieSearch(dicTree, dictionary[i]) == 0) {
      trieInsert(dicTree, dictionary[i]);
    }
  }

  char *ret = (char *)calloc(1000001, sizeof(char));
  char *left = NULL;
  char *p = NULL;
  p = strtok(sentence, " ");
  while (p != NULL) {
    char tmpChr[1001] = {0};
    trieSearchAndGet(dicTree, p, tmpChr);
    strcat(ret, tmpChr);
    strcat(ret, blank);

    p = strtok(NULL, " ");
  }
  int len = strlen(ret);
  ret[len - 1] = '\0';
  return ret;
}