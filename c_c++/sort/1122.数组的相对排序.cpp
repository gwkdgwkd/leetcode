/*
给两个数组，arr1和arr2，arr2中的元素各不相同，arr2中的每个元素都出现在arr1中。
对arr1中的元素进行排序，使arr1中项的相对顺序和arr2中的相对顺序相同。
未在arr2中出现过的元素需要按照升序放在arr1的末尾。

示例1：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19]，
     arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

示例2：
输入：arr1 = [28,6,22,8,44,17]，
     arr2 = [22,28,8,6]
输出：[22,28,8,6,17,44]

提示：
1 <= arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2中的元素arr2[i]各不相同
arr2中的每个元素arr2[i]都出现在arr1中
*/

// 剑指OfferII075数组相对排序

// 自定义排序规则
#define MAXLEN 1001
int* hash;
int cmp(void* _a, void* _b) {
  int a = *((int*)_a);
  int b = *((int*)_b);
  int fa = hash[a];
  int fb = hash[b];

  if (fa == -1) {
    return fb == -1 ? a - b : 1;
  } else {
    return fb == -1 ? -1 : fa - fb;
  }
}
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size,
                       int* returnSize) {
  hash = (int*)malloc(sizeof(int) * MAXLEN);
  for (int i = 0; i < MAXLEN; ++i) {
    hash[i] = -1;
  }
  for (int i = 0; i < arr2Size; ++i) {
    hash[arr2[i]] = i;
  }

  qsort(arr1, arr1Size, sizeof(int), cmp);
  *returnSize = arr1Size;

  return arr1;
}

class Solution {
 public:
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int, int> rank;
    for (int i = 0; i < arr2.size(); ++i) {
      rank[arr2[i]] = i;
    }
    sort(arr1.begin(), arr1.end(), [&](int x, int y) {
      if (rank.count(x)) {
        return rank.count(y) ? rank[x] < rank[y] : true;
      } else {
        return rank.count(y) ? false : x < y;
      }
    });
    return arr1;
  }
};

// 计数排序
// 元素的范围为[0,1000]，这个范围不是很大，也可以考虑不基于比较的排序，例如计数排序
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size,
                       int* returnSize) {
  int upper = 0;
  for (int i = 0; i < arr1Size; i++) {
    upper = fmax(upper, arr1[i]);
  }
  int frequency[upper + 1];
  memset(frequency, 0, sizeof(frequency));
  for (int i = 0; i < arr1Size; i++) {
    frequency[arr1[i]]++;
  }
  int* ans = malloc(sizeof(int) * arr1Size);
  *returnSize = 0;
  for (int i = 0; i < arr2Size; i++) {
    int x = arr2[i];
    for (int j = 0; j < frequency[x]; j++) {
      ans[(*returnSize)++] = x;
    }
    frequency[x] = 0;
  }
  for (int x = 0; x <= upper; x++) {
    for (int i = 0; i < frequency[x]; i++) {
      ans[(*returnSize)++] = x;
    }
  }
  return ans;
}

class Solution {
 public:
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    int upper = *max_element(arr1.begin(), arr1.end());
    vector<int> frequency(upper + 1);
    for (int x : arr1) {
      ++frequency[x];
    }
    vector<int> ans;
    for (int x : arr2) {
      for (int i = 0; i < frequency[x]; ++i) {
        ans.push_back(x);
      }
      frequency[x] = 0;
    }
    for (int x = 0; x <= upper; ++x) {
      for (int i = 0; i < frequency[x]; ++i) {
        ans.push_back(x);
      }
    }
    return ans;
  }
};