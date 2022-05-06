/*
设计一个方法，找出任意指定单词在一本书中的出现频率。

你的实现应该支持如下操作：
WordsFrequency(book)构造函数，参数为字符串数组构成的一本书
get(word)查询指定单词在书中出现的频率

示例：
WordsFrequency wordsFrequency = new WordsFrequency({"i", "have", "an", "apple",
"he", "have", "a", "pen"});
wordsFrequency.get("you"); // 返回0，"you"没有出现过
wordsFrequency.get("have"); // 返回2，"have"出现2次
wordsFrequency.get("an"); // 返回1
wordsFrequency.get("apple"); // 返回1
wordsFrequency.get("pen"); // 返回1

提示：
book[i]中只包含小写字母
1 <= book.length <= 100000
1 <= book[i].length <= 10
get函数的调用次数不会超过100000
*/

#define ALPHBET_SIZE 26
typedef struct {
  int num;  // 用于记录每个单词出现多少次
  struct WordsFrequency* chlidren[ALPHBET_SIZE];  // 记录每个单词
} WordsFrequency;
WordsFrequency* creat() {
  WordsFrequency* wordsFrequency =
      (WordsFrequency*)malloc(sizeof(WordsFrequency));
  memset(wordsFrequency->chlidren, 0, sizeof(wordsFrequency->chlidren));
  wordsFrequency->num = 0;  // 每个单词出现次数默认值为0
  return wordsFrequency;
}
WordsFrequency* wordsFrequencyCreate(char** book, int bookSize) {
  WordsFrequency* obj = creat();  // 新生成树
  WordsFrequency* node;  // 生成一个节点，用于去遍历从头开始插入每个单词
  for (int i = 0; i < bookSize; i++) {
    node = obj;
    for (int j = 0; book[i][j] != '\0'; j++) {
      int ch = book[i][j] - 'a';
      if (node->chlidren[ch] ==
          NULL) {  // 如果这个字母不在，就插入新的子树，也就是字母
        node->chlidren[ch] = creat();
      }
      node = node->chlidren[ch];
    }
    (node->num)++;  // 这个单词已经插入了，将这个单词出现次数增一。
  }
  return obj;
}
int wordsFrequencyGet(WordsFrequency* obj, char* word) {
  for (int i = 0; word[i] != '\0'; i++) {
    int ch = word[i] - 'a';
    if (obj->chlidren[ch] ==
        NULL) {  // 如果该字母在树中没有出现，那么表示这个单词肯定没有出现，单词的出现次数为0；
      return 0;
    }
    obj = obj->chlidren[ch];
  }
  return obj->num;  // 如果该单词在树中，则返回该单词出现次数
}
void wordsFrequencyFree(WordsFrequency* obj) { free(obj); }