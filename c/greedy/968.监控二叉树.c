/*
给定一个二叉树，我们在树的节点上安装摄像头。
节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。
计算监控树的所有节点所需的最小摄像头数量。

示例1：
输入：[0,0,null,0,0]
输出：1
解释：如图所示，一台摄像头足以监控所有节点。

示例2：
输入：[0,0,null,0,null,0,null,null,0]
输出：2
解释：需要至少两个摄像头来监视树的所有节点。

提示：
给定树的节点数的范围是[1, 1000]。
每个节点的值都是0。
*/

// 二叉树树上的贪心算法
// 局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少！
int result;
int traversal(struct TreeNode* cur) {
  // 三个数字来表示：
  // 0：该节点无覆盖
  // 1：本节点有摄像头
  // 2：本节点有覆盖
  if (cur == NULL) return 2;
  int left = traversal(cur->left);    // 左
  int right = traversal(cur->right);  // 右

  if (left == 2 && right == 2) {
    // 情况1，左右节点都有覆盖
    return 0;
  } else if (left == 0 || right == 0) {
    // 情况2
    // left == 0 && right == 0 左右节点无覆盖
    // left == 1 && right == 0 左节点有摄像头，右节点无覆盖
    // left == 0 && right == 1 左节点有无覆盖，右节点摄像头
    // left == 0 && right == 2 左节点无覆盖，右节点覆盖
    // left == 2 && right == 0 左节点覆盖，右节点无覆盖
    result++;
    return 1;
  } else {
    // 情况3
    // left == 1 && right == 2 左节点有摄像头，右节点有覆盖
    // left == 2 && right == 1 左节点有覆盖，右节点有摄像头
    // left == 1 && right == 1 左右节点都有摄像头
    // 其他情况前段代码均已覆盖
    return 2;
  }
}
int minCameraCover(struct TreeNode* root) {
  result = 0;
  if (traversal(root) == 0) {  // root无覆盖
    result++;
  }
  return result;
}