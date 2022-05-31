/*
给定两个整数n和k，返回范围[1, n]中所有可能的k个数的组合。
你可以按任何顺序返回答案。

示例1：
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

示例2：
输入：n = 1, k = 1
输出：[[1]]

提示：
1 <= n <= 20
1 <= k <= n
*/

// 剑指OfferII080含有k个元素的组合

// 回溯算法
// 回溯法也可以叫做回溯搜索法，它是⼀种搜索的⽅式。
// 回溯是递归的副产品，只要有递归就会有回溯。
// 回溯函数也就是递归函数，指的都是⼀个函数。
// 因为回溯的本质是穷举，穷举所有可能，然后选出我们想要的答案，如果想让回溯法⾼效⼀些，
// 可以加⼀些剪枝的操作，但也改不了回溯法就是穷举的本质。
// 回溯法解决的问题都可以抽象为树形结构，回溯法解决的都是在集合中递归查找⼦集，
// 集合的⼤⼩就构成了树的宽度，递归的深度，都构成的树的深度。
// 递归就要有终⽌条件，所以必然是⼀颗⾼度有限的树（N叉树）。
// 回溯法解决的问题都可以抽象为树形结构（N叉树），⽤树形结构来理解回溯就容易多了。
// 回溯是递归的副产品，只要有递归就会有回溯，所以回溯法也经常和⼆叉树遍历，
// 深度优先搜索混在⼀起，因为这两种⽅式都是⽤了递归。

// 回溯三部曲:
// 1.回溯函数模板返回值以及参数，回溯算法中函数返回值⼀般为void。
//   void backtracking(参数)
// 2.回溯函数终⽌条件，⼀般来说搜到叶⼦节点了，也就找到了满⾜条件的⼀条答案，把这个答案存放起来，并结束本层递归。
//   if (终⽌条件) {
//    存放结果;
//    return;
//   }
// 3.回溯搜索的遍历过程，回溯法⼀般是在集合中递归搜索，集合的⼤⼩构成了树的宽度，递归的深度构成的树的深度。
//   for (选择：本层集合中元素（树中节点孩⼦的数量就是集合的⼤⼩）) {
//    处理节点;
//    backtracking(路径，选择列表); // 递归
//    回溯，撤销处理结果
//   }

// 回溯算法模板框架如下：
// void backtracking(参数) {
//  if (终⽌条件) {
//    存放结果;
//    return;
//  }
//  for (选择：本层集合中元素（树中节点孩⼦的数量就是集合的⼤⼩）) {
//    处理节点;
//    backtracking(路径，选择列表); // 递归
//    回溯，撤销处理结果
//  }
// }
// for循环可以理解是横向遍历，backtracking（递归）就是纵向遍历

// 组合是不强调元素顺序的，排列是强调元素顺序。

// 定义两个全局变量，⼀个⽤来存放符合条件单⼀结果，⼀个⽤来存放符合条件结果的集合。
// 其实不定义这两个全局遍历也是可以的，把这两个变量放进递归函数的参数⾥，但函数⾥参数太多影响可读性。
int* path;
int pathSize;
int** result;
int resultSize;
// 每次从集合中选取元素，可选择的范围随着选择的进⾏⽽收缩，调整可选择的范围，就是要靠startIndex。
void backtracking(int n, int k, int startIndex) {
  if (pathSize == k) {
    result[resultSize] = (int*)malloc(sizeof(int) * pathSize);
    memcpy(result[resultSize], path, sizeof(int) * pathSize);
    // for (int i = 0; i < pathSize; ++i) {
    //   result[resultSize][i] = path[i];
    // }
    ++resultSize;
    return;
  }

  // 可以剪枝的地⽅就在递归中每⼀层的for循环所选择的起始位置。
  // 如果for循环选择的起始位置之后的元素个数已经不满足需要的元素个数了，那么就没有必要搜索了。
  // for(int i = startIndex; i <= n; ++i) {
  for (int i = startIndex; i <= n - (k - pathSize) + 1; ++i) {  // 剪枝
    path[pathSize++] = i;
    // printf("%*d[%d %d %d]\n", startIndex * 2, i, n, k, startIndex);
    backtracking(n, k, i + 1);
    pathSize--;
  }

  // 4 3
  // [[1,2,3],[1,2,4],[1,3,4],[2,3,4]]
  // 未剪枝：
  //  1[4 3 1]
  //    2[4 3 2]
  //      3[4 3 3]
  //      4[4 3 3]
  //    3[4 3 2]
  //        4[4 3 4]
  //    4[4 3 2]
  //  2[4 3 1]
  //      3[4 3 3]
  //        4[4 3 4]
  //      4[4 3 3]
  //  3[4 3 1]
  //        4[4 3 4]
  //  4[4 3 1]
  // 剪枝：
  //  1[4 3 1]
  //    2[4 3 2]
  //      3[4 3 3]
  //      4[4 3 3]
  //    3[4 3 2]
  //        4[4 3 4]
  //  2[4 3 1]
  //      3[4 3 3]
  //        4[4 3 4]

  return;
}
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
  path = (int*)malloc(sizeof(int) * k);
  result = (int**)malloc(sizeof(int*) * 10001);
  pathSize = resultSize = 0;
  backtracking(n, k, 1);
  *returnSize = resultSize;
  *returnColumnSizes = malloc(sizeof(int) * resultSize);
  for (int i = 0; i < resultSize; i++) {
    (*returnColumnSizes)[i] = k;
  }
  return result;
}

class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  void backtracking(int n, int k, int start) {
    if (path.size() == k) {
      ans.emplace_back(path);
      return;
    }
    // for(int i = start; i <= n; ++i) {
    for (int i = start; i <= n - (k - path.size()) + 1; ++i) {  // 剪枝
      path.emplace_back(i);
      backtracking(n, k, i + 1);
      path.pop_back();
    }
    return;
  }

 public:
  vector<vector<int>> combine(int n, int k) {
    backtracking(n, k, 1);
    return ans;
  }
};
