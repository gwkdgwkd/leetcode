/*
如果交换字符串X中的两个不同位置的字母，
使得它和字符串Y相等，那么称X和Y两个字符串相似。
如果这两个字符串本身是相等的，那它们也是相似的。
例如，"tars"和"rats"是相似的(交换0与2的位置)；
"rats"和"arts"也是相似的，但是"star"不与"tars"，
"rats"或"arts"相似。
总之，它们通过相似性形成了两个关联组：
{"tars", "rats", "arts"}和{"star"}。
注意，"tars"和"arts"是在同一组中，即使它们并不相似。
形式上，对每个组而言，要确定一个单词在组中，
只需要这个词和该组中至少一个单词相似。
给你一个字符串列表strs，
列表中的每个字符串都是strs中其它所有字符串的一个字母异位词。
请问strs中有多少个相似字符串组？

示例1：
输入：strs = ["tars","rats","arts","star"]
输出：2

示例2：
输入：strs = ["omv","ovm"]
输出：1

提示：
1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i]只包含小写字母。
strs中的所有单词都具有相同的长度，且是彼此的字母异位词。
*/

// 剑指OfferII117相似的字符串

// 并查集
int count;
int *parent;
int *size;
void UF(int n) {
  count = n;
  parent = (int *)malloc(sizeof(int) * n);
  size = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}
int Find(int x) {
  while (parent[x] != x) {
    parent[x] = parent[parent[x]];
    x = parent[x];
  }
  return x;
}
void Union(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  if (rootP == rootQ) return;

  if (size[rootP] > size[rootQ]) {
    parent[rootQ] = rootP;
    size[rootP] += size[rootQ];
  } else {
    parent[rootP] = rootQ;
    size[rootQ] += size[rootP];
  }
  count--;
}
bool Connected(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  return rootP == rootQ;
}
bool check(char *a, char *b, int len) {
  int num = 0;
  for (int i = 0; i < len; i++) {
    if (a[i] != b[i]) {
      num++;
      if (num > 2) {
        return false;
      }
    }
  }
  return true;
}
int numSimilarGroups(char **strs, int strsSize) {
  int m = strsSize;
  int n = strlen(strs[0]);

  UF(m);
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; j++) {
      if (Connected(i, j)) {
        continue;
      }
      if (check(strs[i], strs[j], n)) {
        Union(i, j);
      }
    }
  }

  return count;
}

class UF {
 public:
  UF(int n) : count(n) {
    parent.resize(n);
    size.resize(n);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
      size[i] = 1;
    }
  }
  void Union(int p, int q) {
    int rootP = Find(p);
    int rootQ = Find(q);

    if (rootP == rootQ) return;

    if (size[rootP] > size[rootQ]) {
      parent[rootQ] = rootP;
      size[rootP] += size[rootQ];
    } else {
      parent[rootP] = rootQ;
      size[rootQ] += size[rootP];
    }
    --count;
  }
  bool Connected(int p, int q) { return Find(p) == Find(q); }
  int Count() { return count; }

 private:
  int count;
  vector<int> parent;
  vector<int> size;
  int Find(int x) {
    while (parent[x] != x) {
      parent[x] = parent[parent[x]];
      x = parent[x];
    }
    return x;
  }
};

class Solution {
 public:
  bool check(const string &a, const string &b) {
    int la = a.size();
    int lb = b.size();
    if (la != lb) return false;

    int count = 0;
    for (int i = 0; i < la; ++i) {
      if (a[i] != b[i] && ++count > 2) {
        return false;
      }
    }

    return true;
  }
  int numSimilarGroups(vector<string> &strs) {
    int m = strs.size();
    UF uf(m);

    for (int i = 0; i < m - 1; ++i) {
      for (int j = i + 1; j < m; ++j) {
        if (uf.Connected(i, j)) {
          continue;
        }
        if (check(strs[i], strs[j])) {
          uf.Union(i, j);
        }
      }
    }
    return uf.Count();
  }
};