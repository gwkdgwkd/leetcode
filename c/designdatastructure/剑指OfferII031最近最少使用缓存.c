/*
运用所掌握的数据结构，设计和实现一个LRU(Least Recently Used，最近最少使用)缓存机制。
实现LRUCache类：
LRUCache(int capacity) 以正整数作为容量capacity初始化LRU缓存
int get(int key) 如果关键字key存在于缓存中，则返回关键字的值，否则返回-1。
void put(int key, int value) 
如果关键字已经存在，则变更其数据值；
如果关键字不存在，则插入该组关键字-值。
当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

 

示例：
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是{1=1}
lRUCache.put(2, 2); // 缓存是{1=1, 2=2}
lRUCache.get(1);    // 返回1
lRUCache.put(3, 3); // 该操作会使得关键字2作废，缓存是{1=1, 3=3}
lRUCache.get(2);    // 返回-1(未找到)
lRUCache.put(4, 4); // 该操作会使得关键字1作废，缓存是{4=4, 3=3}
lRUCache.get(1);    // 返回-1(未找到)
lRUCache.get(3);    // 返回3
lRUCache.get(4);    // 返回4

提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 105
最多调用2 * 10^5次get和put

进阶：是否可以在O(1)时间复杂度内完成这两种操作？

注意：本题与146题相同
*/