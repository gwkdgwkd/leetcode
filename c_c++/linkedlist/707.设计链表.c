/*
设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val和next。
val是当前节点的值，next是指向下一个节点的指针/引用。
如果要使用双向链表，则还需要一个属性prev以指示链表中的上一个节点。
假设链表中的所有节点都是0-index的。

在链表类中实现这些功能：
get(index)：获取链表中第index个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为val的节点。
                插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为val的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第index个节点之前添加值为val的节点。
                       如果index等于链表的长度，则该节点将附加到链表的末尾。
                       如果index大于链表长度，则不会插入节点。
                       如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引index有效，则删除链表中的第index个节点。

示例：
MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1,2);   // 链表变为1-> 2-> 3
linkedList.get(1);            // 返回2
linkedList.deleteAtIndex(1);  // 现在链表是1-> 3
linkedList.get(1);            // 返回3

提示：
所有val值都在[1, 1000]之内。
操作次数将在[1, 1000]之内。
请不要使用内置的LinkedList库。
*/

struct Node {
  int val;
  struct Node* next;
};
typedef struct {
  struct Node* head;
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
  MyLinkedList* head = (MyLinkedList*)calloc(1, sizeof(MyLinkedList));
  // printLinkedList("myLinkedListCreate: ",head);
  return head;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
  if (index < 0) {
    return -1;
  }

  int i = 0;
  struct Node* node = obj->head;
  while (node) {
    if (i == index) {
      return node->val;
    }
    ++i;
    node = node->next;
  }

  return -1;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  node->val = val;
  node->next = obj->head;
  obj->head = node;
  // printLinkedList("myLinkedListAddAtHead: ",obj);
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  node->val = val;
  node->next = NULL;

  struct Node* current = obj->head;
  if (current == NULL) {
    obj->head = node;
    // printLinkedList("myLinkedListAddAtTail: ",obj);
    return;
  }
  while (current) {
    if (current->next) {
      current = current->next;
    } else {
      current->next = node;
      // printLinkedList("myLinkedListAddAtTail: ",obj);
      return;
    }
  }
  // printLinkedList("myLinkedListAddAtTail: ",obj);
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
  if (index <= 0) return myLinkedListAddAtHead(obj, val);
  int i = 1;
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  node->val = val;
  node->next = NULL;
  struct Node* current = obj->head;
  while (current) {
    if (i == index) {
      node->next = current->next;
      current->next = node;
    }
    ++i;
    current = current->next;
  }
  // printLinkedList("myLinkedListAddAtIndex: ",obj);
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
  if (index < 0) return;

  if (index == 0) {
    struct Node* tmp = obj->head;
    obj->head = obj->head->next;
    free(tmp);
    tmp = NULL;
  } else {
    struct Node* current = obj->head;
    int i = 1;
    while (current) {
      if (i == index && current->next) {
        struct Node* tmp = current->next;
        current->next = tmp->next;
        free(tmp);
        tmp = NULL;
        return;
      }
      current = current->next;
      i++;
    }
  }

  // printLinkedList("myLinkedListDeleteAtIndex: ", obj);
}

void myLinkedListFree(MyLinkedList* obj) {
  struct Node* cur = obj->head;
  while (cur) {
    struct Node* tmp = cur;
    cur = cur->next;
    free(tmp);
    tmp = NULL;
  }
}

void printLinkedList(const char* str, MyLinkedList* obj) {
  struct Node* cur = obj->head;
  printf("%s[", str);
  while (cur) {
    printf("%d ", cur->val);
    if (cur->next) {
      cur = cur->next;
    } else {
      break;
    }
  }
  printf("]\n");
}
