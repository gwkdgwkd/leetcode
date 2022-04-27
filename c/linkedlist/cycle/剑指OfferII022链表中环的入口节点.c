/*
给定一个链表，返回链表开始入环的第一个节点。
从链表的头节点开始沿着next指针进入环的第一个节点为环的入口节点。
如果链表无环，则返回null。
为了表示给定链表中的环，我们使用整数pos来表示链表尾连接到链表中的位置（索引从0开始）。
如果pos是-1，则在该链表中没有环。
注意，pos仅仅是用于标识环的情况，并不会作为参数传递到函数中。
说明：不允许修改给定的链表。

示例1：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为1的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。

示例2：
输入：head = [1,2], pos = 0
输出：返回索引为0的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。

示例3：
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。

提示：
链表中节点的数目范围在范围[0,10^4]内
-10^5 <= Node.val <= 10^5
pos的值为-1或者链表中的一个有效索引

进阶：是否可以使用O(1)空间解决此题？

注意：本题与142题相同
*/

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head) {
  struct ListNode *fast = head;
  struct ListNode *slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) {
      fast = head;
      while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
      }
      return slow;
    }
  }

  return NULL;
}