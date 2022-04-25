/*
请实现copyRandomList函数，复制一个复杂链表。
在复杂链表中，每个节点除了有一个next指针指向下一个节点，
还有一个random指针指向链表中的任意节点或者null。

示例1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

示例2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]

示例3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]

示例4：
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回null。

提示：
-10000 <= Node.val <= 10000
Node.random为空（null）或指向链表中的节点。
节点数目不超过1000。

注意：本题与138题相同
*/

class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = nullptr;
    random = nullptr;
  }
};
class Solution {
 public:
  Node* copyRandomList(Node* head) {
    if (head == nullptr) return nullptr;

    Node* cur = head;
    // 1.复制各节点，并构建拼接链表
    while (cur != nullptr) {
      Node* tmp = new Node(cur->val);
      tmp->next = cur->next;
      cur->next = tmp;
      cur = tmp->next;
    }
    // 2.构建各新节点的random指向
    cur = head;
    while (cur != nullptr) {
      if (cur->random != nullptr) cur->next->random = cur->random->next;
      cur = cur->next->next;
    }
    // 3.拆分两链表
    cur = head->next;
    Node *pre = head, *res = head->next;
    while (cur->next != nullptr) {
      pre->next = pre->next->next;
      cur->next = cur->next->next;
      pre = pre->next;
      cur = cur->next;
    }
    pre->next = nullptr;  // 单独处理原链表尾节点
    return res;           // 返回新链表头节点
  }
};