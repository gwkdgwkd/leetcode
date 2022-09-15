/*
实现一个MyCalendar类来存放你的日程安排。
如果要添加的日程安排不会造成重复预订，则可以存储这个新的日程安排。
当两个日程安排有一些时间上的交叉时，
例如两个日程安排都在同一时间内，就会产生重复预订。
日程可以用一对整数start和end表示，这里的时间是半开区间，
即[start, end),实数x的范围为，start <= x < end。

实现MyCalendar类：
MyCalendar()
初始化日历对象。
boolean book(int start, int end)
如果可以将日程安排成功添加到日历中而不会导致重复预订，返回true。
否则，返回false并且不要将该日程安排添加到日历中。

示例：
输入：
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
输出：
[null, true, false, true]
解释：
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False
这个日程安排不能添加到日历中，因为时间15已经被另一个日程安排预订了。
myCalendar.book(20, 30); // return True
这个日程安排可以添加到日历中，
因为第一个日程安排预订的每个时间都小于20，且不包含时间20。

提示：
0 <= start < end <= 10^9
每个测试用例，调用book方法的次数最多不超过1000次。
*/

// 剑指OfferII058日程表

// 暴力法
typedef struct {
  int start[1000];
  int end[1000];
  int idx;
} MyCalendar;
MyCalendar* myCalendarCreate() {
  MyCalendar* obj = (MyCalendar*)malloc(sizeof(MyCalendar));
  obj->idx = 0;
  return obj;
}
bool myCalendarBook(MyCalendar* obj, int start, int end) {
  for (int i = 0; i < obj->idx; ++i) {
    if (!(end <= obj->start[i] || start >= obj->end[i])) {
      return false;
    }
  }
  obj->start[obj->idx] = start;
  obj->end[obj->idx] = end;
  ++obj->idx;
  return true;
}
void myCalendarFree(MyCalendar* obj) {
  free(obj);
  obj = NULL;
}

// 二分查找
class MyCalendar {
  set<pair<int, int>> booked;

 public:
  bool book(int start, int end) {
    auto it = booked.lower_bound({end, 0});
    if (it == booked.begin() || (--it)->second <= start) {
      booked.emplace(start, end);
      return true;
    }
    return false;
  }
};

// 线段树