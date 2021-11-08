// 递归
void flatten(struct TreeNode* root) {
  if (!root) return;

  flatten(root->left);
  flatten(root->right);

  // 后序遍历位置，左右子树已经被拉平成一条链表
  struct TreeNode* l = root->left;
  struct TreeNode* r = root->right;

  // 将左子树作为右子树
  root->left = NULL;
  root->right = l;

  // 将原先的右子树接到当前右子树的末端
  struct TreeNode* p = root;
  while (p->right) {
    p = p->right;
  }

  p->right = r;

  return;
}

// 递归，前序遍历保存树节点到数组
struct TreeNode* array[10000];
int i;
void put_array(struct TreeNode* r) {
  if (r == NULL) {
    return;
  }
  array[i++] = r;
  put_array(r->left);
  put_array(r->right);
}
void flatten(struct TreeNode* root) {
  memset(array, 0, sizeof(array));
  i = 0;
  put_array(root);
  int j = 0;
  while (array[j] != NULL) {
    array[j]->left = NULL;
    array[j]->right = array[j + 1];
    j++;
  }
  return array[0];
}