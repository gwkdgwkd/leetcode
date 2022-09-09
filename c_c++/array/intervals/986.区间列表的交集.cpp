/*
给定两个由一些闭区间组成的列表，firstList和secondList，
其中firstList[i] = [starti,endi]而secondList[j] = [startj,endj]。
每个区间列表都是成对不相交的，并且已经排序。
返回这两个区间列表的交集。

形式上，闭区间[a,b]（其中a <= b）表示实数x的集合，而a <= x <= b。
两个闭区间的交集是一组实数，要么为空集，要么为闭区间。
例如，[1, 3]和[2, 4]的交集为[2, 3]。

示例2：
输入：firstList = [[0,2],[5,10],[13,23],[24,25]],
     secondList = [[1,5],[8,12],[15,24],[25,26]]
输出：[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]

示例2：
输入：firstList = [[1,3],[5,9]], secondList = []
输出：[]

示例3：
输入：firstList = [], secondList = [[4,8],[10,12]]
输出：[]

示例4：
输入：firstList = [[1,7]], secondList = [[3,10]]
输出：[[3,7]]

提示：
0 <= firstList.length, secondList.length <= 1000
firstList.length + secondList.length >= 1
0 <= starti < endi <= 10^9
endi < starti+1
0 <= startj < endj <= 10^9
endj < startj+1
*/
int** intervalIntersection(int** firstList, int firstListSize,
                           int* firstListColSize, int** secondList,
                           int secondListSize, int* secondListColSize,
                           int* returnSize, int** returnColumnSizes) {
  if (firstListSize == 0 || secondList == 0) {
    return NULL;
  }

  int resMaxLen = firstListSize + secondListSize;
  int** res = (int**)malloc(sizeof(int*) * resMaxLen);
  *returnSize = 0;
  *returnColumnSizes = (int*)malloc(sizeof(int) * resMaxLen);

  int f = 0;
  int s = 0;
  while (f < firstListSize && s < secondListSize) {
    // printf("first:%d %d, second:%d
    // %d\n",firstList[f][0],firstList[f][1],secondList[s][0],secondList[s][1]);
    // if (firstList[f][0] > secondList[s][1] ||
    //     firstList[f][1] < secondList[s][0]) {
    //   firstList[f][1] < secondList[s][1] ? f++ : s++;
    //   continue;
    // }
    // res[*returnSize] = (int*)malloc(sizeof(int) * 2);
    // res[*returnSize][0] = fmax(firstList[f][0], secondList[s][0]);
    // res[*returnSize][1] = fmin(firstList[f][1], secondList[s][1]);
    // (*returnSize)++;
    // firstList[f][1] < secondList[s][1] ? f++ : s++;
    int start = fmax(firstList[f][0], secondList[s][0]);
    int end = fmin(firstList[f][1], secondList[s][1]);
    if (start <= end) {
      res[*returnSize] = (int*)malloc(sizeof(int) * 2);
      res[*returnSize][0] = start;
      res[*returnSize][1] = end;
      (*returnSize)++;
    }
    firstList[f][1] < secondList[s][1] ? f++ : s++;
  }

  for (int i = 0; i < *returnSize; ++i) {
    (*returnColumnSizes)[i] = 2;
  }

  return res;
}

class Solution {
 public:
  vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList,
                                           vector<vector<int>>& secondList) {
    vector<vector<int>> res;
    int i1 = 0;
    int n1 = firstList.size();
    int i2 = 0;
    int n2 = secondList.size();

    while (i1 < n1 && i2 < n2) {
      int left = max(firstList[i1][0], secondList[i2][0]);
      int right = min(firstList[i1][1], secondList[i2][1]);
      if (left <= right) {
        res.push_back({left, right});
      }
      firstList[i1][1] < secondList[i2][1] ? ++i1 : ++i2;
    }

    return res;
  }
};