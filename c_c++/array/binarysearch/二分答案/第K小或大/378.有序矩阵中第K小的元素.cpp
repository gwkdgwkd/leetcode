/*
给一个nxn矩阵matrix，其中每行和每列元素均按升序排序，找到矩阵中第k小的元素。
请注意，它是排序后的第k小元素，而不是第k个不同的元素。
必须找到一个内存复杂度优于O(n^2)的解决方案。

示例1：
输入：matrix = [[1, 5, 9],
               [10,11,13],
               [12,13,15]], k = 8
输出：13
解释：矩阵中的元素为[1,5,9,10,11,12,13,13,15]，第8小元素是13

示例2：
输入：matrix = [[-5]], k = 1
输出：-5

提示：
n == matrix.length
n == matrix[i].length
1 <= n <= 300
-10^9 <= matrix[i][j] <= 10^9
题目数据保证matrix中的所有行和列都按非递减顺序排列
1 <= k <= n^2

进阶：
你能否用一个恒定的内存(即O(1)内存复杂度)来解决这个问题?
你能在O(n)的时间复杂度下解决这个问题吗?
*/

// 直接排序，没有利用矩阵性质
// 时间复杂度：O(n^2log⁡n)
// 空间复杂度：O(n^2)
int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
int kthSmallest(int **matrix, int matrixSize, int *matrixColSize, int k) {
  int *rec = (int *)malloc(matrixSize * matrixSize * sizeof(int));

  int num = 0;
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixColSize[i]; j++) {
      rec[num++] = matrix[i][j];
    }
  }
  qsort(rec, num, sizeof(int), cmp);

  return rec[k - 1];
}

// 归并排序，只使用了矩阵一部分性质
// 时间复杂度：O(klogn)
// 空间复杂度：O(n)
typedef struct point {
  int val, x, y;
} point;
bool cmp(point a, point b) { return a.val >= b.val; }
void swap(point *a, point *b) {
  point t = *a;
  *a = *b, *b = t;
}
void push(point heap[], int *size, point *p) {
  heap[++(*size)] = *p;
  int s = (*size);
  while (s > 1) {
    if (cmp(heap[s], heap[s >> 1])) {
      break;
    }
    swap(&heap[s], &heap[s >> 1]);
    s >>= 1;
  }
}
void pop(point heap[], int *size) {
  heap[1] = heap[(*size)--];
  int p = 1, s = 2;
  while (s <= (*size)) {
    if (s < (*size) && !cmp(heap[s + 1], heap[s])) {
      s++;
    }
    if (cmp(heap[s], heap[p])) {
      break;
    }
    swap(&heap[s], &heap[p]);
    p = s, s = p << 1;
  }
}
int kthSmallest(int **matrix, int matrixSize, int *matrixColSize, int k) {
  point heap[matrixSize + 1];
  int size = 0;
  for (int i = 0; i < matrixSize; i++) {
    point p = {matrix[i][0], i, 0};
    push(heap, &size, &p);
  }
  for (int i = 0; i < k - 1; i++) {
    point now = heap[1];
    pop(heap, &size);
    if (now.y != matrixSize - 1) {
      point p = {matrix[now.x][now.y + 1], now.x, now.y + 1};
      push(heap, &size, &p);
    }
  }
  return heap[1].val;
}

// 二分查找，使用了矩阵全部性质
// 时间复杂度：O(nlog(r−l))
// 空间复杂度：O(1)
bool check(int **matrix, int mid, int k, int n) {
  int i = n - 1;
  int j = 0;
  int num = 0;  // 表示矩阵中小于等于mid的元素个数
  while (i >= 0 && j < n) {
    if (matrix[i][j] <= mid) {
      num += i + 1;
      j++;
    } else {
      i--;
    }
  }
  return num >= k;
}
int kthSmallest(int **matrix, int matrixSize, int *matrixColSize, int k) {
  int left = matrix[0][0];
  int right = matrix[matrixSize - 1][matrixSize - 1];
  while (left < right) {
    int mid = left + ((right - left) >> 1);
    if (check(matrix, mid, k, matrixSize)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

class Solution {
 public:
  int kthSmallest(vector<vector<int>> &matrix, int k) {
    int m = matrix.size();
    int n = matrix[0].size();

    // 判断matrix中小于item的元素个数是否大于等于k个
    auto check = [&](int item) -> bool {
      // 挑选左下角的元素为第一个与item比较
      int i = n - 1;
      int j = 0;
      int num = 0;  // 表示矩阵中小于等于mid的元素个数
      while (i >= 0 && j < n) {
        if (matrix[i][j] <= item) {  // 如果左下角的元素小于等于item
          num += i + 1;  // 证明左边这列的元素都小于item，num加上i+1个
          j++;           // j右移，下次判断右边一列最下面的元素
        } else {
          i--;  // 左下角的元素大于item，行标向上移动
        }
      }
      return num >= k;
    };

    int left = matrix[0][0];
    int right = matrix[m - 1][n - 1];

    // while (left < right) {
    //   int mid = left + (right - left) / 2;
    //   if (check(mid)) {
    //     right = mid;
    //   } else {
    //     left = mid + 1;
    //   }
    // }
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};
