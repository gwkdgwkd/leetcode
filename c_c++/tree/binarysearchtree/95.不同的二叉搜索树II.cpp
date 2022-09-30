/*
给你一个整数n，请你生成并返回所有由n个节点组成，
且节点值从1到n互不相同的不同二叉搜索树。
可以按任意顺序返回答案。

示例1：
输入：n = 3
输出：[[1,null,2,null,3],[1,null,3,2],[2,1,3],
      [3,1,null,null,2],[3,2,null,1]]

示例2：
输入：n = 1
输出：[[1]]

提示：1 <= n <= 8
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

// 递归
struct TreeNode** buildTree(int start, int end, int* returnSize) {
  if (start > end) {
    (*returnSize) = 1;
    struct TreeNode** ret = malloc(sizeof(struct TreeNode*));
    ret[0] = NULL;
    return ret;
  }
  *returnSize = 0;
  struct TreeNode** allTrees = malloc(0);
  // 枚举可行根节点
  for (int i = start; i <= end; i++) {
    // 获得所有可行的左子树集合
    int leftTreesSize;
    struct TreeNode** leftTrees = buildTree(start, i - 1, &leftTreesSize);

    // 获得所有可行的右子树集合
    int rightTreesSize;
    struct TreeNode** rightTrees = buildTree(i + 1, end, &rightTreesSize);

    // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
    for (int left = 0; left < leftTreesSize; left++) {
      for (int right = 0; right < rightTreesSize; right++) {
        struct TreeNode* currTree = malloc(sizeof(struct TreeNode));
        currTree->val = i;
        currTree->left = leftTrees[left];
        currTree->right = rightTrees[right];

        (*returnSize)++;
        allTrees = realloc(allTrees, sizeof(struct TreeNode*) * (*returnSize));
        allTrees[(*returnSize) - 1] = currTree;
      }
    }
    free(rightTrees);
    free(leftTrees);
  }
  return allTrees;
}
struct TreeNode** generateTrees(int n, int* returnSize) {
  if (!n) {
    (*returnSize) = 0;
    return NULL;
  }
  return buildTree(1, n, returnSize);
}

class Solution {
 public:
  vector<TreeNode*> generateTrees(int start, int end) {
    if (start > end) {
      return {nullptr};
    }
    vector<TreeNode*> allTrees;
    // 枚举可行根节点：
    for (int i = start; i <= end; i++) {
      // 获得所有可行的左子树集合：
      vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
      // 获得所有可行的右子树集合：
      vector<TreeNode*> rightTrees = generateTrees(i + 1, end);
      // 从左子树集合中选出一棵左子树，
      // 从右子树集合中选出一棵右子树，拼接到根节点上：
      for (auto& left : leftTrees) {
        for (auto& right : rightTrees) {
          TreeNode* currTree = new TreeNode(i);
          currTree->left = left;
          currTree->right = right;
          allTrees.emplace_back(currTree);
        }
      }
    }
    return allTrees;
  }

  vector<TreeNode*> generateTrees(int n) {
    if (!n) {
      return {};
    }
    return generateTrees(1, n);
  }
};