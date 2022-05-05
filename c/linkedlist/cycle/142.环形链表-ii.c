/*
给定一个链表的头节点head，返回链表开始入环的第一个节点。
如果链表无环，则返回null。
如果链表中有某个节点，可以通过连续跟踪next指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数pos来表示链表尾连接到链表中的位置（索引从0开始）。
如果pos是-1，则在该链表中没有环。
注意：pos不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改链表。

示例1：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。

示例2：
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。

示例3：
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。

提示：
链表中节点的数目范围在范围[0, 10^4]内
-10^5 <= Node.val <= 10^5
pos的值为-1或者链表中的一个有效索引
*/

// 面试题0208环路检测

struct ListNode {
  int val;
  struct ListNode* next;
};
// 快慢指针
struct ListNode* detectCycle(struct ListNode* head) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    // 快慢指针相遇，此时从head和相遇点，同时查找直至相遇
    if (slow == fast) {
      // 当快慢指针相遇时，让其中任一个指针指向头节点，
      // 然后让它俩以相同速度前进，再次相遇时所在的节点位置就是环开始的位置。
      struct ListNode* index1 = fast;  // 从相遇节点也出发一个指针
      struct ListNode* index2 = head;  // 从头结点出发一个指针
      // 这两个指针每次只走一个节点，
      // 那么当这两个指针相遇的时候就是环形入口的节点
      while (index1 != index2) {
        index1 = index1->next;
        index2 = index2->next;
      }
      return index2;  // 返回环的入口
    }
  }
  return NULL;
}
