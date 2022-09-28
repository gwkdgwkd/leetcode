/*
若链表中的某个节点，既不是链表头节点，
也不是链表尾节点，则称其为该链表的中间节点。
假定已知链表的某一个中间节点，请实现一种算法，将该节点从链表中删除。
例如，传入节点c（位于单向链表a->b->c->d->e->f中），
将其删除后，剩余链表为a->b->d->e->f。

示例：
输入：节点5（位于单向链表4->5->1->9 中）
输出：不返回任何数据，从链表中删除传入的节点5，使链表变为4->1->9。
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 值复制
void deleteNode(struct ListNode* node) {
  node->val = node->next->val;
  node->next = node->next->next;
}

class Solution {
 public:
  void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
  }
};