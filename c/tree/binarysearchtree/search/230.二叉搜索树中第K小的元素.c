int i;
int ret;
void find(struct TreeNode* root, int k) {
  if (!root) return;

  find(root->left, k);
  if (i++ == k) {
    ret = root->val;
  }
  find(root->right, k);

  return;
}
int kthSmallest(struct TreeNode* root, int k) {
  i = 1;
  find(root, k);
  return ret;
}