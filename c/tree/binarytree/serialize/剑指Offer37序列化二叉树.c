/*
请实现两个函数，分别用来序列化和反序列化二叉树。
你需要设计一个算法来实现二叉树的序列化与反序列化。
这里不限定你的序列/反序列化算法执行逻辑，
你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

提示：输入输出格式与LeetCode目前使用的方式一致，详情请参阅LeetCode序列化二叉树的格式。
你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

示例：
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]

注意：本题与297题相同
*/

#define MAXSIZE 50000
void preorder(struct TreeNode* root, char* tree) {
  if (root == NULL) {
    sprintf(tree + strlen(tree), "#,");
    return;
  }
  sprintf(tree + strlen(tree), "%d,", root->val);
  preorder(root->left, tree);
  preorder(root->right, tree);
}

char* serialize(struct TreeNode* root) {
  char* tree = (char*)malloc(sizeof(char) * MAXSIZE);
  memset(tree, 0, sizeof(char) * MAXSIZE);

  preorder(root, tree);
  return tree;
}
struct TreeNode* createTree(char* tree, int* index) {
  if (tree[(*index)] == '#') {
    *index += 2;
    return NULL;
  }

  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = 0;
  int neg = 1;
  if (tree[(*index)] == '-') {
    neg = -1;
    (*index)++;
  }
  while (tree[*index] != ',') {
    root->val = root->val * 10 + tree[(*index)++] - '0';
  }
  (*index)++;
  root->val *= neg;

  root->left = createTree(tree, index);
  root->right = createTree(tree, index);
  return root;
}
struct TreeNode* deserialize(char* data) {
  int index = 0;
  return createTree(data, &index);
}