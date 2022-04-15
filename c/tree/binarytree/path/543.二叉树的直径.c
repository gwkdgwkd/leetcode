/*
给定一棵二叉树，你需要计算它的直径长度。
一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
这条路径可能穿过也可能不穿过根结点。

示例:
给定二叉树
          1
         / \
        2   3
       / \     
      4   5    

返回3, 它的长度是路径[4,2,1,3]或者[5,2,1,3]。

注意：两结点之间的路径长度是以它们之间边的数目表示。
*/

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int len;
int dfs(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }

  int left = dfs(root->left);
  int right = dfs(root->right);
  len = fmax(len, left + right + 1);
  return fmax(left, right) + 1;
}
int diameterOfBinaryTree(struct TreeNode* root) {
  len = 1;
  dfs(root);
  return len - 1;  // 路径的长度为该路径经过的节点数减1
}