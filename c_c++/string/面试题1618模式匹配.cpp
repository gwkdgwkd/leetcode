/*
你有两个字符串，即pattern和value。
pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。
例如，字符串"catcatgocatgo"匹配模式"aabab"，
其中"cat"是"a"，"go"是"b"，
该字符串也匹配像"a"、"ab"和"b"这样的模式。
但需注意"a"和"b"不能同时表示相同的字符串。
编写一个方法判断value字符串是否匹配pattern字符串。

示例1：
输入：pattern = "abba", value = "dogcatcatdog"
输出：true

示例2：
输入：pattern = "abba", value = "dogcatcatfish"
输出：false

示例3：
输入：pattern = "aaaa", value = "dogcatcatdog"
输出：false

示例4：
输入：pattern = "abba", value = "dogdogdogdog"
输出：true
解释："a"="dogdog",b=""，反之也符合规则

提示：
1 <= len(pattern) <= 1000
0 <= len(value) <= 1000
你可以假设pattern只包含字母"a"和"b"，value仅包含小写字母。
*/

typedef struct {
  char s;
  char *word;
} mystyle;
int camp1(const void *a, const void *b) {
  return (*(mystyle *)a).s > (*(mystyle *)b).s ? 1 : -1;
}
int camp2(const void *a, const void *b) {
  return strcmp((*(mystyle *)a).word, (*(mystyle *)b).word) > 0 ? 1 : -1;
}
bool find1(mystyle *hash, int index) {
  mystyle help[index + 1];
  memcpy(help, hash, (index + 1) * sizeof(mystyle));
  qsort(help, (index + 1), sizeof(mystyle), camp1);
  for (int i = 0; i < index; ++i) {
    if (help[i].s != help[i + 1].s) continue;
    int len1 = strlen(help[i].word);
    int len2 = strlen(help[i + 1].word);
    if (len1 != len2) return false;
    if (len1 == 0 && len2 == 0)
      continue;
    else {
      if (strcmp(help[i].word, help[i + 1].word) != 0) return false;
    }
  }
  return true;
}
bool find2(mystyle *hash, int index) {
  mystyle help[index + 1];
  memcpy(help, hash, (index + 1) * sizeof(mystyle));
  qsort(help, (index + 1), sizeof(mystyle), camp1);
  for (int i = 0; i < index; ++i) {
    if (strcmp(hash[i].word, hash[i + 1].word) != 0) continue;
    if (hash[i].s != hash[i + 1].s) return false;
  }
  return true;
}
bool patternMatching(char *pattern, char *value) {
  int lenp = strlen(pattern);
  int lenv = strlen(value);
  if (lenp == 0) {
    if (lenv == 0)
      return true;
    else
      return false;
  }
  int counta = 0;
  int countb = 0;
  int index = 0;
  for (int i = 0; i < lenp; ++i) {
    if (pattern[i] == 'a')
      counta++;
    else
      countb++;
  }
  if (lenv == 0) {
    if (counta == 0 || countb == 0) return true;
    return false;
  }
  int count[lenv + 1][2];
  memset(count, 0, sizeof(count));
  int lena = counta == 0 ? 0 : (lenv / counta + 1);
  int lenb = countb == 0 ? 0 : (lenv / countb + 1);
  int pos = 0;
  for (int i = 0; i <= lena; ++i) {
    for (int j = 0; j <= lenb; ++j) {
      if (counta * i + countb * j == lenv) {
        count[pos][0] = i;
        count[pos++][1] = j;
      }
    }
  }
  mystyle hash[lenp];
  memset(hash, 0, sizeof(hash));
  for (int i = 0; i < pos; ++i) {
    int pre = 0;
    for (int j = 0; j < lenp; ++j) {
      hash[j].s = pattern[j];
      hash[j].word = (char *)malloc(1001 * sizeof(char));
      if (hash[j].s == 'a') {
        memcpy(hash[j].word, value + pre, count[i][0] * sizeof(char));
        hash[j].word[count[i][0]] = '\0';
        pre += count[i][0];
      } else {
        memcpy(hash[j].word, value + pre, count[i][1] * sizeof(char));
        hash[j].word[count[i][1]] = '\0';
        pre += count[i][1];
      }
    }
    if (find1(hash, lenp - 1) && find2(hash, lenp - 1)) return true;
  }
  return false;
}

class Solution {
 public:
  bool patternMatching(string pattern, string value) {
    int count_a = 0, count_b = 0;
    for (char ch : pattern) {
      if (ch == 'a') {
        ++count_a;
      } else {
        ++count_b;
      }
    }
    if (count_a < count_b) {
      swap(count_a, count_b);
      for (char &ch : pattern) {
        ch = (ch == 'a' ? 'b' : 'a');
      }
    }
    if (value.empty()) {
      return count_b == 0;
    }
    if (pattern.empty()) {
      return false;
    }
    for (int len_a = 0; count_a * len_a <= value.size(); ++len_a) {
      int rest = value.size() - count_a * len_a;
      if ((count_b == 0 && rest == 0) ||
          (count_b != 0 && rest % count_b == 0)) {
        int len_b = (count_b == 0 ? 0 : rest / count_b);
        int pos = 0;
        bool correct = true;
        string value_a, value_b;
        for (char ch : pattern) {
          if (ch == 'a') {
            string sub = value.substr(pos, len_a);
            if (!value_a.size()) {
              value_a = move(sub);
            } else if (value_a != sub) {
              correct = false;
              break;
            }
            pos += len_a;
          } else {
            string sub = value.substr(pos, len_b);
            if (!value_b.size()) {
              value_b = move(sub);
            } else if (value_b != sub) {
              correct = false;
              break;
            }
            pos += len_b;
          }
        }
        if (correct && value_a != value_b) {
          return true;
        }
      }
    }
    return false;
  }
};
