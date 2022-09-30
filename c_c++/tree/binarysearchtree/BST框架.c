struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

// 1.遍历
void traverse(struct TreeNode *root) {
  // root需要做什么？
  // 在这做，其他的不用root操心，抛给框架。
  traverse(root.left);
  traverse(root.right);
}
void plusOne(TreeNode root) {
  if (root == NULL) return;
  root.val += 1;

  plusOne(root.left);
  plusOne(root.right);
}
bool isSameTree(struct TreeNode *root1, struct TreeNode *root2) {
  // 都为空的话，显然相同：
  if (root1 == NULL && root2 == NULL) return true;
  // 一个为空，一个非空，显然不同：
  if (root1 == NULL || root2 == NULL) return false;
  // 两个都非空，但val不一样也不行：
  if (root1->val != root2->val) return false;

  // root1和root2该比的都比完了，继续比子树：
  return isSameTree(root1->left, root2->left) &&
         isSameTree(root1->right, root2->right);
}

// 2.判断BST的合法性
// 按遍历的思路处理，不对。
// 不光要和子树根节点比较，而是要限制整个子树节点的范围。
// bool isValidBST(struct TreeNode *root) {
//   if (root == NULL) return true;
//   if (root.left != NULL && root.val <= root.left.val) return false;
//   if (root.right != NULL && root.val >= root.right.val) return false;
//   return isValidBST(root.left) && isValidBST(root.right);
// }
bool isValid(struct TreeNode *root, struct TreeNode *min,
             struct TreeNode *max) {
  if (root == NULL) return true;
  if (min != NULL && root->val <= min->val) return false;
  if (max != NULL && root->val >= max->val) return false;
  return isValidBST(root->left, min, root) &&
         isValidBST(root->right, root, max);
}
bool isValidBST(struct TreeNode *root) { return isValidBST(root, NULL, NULL); }

// 3.在BST中查找一个数是否存在
// 正确，但没有把BST左小右大的特性用上
bool isInBST(struct TreeNode *root, int target) {
  if (root == NULL) return false;
  if (root->val == target) return true;

  return isInBST(root->left, target) || isInBST(root->right, target);
}
bool isInBST(struct TreeNode *root, int target) {
  if (root == NULL) return false;
  if (root->val == target) return true;
  if (root->val < target) return isInBST(root->right, target);
  if (root->val > target) return isInBST(root->left, target);
}

// 4.在BST中插入一个数
struct TreeNode *insertIntoBST(struct TreeNode *root, int val) {
  // 找到空位置插入新节点
  if (root == NULL) {
    struct TreeNode *res = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    res->val = val;
    res->left = NULL;
    res->right = NULL;
    return res;
  }
  // if (root->val == val) BST中一般不会插入已存在元素
  if (root->val < val) root->right = insertIntoBST(root->right, val);
  if (root->val > val) root->left = insertIntoBST(root->left, val);
  return root;
}

// 5.在BST中删除一个数
struct TreeNode *getMin(struct TreeNode *node) {
  // BST最左边的就是最小的：
  while (node->left != NULL) node = node->left;
  return node;
}
struct TreeNode *deleteNode(struct TreeNode *root, int key) {
  if (root == NULL) return root;

  if (root->val == key) {  // 找到啦，进行删除
    /*
    // 删除节点的同时不能破坏BST的性质，有三种情况:
    // 情况1：恰好是末端节点，两个子节点都为空，那么它可以当场去世了。
    if (root->left == NULL && root->right == NULL) return NULL;
    // 情况2：只有一个非空子节点，那么它要让这个孩子接替自己的位置。
    if (root->left == NULL) return root->right;
    if (root->right == NULL) return root->left;
    //
    // 情况3：有两个子节点，麻烦了，为了不破坏BST的性质，
    // 必须找到左子树中最大的那个节点，或者右子树中最小的那个节点来接替自己。
    if (root->left != NULL && root->right != NULL) {
      // 找到右子树的最小节点
      struct TreeNode minNode = getMin(root->right);
      // 把root改成minNode
      root->val = minNode->val;
      // 转而去删除minNode
      root->right = deleteNode(root->right, minNode.val);
    }
    */
    // 这两个if把情况1和2都正确处理了
    if (root->left == NULL) return root->right;
    if (root->right == NULL) return root->left;
    // 处理情况3
    struct TreeNode *minNode = getMin(root->right);
    root->val = minNode->val;
    root->right = deleteNode(root->right, minNode->val);
  } else if (root->val > key) {
    root->left = deleteNode(root->left, key);
  } else if (root->val < key) {
    root->right = deleteNode(root->right, key);
  }
  return root;
}