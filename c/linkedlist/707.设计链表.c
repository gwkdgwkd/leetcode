/*
 * @lc app=leetcode.cn id=707 lang=c
 *
 * [707] 设计链表
 */

// @lc code=start

struct Node {
  int val;
  struct Node* next;
};
typedef struct { struct Node* head; } MyLinkedList;

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

  printLinkedList("myLinkedListDeleteAtIndex: ", obj);
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

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/
/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/
// @lc code=end
