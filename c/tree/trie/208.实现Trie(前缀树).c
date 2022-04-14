/*
Trie（发音类似"try"）或者说前缀树是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
请你实现Trie类：
Trie()初始化前缀树对象。
void insert(String word)向前缀树中插入字符串word。
boolean search(String word)
如果字符串word在前缀树中，返回true（即，在检索之前已经插入）；否则，返回false。
boolean startsWith(String prefix)
如果之前已经插入的字符串word的前缀之一为prefix，返回true；否则，返回false。

示例：
输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回True
trie.search("app");     // 返回False
trie.startsWith("app"); // 返回True
trie.insert("app");
trie.search("app");     // 返回True

提示：
1 <= word.length, prefix.length <= 2000
word和prefix仅由小写英文字母组成
insert、search和startsWith调用次数总计不超过3 * 10^4次
*/

// 字典树，又称为单词查找树，是一种树形结构，它是一种哈希树的变种。
// Trie，又称前缀树或字典树，是一棵有根树，其每个节点包含以下字段：
// 1.指向子节点的指针数组children。
// 2.布尔字段isEnd，表示该节点是否为字符串的结尾。

// 从字典树的根开始，插入字符串。对于当前字符对应的子节点，有两种情况：
// 1.子节点存在。沿着指针移动到子节点，继续处理下一个字符。
// 2.子节点不存在。
//   创建一个新的子节点，记录在children数组的对应位置上，然后沿着指针移动到子节点，继续搜索下一个字符。
// 3.重复以上步骤，直到处理字符串的最后一个字符，然后将当前节点标记为字符串的结尾。

// 从字典树的根开始，查找前缀。对于当前字符对应的子节点，有两种情况：
// 1.子节点存在。沿着指针移动到子节点，继续搜索下一个字符。
// 2.子节点不存在。说明字典树中不包含该前缀，返回空指针。
// 3.重复以上步骤，直到返回空指针或搜索完前缀的最后一个字符。

// 若搜索到了前缀的末尾，就说明字典树中存在该前缀。
// 此外，若前缀末尾对应节点的isEnd为真，则说明字典树中存在该字符串。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

typedef struct Trie {
  struct Trie* children[26];
  bool isEnd;
} Trie;
Trie* trieCreate() {
  Trie* ret = malloc(sizeof(Trie));
  memset(ret->children, 0, sizeof(ret->children));
  ret->isEnd = false;
  return ret;
}
void trieInsert(Trie* obj, char* word) {
  int n = strlen(word);
  for (int i = 0; i < n; i++) {
    int ch = word[i] - 'a';
    if (obj->children[ch] == NULL) {
      obj->children[ch] = trieCreate();
    }
    obj = obj->children[ch];
  }
  obj->isEnd = true;
}
bool trieSearch(Trie* obj, char* word) {
  int n = strlen(word);
  for (int i = 0; i < n; i++) {
    int ch = word[i] - 'a';
    if (obj->children[ch] == NULL) {
      return false;
    }
    obj = obj->children[ch];
  }
  return obj->isEnd;
}
bool trieStartsWith(Trie* obj, char* prefix) {
  int n = strlen(prefix);
  for (int i = 0; i < n; i++) {
    int ch = prefix[i] - 'a';
    if (obj->children[ch] == NULL) {
      return false;
    }
    obj = obj->children[ch];
  }
  return true;
}
void trieFree(Trie* obj) {
  for (int i = 0; i < 26; i++) {
    if (obj->children[i]) {
      trieFree(obj->children[i]);
    }
  }
  free(obj);
}

int main() {
  char* word = "nihao";
  char* prefix = "ni";

  Trie* obj = trieCreate();
  trieInsert(obj, word);
  bool ret = trieSearch(obj, word);
  printf("%d\n", ret);  // 1
  ret = trieStartsWith(obj, prefix);
  printf("%d\n", ret);  // 1
  char* prefix1 = "xxx";
  ret = trieStartsWith(obj, prefix1);
  printf("%d\n", ret);  // 0
  trieFree(obj);

  return 0;
}
