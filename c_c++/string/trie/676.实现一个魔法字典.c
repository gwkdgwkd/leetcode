/*
设计一个使用单词列表进行初始化的数据结构，单词列表中的单词互不相同。
如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，
使得所形成的新单词存在于你构建的字典中。

实现MagicDictionary类：
MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组dictionary设定该数据结构，
dictionary中的字符串互不相同
bool search(String searchWord) 给定一个字符串searchWord，
判定能否只将字符串中一个字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。
如果可以，返回true；否则，返回false。

示例：
输入
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
输出
[null, null, false, true, false, false]
解释
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // 返回False
magicDictionary.search("hhllo"); // 将第二个'h'替换为'e'可以匹配，所以返回True
magicDictionary.search("hell"); // 返回False
magicDictionary.search("leetcoded"); // 返回False

提示：
1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i]仅由小写英文字母组成
dictionary中的所有字符串互不相同
1 <= searchWord.length <= 100
searchWord仅由小写英文字母组成
buildDict仅在search之前调用一次
最多调用100次search
*/

// 剑指OfferII064神奇的字典

#define MAX_LETTER 26
typedef struct trie {
  struct trie* next[MAX_LETTER];
  bool isEnd;
} MagicDictionary;
MagicDictionary* magicDictionaryCreate() {
  MagicDictionary* node = (MagicDictionary*)calloc(1, sizeof(MagicDictionary));
  return node;
}
void magicDictionaryBuildDict(MagicDictionary* obj, char** dict, int dictSize) {
  MagicDictionary* node = NULL;
  for (int i = 0; i < dictSize; i++) {
    node = obj;
    for (int j = 0; dict[i][j] != '\0'; j++) {
      char c = dict[i][j];
      if (node->next[c - 'a'] == NULL) {
        node->next[c - 'a'] = magicDictionaryCreate();
      }
      node = node->next[c - 'a'];
    }
    node->isEnd = true;
  }
}
// 查找剩下的word和剩下的字典树是否匹配
bool checkLeftWord(MagicDictionary* obj, char* leftWord) {
  MagicDictionary* leftNode = obj;
  for (int i = 0; leftWord[i] != '\0'; i++) {
    char c = leftWord[i];
    if (leftNode->next[c - 'a'] == NULL) {
      return false;
    }
    leftNode = leftNode->next[c - 'a'];
  }

  return leftNode->isEnd;
}
bool magicDictionarySearch(MagicDictionary* obj, char* word) {
  MagicDictionary* node = obj;
  for (int i = 0; word[i] != '\0'; i++) {
    char c = word[i];
    // 每个字母尝试一遍去掉这个单词其他是否一致
    for (int j = 0; j < 26; j++) {
      if (node->next[j] != NULL && j != word[i] - 'a') {
        if (checkLeftWord(node->next[j], word + i + 1) == true) {
          return true;
        }
      }
    }

    // 只有替换一次的机会, 下次再不一样就退出
    if (node->next[c - 'a'] == NULL) {
      break;
    }

    node = node->next[c - 'a'];
  }

  return false;
}
void magicDictionaryFree(MagicDictionary* obj) {
  MagicDictionary* node = obj;
  if (node == NULL) {
    return;
  }
  for (int i = 0; i < MAX_LETTER; i++) {
    if (node->next[i] != NULL) {
      magicDictionaryFree(node->next[i]);
    }
  }
  free(node);
}
