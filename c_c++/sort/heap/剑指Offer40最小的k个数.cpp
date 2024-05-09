/*
输入整数数组arr，找出其中最小的k个数。
例如，输入4、5、1、6、2、7、3、8这8个数字，
则最小的4个数字是1、2、3、4。

示例1：
输入：arr = [3,2,1], k = 2
输出：[1,2]或者[2,1]

示例2：
输入：arr = [0,1,2,1], k = 1
输出：[0]

限制：
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000
*/

// 面试题1714最小K个数

// 小顶堆
void adjustHeap(int* arr, int top, int size) {
  int tmp = arr[top];
  for (int i = top * 2 + 1; i < size; i = 2 * i + 1) {
    if (i + 1 < size && arr[i] > arr[i + 1]) {
      ++i;
    }
    if (tmp < arr[i]) {
      break;
    }
    arr[top] = arr[i];
    top = i;
  }
  arr[top] = tmp;
}
void buildHeap(int* arr, int size) {
  for (int i = size / 2 - 1; i >= 0; --i) {
    adjustHeap(arr, i, size);
  }
}
int* getLeastNumbers(int* arr, int arrSize, int k, int* returnSize) {
  buildHeap(arr, arrSize);

  int* res = (int*)malloc(sizeof(int) * k);
  *returnSize = 0;
  int i = arrSize - 1;
  while ((*returnSize) < k) {
    res[(*returnSize)++] = arr[0];
    arr[0] = arr[i];
    adjustHeap(arr, 0, i);
    --i;
  }

  return res;
}

class Solution {
 public:
  vector<int> getLeastNumbers(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());
    vector<int> ans;
    while (k-- > 0) {
      ans.emplace_back(pq.top());
      pq.pop();
    }
    return ans;
  }
};

class Solution {
  void adjustHeap(vector<int>& arr, int parent, int len) {
    int tmp = arr[parent];
    for (int child = parent * 2 + 1; child < len; child = child * 2 + 1) {
      if (child + 1 < len && arr[child] > arr[child + 1]) {
        ++child;
      }
      if (tmp < arr[child]) {
        break;
      }
      arr[parent] = arr[child];
      parent = child;
    }
    arr[parent] = tmp;
  }

 public:
  vector<int> getLeastNumbers(vector<int>& arr, int k) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
      adjustHeap(arr, i, n);
    }

    vector<int> ans;
    for (int i = 1; i <= k; ++i) {
      ans.emplace_back(arr[0]);
      swap(arr[0], arr[n - i]);
      Adjust(arr, 0, n - i);
    }

    // for (int i = n - 1; i >= n - k; --i) {
    //   ans.emplace_back(arr[0]);
    //   arr[0] = arr[i];
    //   adjustHeap(arr, 0, i);
    // }

    return ans;
  }
};