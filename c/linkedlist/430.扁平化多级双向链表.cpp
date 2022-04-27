/*
你会得到一个双链表，其中包含的节点有一个下一个指针、一个前一个指针和一个额外的子指针。
这个子指针可能指向一个单独的双向链表，也包含这些特殊的节点。
这些子列表可以有一个或多个自己的子列表，以此类推，以生成如下面的示例所示的多层数据结构 。
给定链表的头节点head，将链表扁平化，以便所有节点都出现在单层双链表中。
让curr是一个带有子列表的节点。
子列表中的节点应该出现在扁平化列表中的curr之后和curr.next之前。
返回扁平列表的head。列表中的节点必须将其所有子指针设置为null。

示例1：
输入：head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
输出：[1,2,3,7,8,11,12,9,10,4,5,6]
解释：输入的多级列表如上图所示。
扁平化后的链表如下图：

示例2：
输入：head = [1,2,null,3]
输出：[1,3,2]
解释：输入的多级列表如上图所示。

示例3：
输入：head = []
输出：[]
说明：输入中可能存在空列表。

提示：
节点数目不超过 1000
1 <= Node.val <= 10^5

如何表示测试用例中的多级链表？
以示例1为例：
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL

序列化其中的每一级之后：
[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]

为了将每一级都序列化到一起，我们需要每一级中添加值为null的元素，以表示没有节点连接到上一级的上级节点。
[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]

合并所有序列化结果，并去除末尾的null。
[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
*/

// 剑指OfferII028展平多级双向链表

class Node {
 public:
  int val;
  Node* prev;
  Node* next;
  Node* child;
};

class Solution {
 public:
  Node* flatten(Node* head) {
    function<Node*(Node*)> dfs = [&](Node* node) {
      Node* cur = node;
      // 记录链表的最后一个节点
      Node* last = nullptr;

      while (cur) {
        Node* next = cur->next;
        //  如果有子节点，那么首先处理子节点
        if (cur->child) {
          Node* child_last = dfs(cur->child);

          next = cur->next;
          //  将node与child相连
          cur->next = cur->child;
          cur->child->prev = cur;

          //  如果next不为空，就将last与next相连
          if (next) {
            child_last->next = next;
            next->prev = child_last;
          }

          // 将child置为空
          cur->child = nullptr;
          last = child_last;
        } else {
          last = cur;
        }
        cur = next;
      }
      return last;
    };

    dfs(head);
    return head;
  }
};