/*
给你一个变量对数组equations和一个实数值数组values作为已知条件，
其中equations[i] = [Ai, Bi]和values[i]共同表示等式Ai / Bi = values[i]。
每个Ai或Bi是一个表示单个变量的字符串。
另有一些以数组queries表示的问题，其中queries[j] = [Cj, Dj]表示第j个问题，
请你根据已知条件找出Cj / Dj = ?的结果作为答案。
返回 所有问题的答案。
如果存在某个无法确定的答案，则用-1.0替代这个答案。
如果问题中出现了给定的已知条件中没有出现的字符串，也需要用-1.0替代这个答案。
注意：输入总是有效的。你可以假设除法运算中不会出现除数为0的情况，且不存在任何矛盾的结果。

示例1：
输入：equations = [["a","b"],["b","c"]], 
     values = [2.0,3.0], 
     queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]

示例2：

输入：equations = [["a","b"],["b","c"],["bc","cd"]], 
     values = [1.5,2.5,5.0], 
     queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]

示例3：
输入：equations = [["a","b"]], 
     values = [0.5], 
     queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]

提示：
1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj由小写英文字母与数字组成
*/

// 并查集
typedef struct {
  char *a;
  char *b;
  double t;
  UT_hash_handle hh;
} Hash;

typedef struct {
  char *x;
  UT_hash_handle hh;
} Hash_x;
Hash *hash_table;
Hash_x *hash_x;
char *getParent(char *x, double *t) {
  *t = 1;
  Hash *p;
  do {
    HASH_FIND(hh, hash_table, x, strlen(x), p);
    if (p) {
      x = p->b;
      *t *= p->t;
    }
  } while (p);
  return x;
}
Hash_x *find_x(char *x) {
  Hash_x *p;
  HASH_FIND(hh, hash_x, x, strlen(x), p);
  return p;
}
void add_x(char *x) {
  Hash_x *p = find_x(x);
  if (!p) {
    p = malloc(sizeof(Hash_x));
    p->x = x;
    HASH_ADD_STR(hash_x, x, p);
  }
}
void merge(char *a, char *b, double c) {
  add_x(a);
  add_x(b);
  double ta, tb;
  char *ra = getParent(a, &ta);
  char *rb = getParent(b, &tb);
  if (strcmp(ra, rb) == 0) return;
  Hash *p = malloc(sizeof(Hash));
  p->a = ra;
  p->b = rb;
  // a / b = c, ta * ra / (tb * rb) = c; ra / rb = c * tb / ta
  p->t = c * tb / ta;
  HASH_ADD_STR(hash_table, a, p);
}
double _div(char *a, char *b) {
  if (!find_x(a) || !find_x(b)) return -1;
  double ta, tb;
  char *ra = getParent(a, &ta);
  char *rb = getParent(b, &tb);
  if (strcmp(ra, rb)) return -1;
  return ta / tb;
}
double *calcEquation(char ***equations, int equationsSize,
                     int *equationsColSize, double *values, int valuesSize,
                     char ***queries, int queriesSize, int *queriesColSize,
                     int *returnSize) {
  hash_table = NULL;
  hash_x = NULL;
  *returnSize = queriesSize;
  double *res = malloc(queriesSize * sizeof(double));
  for (int i = 0; i < equationsSize; ++i) {
    char *a = equations[i][0], *b = equations[i][1];
    double c = values[i];
    merge(a, b, c);
  }
  for (int i = 0; i < queriesSize; ++i) {
    char *a = queries[i][0];
    char *b = queries[i][1];
    res[i] = _div(a, b);
  }
  return res;
}