/*
给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素insertVal，
使这个列表仍然是循环升序的，给定的可以是这个列表中任意一个顶点的指针，
并不一定是这个列表中最小元素的指针，如果有多个满足条件的插入位置，
可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。
如果列表为空（给定的节点是null），需要创建一个循环有序列表并返回这个节点。
否则，请返回原先给定的节点。

示例1：
输入：head = [3,4,1], insertVal = 2
输出：[3,4,1,2]
解释：有一个包含三个元素的循环有序列表，你获得值为3的节点的指针，需要向表中插入元素2。
新插入的节点应该在1和3之间，插入之后，整个列表如上图所示，最后返回节点3。

示例2：
输入：head = [], insertVal = 1
输出：[1]
解释：列表为空（给定的节点是null），创建一个循环有序列表并返回这个节点。

示例3：
输入：head = [1], insertVal = 0
输出：[1,0]

提示：
0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6

注意：本题与708题相同
*/

// 剑指OfferII029.排序的循环链表

struct Node {
  int val;
  struct TreeNode* next;
};
struct Node* insert(struct Node* head, int insertVal) {
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->val = insertVal;
  if (!head) {
    new_node->next = new_node;
    return new_node;
  }

  // 快慢指针避免所有节点都为相同值死循环
  struct Node* slow = head;
  struct Node* fast = head;
  struct Node* before = head;
  struct Node* after = head->next;
  while (slow->next != fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (((before->val <= insertVal) && (after->val >= insertVal))) {
      // 如果前一个比后一个大且前一个比insertVal小且后一个比insertVal大则找到
      break;
    } else if ((before->val > after->val) &&
               ((before->val <= insertVal) || (after->val >= insertVal))) {
      // 如果前一个比后一个小且前一个和后一个都比insertVal小或大则找到
      break;
    }
    before = before->next;
    after = after->next;
  }

  before->next = new_node;
  new_node->next = after;

  return head;
}

class Solution {
 public:
  Node* insert(Node* head, int insertVal) {
    Node* node = new Node(insertVal);
    if (head == nullptr) {
      node->next = node;
      return node;
    }

    Node* currNode = head;
    Node* nextNode = head->next;
    while (nextNode != head) {
      if (currNode->val <= insertVal && insertVal <= nextNode->val) {
        break;
      }
      if (currNode->val > nextNode->val &&
          (currNode->val < insertVal || insertVal < nextNode->val)) {
        break;
      }
      currNode = currNode->next;
      nextNode = nextNode->next;
    }

    currNode->next = node;
    node->next = nextNode;

    return head;
  }
};