/*
给定一个整数n和一个无重复黑名单整数数组blacklist。
设计一种算法，从[0,n-1]范围内的任意整数中，
选取一个未加入黑名单blacklist的整数。
任何在上述范围内且不在黑名单blacklist中的整数都应该有同等的可能性被返回。
优化你的算法，使它最小化调用语言内置随机函数的次数。
实现Solution类:
Solution(int n, int[] blacklist)
初始化整数n和被加入黑名单blacklist的整数。
int pick()
返回一个范围为[0,n-1]且不在黑名单blacklist中的随机整数。

示例1：
输入
["Solution", "pick", "pick", "pick",
 "pick", "pick", "pick", "pick"]
[[7, [2, 3, 5]], [], [], [], [], [], [], []]
输出
[null, 0, 4, 1, 6, 1, 0, 4]

解释
Solution solution = new Solution(7, [2, 3, 5]);
solution.pick();
返回0，任何[0,1,4,6]的整数都可以。
注意，对于每一个pick的调用，
0、1、4和6的返回概率必须相等(即概率为1/4)。
solution.pick(); // 返回 4
solution.pick(); // 返回 1
solution.pick(); // 返回 6
solution.pick(); // 返回 1
solution.pick(); // 返回 0
solution.pick(); // 返回 4

提示:
1 <= n <= 10^9
0 <= blacklist.length <- min(10^5, n - 1)
0 <= blacklist[i] < n
blacklist中所有值都不同
pick最多被调用2 * 10^4次
*/

typedef struct {
  int key;
  int pos;
  UT_hash_handle hh;
} BlackHashData;

typedef struct {
  BlackHashData *data;
  int dataLen;
  int *nums;
  int numsLen;
} Solution;

Solution *solutionCreate(int n, int *blacklist, int blacklistSize) {
  Solution *obj = (Solution *)malloc(sizeof(Solution));
  obj->data = NULL;
  obj->dataLen = blacklistSize;
  obj->nums = (int *)malloc(sizeof(int) * n);
  obj->numsLen = n;

  for (int i = 0; i < blacklistSize; i++) {
    BlackHashData *b = (BlackHashData *)malloc(sizeof(BlackHashData));
    b->key = blacklist[i];
    b->pos = blacklist[i];
    HASH_ADD_INT(obj->data, key, b);
  }

  int sz = n - blacklistSize;
  int last = n - 1;
  for (int i = 0; i < blacklistSize; i++) {
    if (blacklist[i] >= sz) {
      continue;
    }
    BlackHashData *b = NULL;
    HASH_FIND_INT(obj->data, &blacklist[i], b);
    BlackHashData *s = NULL;
    HASH_FIND_INT(obj->data, &last, s);
    while (s != NULL) {
      last--;
      HASH_FIND_INT(obj->data, &last, s);
    }
    b->pos = last;
    last--;
  }
  return obj;
}

int solutionPick(Solution *obj) {
  int sz = obj->numsLen - obj->dataLen;
  int index = rand() % sz;
  BlackHashData *b = NULL;
  HASH_FIND_INT(obj->data, &index, b);
  if (b != NULL) {
    return b->pos;
  }
  return index;
}

void solutionFree(Solution *obj) {
  BlackHashData *s = NULL;
  BlackHashData *tmp = NULL;
  free(obj->nums);
  HASH_ITER(hh, obj->data, s, tmp) {
    HASH_DEL(obj->data, s);
    free(s);
  }
  free(obj);
}

// 二分查找
class Solution {
  int n;
  vector<int> b;

 public:
  Solution(int N, vector<int> blacklist) {
    n = N;
    sort(blacklist.begin(), blacklist.end());
    b = blacklist;
  }
  int pick() {
    int k = rand() % (n - b.size());
    int left = 0;
    int right = b.size() - 1;

    while (left < right) {
      int mid = (left + right + 1) / 2;
      if (b[mid] - mid > k)
        right = mid - 1;
      else
        left = mid;
    }
    return left == right && b[left] - left <= k ? k + left + 1 : k;
  }
};
