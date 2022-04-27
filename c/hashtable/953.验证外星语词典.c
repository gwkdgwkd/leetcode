/*
某种外星语也使用英文小写字母，但可能顺序order不同。
字母表的顺序（order）是一些小写字母的排列。
给定一组用外星语书写的单词words，以及其字母表的顺序order，
只有当给定的单词在这种外星语中按字典序排列时，返回true；否则，返回false。

示例1：
输入：words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
输出：true
解释：在该语言的字母表中，'h'位于'l'之前，所以单词序列是按字典序排列的。

示例2：
输入：words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
输出：false
解释：在该语言的字母表中，'d'位于'l'之后，那么words[0]>words[1]，因此单词序列不是按字典序排列的。

示例3：
输入：words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
输出：false
解释：当前三个字符"app"匹配时，第二个字符串相对短一些，然后根据词典编纂规则"apple">"app"，
因为'l'>'∅'，其中'∅'是空白字符，定义为比任何其他字符都小（更多信息）。

提示：
1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
在words[i]和order中的所有字符都是英文小写字母。
*/

// 剑指OfferII034外星语言是否排序

bool isAlienSorted(char** words, int wordsSize, char* order) {
  // 对order进行hashSet转话
  int hashSet[26];
  int i, len = strlen(order);
  for (i = 0; i < len; i++) {
    hashSet[order[i] - 'a'] = i;
  }

  // 检测是否按字典排序顺序
  bool isAccord;
  int srcLen, dstLen;
  int srcIndex, dstIndex;
  for (i = 1; i < wordsSize; i++) {
    // 比较源字符串，和目标字符是否按字典顺序
    isAccord = false;
    srcLen = strlen(words[i - 1]);
    dstLen = strlen(words[i]);
    srcIndex = 0;
    dstIndex = 0;
    while (srcIndex < srcLen && dstIndex < dstLen) {
      if ((words[i - 1][srcIndex] != words[i][dstIndex])) {
        if (hashSet[words[i - 1][srcIndex] - 'a'] <
            hashSet[words[i][dstIndex] - 'a']) {
          isAccord = true;
          break;
        } else {
          return false;
        }
      }
      srcIndex++;
      dstIndex++;
    }

    if (!isAccord) {
      if (srcLen > dstLen) {
        return false;
      }
    }
  }
  return true;
}