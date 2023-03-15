/*
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
如果是则返回true，否则返回false，假设输入的数组的任意两个数字都互不相同。

参考以下这颗二叉搜索树：
     5
    / \
   2   6
  / \
 1   3

示例1：
输入：[1，6，3，2，5]
输出：false

示例2：
输入：[1，3，2，6，5]
输出：true

提示：数组长度 <= 1000
*/

// 递归
// 时间复杂度：O(N^2)
// 空间复杂度：O(N)
bool dfs(int* nums, int left, int right) {
  if (left >= right) {
    return true;
  }

  // 数组中最后一个数字nums[right]就是根节点
  // 从前往后找到第一个比根大的数字mid，
  // 那么[mid，right-1]是右子树，[left，mid-1]是左子树
  int mid = left;
  while (nums[mid] < nums[right]) {
    ++mid;
  }

  int i = mid;
  while (i < right) {  // 遍历右子树
    // 如果右子树中有比根小的元素，那么不是二叉搜索树
    if (nums[i] < nums[right]) {
      return false;
    }
    ++i;
  }

  // 递归地判断左子树和右子树
  return dfs(nums, left, mid - 1) && dfs(nums, mid, right - 1);
}
bool verifyPostorder(int* postorder, int postorderSize) {
  return dfs(postorder, 0, postorderSize - 1);
}

/*
       10
      /  \
     8    12
    / \   / \
   5   9 11 13
  / \
 3   6
*/
// 后序：[3，6，5，9，8，11，13，12，10]
// 逆序：[10，12，13，11，8，9，5，6，3]

// 单调栈
// 时间复杂度：O(N)
// 空间复杂度：O(N)
bool verifyPostorder(int* postorder, int postorderSize) {
  if (postorderSize == 0) return true;
  int stack[postorderSize];
  int top = 0;
  int parent = INT_MAX;

  // 后序遍历的倒序：
  // 1.挨着的两个数如果arr[i]<arr[i+1]，
  //   那么arr[i+1]一定是arr[i]的右子节点
  // 2.如果arr[i]>arr[i+1]，
  //   那么arr[i+1]一定是arr[0]……arr[i]中某个节点的左子节点，
  //   并且这个值是大于arr[i+1]中最小的

  // 遍历数组的所有元素，如果栈为空，就把当前元素压栈。
  // 如果栈不为空，并且当前元素大于栈顶元素，说明是升序的，
  // 那么就说明当前元素是栈顶元素的右子节点，
  // 就把当前元素压栈，如果一直升序，就一直压栈。
  // 当前元素小于栈顶元素，说明是倒序的，
  // 说明当前元素是某个节点的左子节点，
  // 我们目的是要找到这个左子节点的父节点，就让栈顶元素出栈，
  // 直到栈为空或者栈顶元素小于当前值为止，
  // 其中最后一个出栈的就是当前元素的父节点。

  for (int i = postorderSize - 1; i >= 0; i--) {
    int cur = postorder[i];
    // 当如果前节点小于栈顶元素，说明栈顶元素和当前值构成了倒序，
    // 说明当前节点是前面某个节点的左子节点，要找到他的父节点：
    while (top > 0 && stack[top - 1] > cur) {
      parent = stack[top - 1];
      --top;
    }

    // 只要遇到了某一个左子节点，才会执行上面的代码，
    // 才会更新parent的值，否则parent就是一个非常大的值，
    // 也就是说如果一直没有遇到左子节点，那么右子节点可以非常大：
    if (cur > parent) return false;
    // 入栈
    stack[top++] = cur;
  }
  return true;
}

class Solution {
 public:
  bool dfs(vector<int>& postorder, int left, int right) {
    if (left >= right) {
      return true;
    }
    // 左子树：[left，m-1] --> 每个节点需要小于根节点的值
    // 右子树：[m，right-1] --> 每个节点需要大于根节点的值
    // 根节点：right
    int mid = left;
    while (postorder[mid] < postorder[right]) {
      mid++;
    }
    int t = mid;
    while (postorder[mid] > postorder[right]) {
      mid++;
    }
    return mid == right && dfs(postorder, left, t - 1) &&
           dfs(postorder, t, right - 1);
  }

  bool verifyPostorder(vector<int>& postorder) {
    return dfs(postorder, 0, postorder.size() - 1);
  }
};