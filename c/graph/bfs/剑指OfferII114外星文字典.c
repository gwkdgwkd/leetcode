/*
现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。
给定一个字符串列表words，作为这门语言的词典，words中的字符串已经按这门新语言的字母顺序进行了排序。
请你根据该词典还原出此语言中已知的字母顺序，并按字母递增顺序排列。
若不存在合法字母顺序，返回""。
若存在多种可能的合法字母顺序，返回其中任意一种顺序即可。
字符串s字典顺序小于字符串t有两种情况：
在第一个不同字母处，如果s中的字母在这门外星语言的字母顺序中位于t中字母之前，那么s的字典顺序小于t。
如果前面min(s.length,t.length)字母都相同，那么s.length<t.length时，s的字典顺序也小于t。

示例1：
输入：words = ["wrt","wrf","er","ett","rftt"]
输出："wertf"

示例2：
输入：words = ["z","x"]
输出："zx"

示例3：
输入：words = ["z","x","z"]
输出：""
解释：不存在合法字母顺序，因此返回 "" 。

提示：
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i]仅由小写英文字母组成

注意：本题与269题相同
*/

// 图 + BFS
#define MAX_NUM 27
int InitGrah(char** words, int wordsSize, int** grah) {
  int wCnt = 0;
  for (int i = 0; i < wordsSize; i++) {
    for (int j = 0; j < strlen(words[i]); j++) {
      int wd = words[i][j] - 'a';
      // 初始化words中的字母，对应26个字母存在则置1，同时保存出现的字母个数
      if (grah[wd][wd] == 0) {
        grah[wd][wd] = 1;
        wCnt++;
      }
    }

    if (wCnt == MAX_NUM) {
      break;
    }
  }

  for (int i = 0; i < wordsSize - 1; i++) {
    int len1 = strlen(words[i]);
    int len2 = strlen(words[i + 1]);
    int j = 0;
    // 根据规则一找到第一个不相等的字符，通过二位数组建立指向关系
    while (j < len1 && j < len2 && words[i][j] == words[i + 1][j]) {
      j++;
    }
    if (j < len1 && j < len2) {
      if (grah[words[i][j] - 'a'][words[i + 1][j] - 'a'] == 0) {
        grah[words[i][j] - 'a'][words[i + 1][j] - 'a'] = 1;
        // 被指向节点入度加一
        grah[words[i + 1][j] - 'a'][words[i + 1][j] - 'a']++;
      }
    } else if (j < len1) {
      return 0;
    }
  }

  return wCnt;
}
int GetResultByBFS(char** words, int wordsSize, int** grah, char* res) {
  // 根据字母关系关键图
  int ret = InitGrah(words, wordsSize, grah);
  if (ret == 0) {  // 非法输入顺序
    return 0;
  }

  int right = 0;
  int* que = (int*)malloc(sizeof(int) * MAX_NUM);
  for (int i = 0; i < MAX_NUM; i++) {
    if (grah[i][i] == 1) {
      que[right++] = i;
      grah[i][i] == 0;
    }
  }

  if (right == 0) {  // 循环依赖，没有入度为0的情况
    return 0;
  }

  int left = 0;
  int cnt = 0;
  while (left < right) {
    res[cnt++] = que[left] + 'a';
    for (int i = 0; i < MAX_NUM; i++) {
      if (grah[que[left]][i] == 0) {
        continue;
      }

      // 找到que[left]指向的节点，删除que[left]->i这条边，入度减一
      if (grah[que[left]][i] == 1) {
        grah[i][i]--;
        grah[que[left]][i] = 0;
      }

      if (grah[i][i] == 1) {  // 入度减一为0则入队列
        que[right++] = i;
      }
    }
    left++;
  }

  return (cnt == ret);
}
char* alienOrder(char** words, int wordsSize) {
  int** grah = (int**)malloc(sizeof(int*) * MAX_NUM);
  for (int i = 0; i < MAX_NUM; i++) {
    grah[i] = (int*)malloc(sizeof(int) * MAX_NUM);
    memset(grah[i], 0, sizeof(int) * MAX_NUM);
  }

  // 通过BFS获取结果
  char* res = (char*)malloc(sizeof(char) * MAX_NUM);
  memset(res, 0, sizeof(char) * MAX_NUM);
  if (GetResultByBFS(words, wordsSize, grah, res) == 0) {
    return "";
  }
  return res;
}