int sum;
void traversal(struct TreeNode* root) {
  if (!root) return;
  traversal(root->right);
  sum += root->val;
  root->val = sum;
  traversal(root->left);
  return;
}
struct TreeNode* bstToGst(struct TreeNode* root) {
  sum = 0;
  traversal(root);
  return root;
}