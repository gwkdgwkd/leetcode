/*
如果序列X_1, X_2, ..., X_n满足下列条件，就说它是斐波那契式的：
n>=3，对于所有i+2<=n，都有X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列arr，找到arr中最长的斐波那契式的子序列的长度。
如果一个不存在，返回0，子序列是从原序列arr中派生出来的，
它从arr中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。
例如，[3, 5, 8]是[3, 4, 5, 6, 7, 8]的一个子序列

示例1：
输入：arr = [1,2,3,4,5,6,7,8]
输出：5
解释：最长的斐波那契式子序列为[1,2,3,5,8]。

示例2：
输入：arr = [1,3,7,11,12,14,18]
输出：3
解释：最长的斐波那契式子序列有[1,11,12]、[3,11,14]以及[7,11,18]。

提示：
3 <= arr.length <= 1000
1 <= arr[i] < arr[i + 1] <= 10^9
*/

// 剑指OfferII093最长斐波那契数列

typedef struct tagHashNode {
  int key;
  int i;
  struct tagHashNode *next;
} HashNode;
int HashFind(HashNode *head, int numSize, int key) {
  int idx = key % numSize;
  HashNode *node = head[idx].next;
  while (node) {
    if (node->key == key) {
      return node->i;
    }
    node = node->next;
  }
  return 0;
}
void HashAdd(HashNode *head, int numSize, int key, int i) {
  int idx = key % numSize;
  HashNode *node = &head[idx];
  while (node->next) {
    node = node->next;
  }

  HashNode *newNode = malloc(sizeof(HashNode));
  newNode->key = key;
  newNode->i = i;
  newNode->next = NULL;
  node->next = newNode;
}
int lenLongestFibSubseq(int *A, int ASize) {
  int hsize = ASize * 2.5;
  HashNode hn[hsize];
  memset(hn, 0, sizeof(hn));

  // dp[i][j]：表示以A[i],A[j]结尾的斐波那契数列的最大长度
  int dp[ASize * ASize];
  memset(dp, 0, sizeof(dp));

  int cnt = 0;
  int n;
  for (int i = 0; i < ASize; i++) {
    for (int j = 0; j < i; j++) {
      if ((A[i] - A[j] < A[j]) && (n = HashFind(hn, hsize, A[i] - A[j]))) {
        dp[j * ASize + i] = dp[(n - 1) * ASize + j] + 1;
        cnt < dp[j * ASize + i] && (cnt = dp[j * ASize + i]);
      }
    }
    HashAdd(hn, hsize, A[i], i + 1);
  }

  for (int i = 0; i < hsize; i++) {
    HashNode *pre = hn[i].next;
    while (pre) {
      HashNode *cur = pre->next;
      free(pre);
      pre = cur;
    }
  }
  return cnt ? cnt + 2 : 0;
}

// 超时
class Solution {
 public:
  int lenLongestFibSubseq(vector<int> &arr) {
    int n = arr.size();
    if (n == 0) {
      return 0;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        dp[i][j] = 2;
      }
    }

    int Max = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = i - 1; k >= 0; k--) {
          if (arr[k] + arr[i] == arr[j]) {
            dp[i][j] = max(dp[i][j], dp[k][i] + 1);
          }
        }
        Max = max(Max, dp[i][j]);
      }
    }
    return Max > 2 ? Max : 0;
    ;
  }
};

class Solution {
 public:
  int lenLongestFibSubseq(vector<int> &arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 2));

    unordered_map<int, int> iim;
    for (int i = 0; i < n; i++) {
      iim[arr[i]] = i;
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        int diff = arr[j] - arr[i];  // arr[iim[diff]] + arr[i] = arr[j]
        if (iim.count(diff)) {
          int index = iim[diff];
          if (index < i) {
            dp[i][j] = max(dp[i][j], dp[index][i] + 1);
            ans = max(ans, dp[i][j]);
          }
        }
      }
    }
    return ans > 2 ? ans : 0;
  }
};