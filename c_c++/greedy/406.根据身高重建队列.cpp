/*
假设有打乱顺序的一群人站成一个队列，数组people表示队列中一些人的属性（不一定按顺序）。
每个people[i]=[hi,ki]表示第i个人的身高为hi，前面正好有ki个身高大于或等于hi的人。
请你重新构造并返回输入数组people所表示的队列，返回的队列应该格式化为数组queue，
其中queue[j]=[hj,kj]是队列中第j个人的属性，queue[0]是排在队列前面的人。

示例1：
输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
解释：
编号为0的人身高为5，没有身高更高或者相同的人排在他前面。
编号为1的人身高为7，没有身高更高或者相同的人排在他前面。
编号为2的人身高为5，有2个身高更高或者相同的人排在他前面，即编号为0和1的人。
编号为3的人身高为6，有1个身高更高或者相同的人排在他前面，即编号为1的人。
编号为4的人身高为4，有4个身高更高或者相同的人排在他前面，即编号为0、1、2、3的人。
编号为5的人身高为7，有1个身高更高或者相同的人排在他前面，即编号为1的人。
因此[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]是重新构造后的队列。

示例2：
输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]

提示：
1 <= people.length <= 2000
0 <= hi <= 10^6
0 <= ki < people.length
题目数据确保队列可以被重建
*/

// 贪心算法
typedef struct peopleStr {
  int height;
  int hCount;
} peopleStr;
int heighCmp(const void* hCount1, const void* hCount2) {
  const peopleStr* l1 = *(const peopleStr**)hCount1;
  const peopleStr* l2 = *(const peopleStr**)hCount2;
  if (l1->height == l2->height) {
    return ((l1->hCount) - (l2->hCount));
  }
  return ((l2->height) - (l1->height));
}
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize,
                       int* returnSize, int** returnColumnSizes) {
  int heightCount;
  int* colSize = NULL;
  colSize = (int*)malloc(sizeof(int) * peopleSize);

  int** res = NULL;
  res = (int**)malloc(sizeof(int*) * peopleSize);

  qsort(people, peopleSize, sizeof(int*), heighCmp);

  for (int i = 0; i < peopleSize; i++) {
    heightCount = people[i][1];
    memmove(&res[heightCount + 1], &res[heightCount],
            (i - heightCount) * sizeof(int*));
    res[heightCount] = (int*)malloc(sizeof(int) * 2);
    res[heightCount][0] = people[i][0];
    res[heightCount][1] = people[i][1];
  }
  *returnColumnSizes = peopleColSize;
  *returnSize = peopleSize;
  return res;
}

class Solution {
 public:
  vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
      return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
    });
    vector<vector<int>> ans;
    for (const auto& p : people) {
      ans.insert(ans.begin() + p[1], p);
    }

    return ans;
  }
};